/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/13 08:30:13 by abitonti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//utils

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(int memory)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(memory);
	if (!ptr)
		return (NULL);
	while (i < memory)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char    *tmpstr(t_cube *cube)
{
    char    *map;

    map = ft_calloc(1);
    if (!map)
	{
		free(cube->source);
		free(cube);
		return (NULL);
	}
    return (map);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dup;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1)
		return (-1);
	while (s1[i] && s1[i] == s2[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && n > 0 && s2[i])
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	free_strjoin(char *s1, char *s2, int opt)
{
	if (opt == 0)
		free(s1);
	if (opt == 1)
		free(s2);
	else if (opt == 2)
	{
		free(s1);
		free(s2);
	}
	return ;
}

char	*empty_malloc(char *s1, char *s2, int opt)
{
	char	*ret;

	ret = (char *)malloc(1 * sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	free_strjoin(s1, s2, opt);
	return (ret);
}

char	*cube_strjoin(char *s1, char *s2, int opt)
{
	int		i;
	int		x;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	x = ft_strlen(s2);
	if ((i == 0 && x == 0) || s2[0] == '\n')
		return (empty_malloc(s1, s2, opt));
	str = (char *) malloc((i + x + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	x = 0;
	while (s1[x])
		str[i++] = s1[x++];
	x = 0;
	while (s2[x])
		str[i++] = s2[x++];
	str[i] = '\0';
	free_strjoin(s1, s2, opt);
	return (str);
}

char	*mapsplit(char *map, int lenght)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((lenght + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (map[i] != '\n' && map[i] != '\0')
	{
		str[i] = map[i];
		i++;
	}
	while (i < lenght)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_charfind(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	*null_free(t_cube *cube)
{
	free(cube);
	return (NULL);
}

//program

void	map_calculator(t_cube *cube, char *map)
{
	int	i;
	int	lenght;

	i = 0;
	while (map[i])
	{
		lenght = 0;
		while (map[i] && map[i++] != '\n')
			lenght++;
		if (cube->utils.lenght < lenght)
			cube->utils.lenght = lenght;
		cube->utils.height++;
		//i++;
	}
	//cube->utils.height--;
}

int ft_freeall(t_cube *cube, char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
		free(str);
	while (i < cube->utils.height)
		free(cube->utils.map[i++]);
	free(cube->utils.map);
	free(cube->source->north);
	free(cube->source->south);
	free(cube->source->west);
	free(cube->source->east);
	free(cube->source->floor);
	free(cube->source->ceiling);
	free(cube->source);
	free(cube);
	return (1);
}

t_source	*struct_init(t_cube *cube)
{
	t_source *source;

	source = (t_source *)malloc(1 * sizeof(t_source));
	if (!source)
	{
		free(cube);
		return (NULL);
	}
	cube->angle = -1;
	cube->xpos = -1;
	cube->ypos = -1;
	cube->utils.i = 0;
	cube->utils.lenght = 0;
	cube->utils.height = 0;
	source->north = NULL;
	source->south = NULL;
	source->east = NULL;
	source->west = NULL;
	source->floor = NULL;
	source->ceiling = NULL;
	return (source);
}

int	startpos(t_cube *cube, int x, int y)
{
	if (cube->angle != -1)
		return (1);
	if (cube->utils.map[y][x] == 'N')
		cube->angle = 30;
	else if (cube->utils.map[y][x] == 'S')
		cube->angle = 270;
	else if (cube->utils.map[y][x] == 'E')
		cube->angle = 0;
	else if (cube->utils.map[y][x] == 'W')
		cube->angle = 180;
	else
		return (1);
	cube->xpos = x * 100 + 50;
	cube->ypos = y * 100 + 50;
	cube->utils.map[y][x] = '0';
	printf("depart : %d %d\n", x, y);
	return (0);
}

int	map_verif(char **map, int max_y, int max_x, t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			if (map[y][x] >= 'A' && map[y][x] <= 'Z' && startpos(cube, x, y))
				return (1);
			if (map[y][x] == '0')
			{
				if (x == 0 || x == max_x - 1 || y == 0 || y == max_y - 1)
					return (1);
				if (map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
					return (1);
				if (map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
					return (1);
			}
			x++;
		}
		y++;
	}
	if (cube->angle == -1)
		return (1);
	return (0);
}

int	*ft_source_filling(char *line)
{
	int	*ret;
	int	i;
	int	j;

	i = 0;
	j = 0;
	ret = (int *)malloc(3 * sizeof(int));
	if (!ret)
		return (NULL);
	ret[0] = 0;
	ret[1] = 0;
	ret[2] = 0;
	while (line[i] > '9' || line[i] < '0')
		i++;
	while (line[i] <= '9' && line[i] >= '0')
		ret[j] = (ret[j] * 10) + line[i++] - 48;
	i++;
	j++;
	while (line[i] <= '9' && line[i] >= '0')
		ret[j] = (ret[j] * 10) + line[i++] - 48;
	j++;
	i++;
	while (line[i] <= '9' && line[i] >= '0')
		ret[j] = (ret[j] * 10) + line[i++] - 48;
	return (ret);
}

int	map_formator(t_cube *cube, char *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cube->utils.map = (char **)malloc(cube->utils.height * sizeof(char *));
	while (i < cube->utils.height)
	{
		cube->utils.map[i] = mapsplit(&map[j], cube->utils.lenght);
		j = j + ft_charfind(&map[j], '\n') + 1;
		i++;
	}
	free(map);
	if (map_verif(cube->utils.map, cube->utils.height, cube->utils.lenght, cube) == 1)
		return (ft_freeall(cube, NULL));
	return (0);
}

void	source_fill2(char *line, t_cube *cube)
{
	if (ft_strncmp(line, "F ", 2) == 0 && cube->source->floor == NULL)
	{
		cube->source->floor = ft_source_filling(line);
		cube->utils.i++;
		printf("F: %d, %d, %d\n", cube->source->floor[0], cube->source->floor[1], cube->source->floor[2]);
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && cube->source->ceiling == NULL)
	{
		cube->source->ceiling = ft_source_filling(line);
		cube->utils.i++;
		printf("C: %d, %d, %d\n", cube->source->ceiling[0], cube->source->ceiling[1], cube->source->ceiling[2]);
	}
}

void	source_fill(char *line, t_cube *cube)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && cube->source->north == NULL)
	{
		cube->source->north = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && cube->source->south == NULL)
	{
		cube->source->south = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0 && cube->source->west == NULL)
	{
		cube->source->west = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && cube->source->east == NULL)
	{
		cube->source->east = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
	}
	else
		source_fill2(line, cube);
}

int	ft_open(char *arg)
{
	int	fd;

	if (ft_strcmp(ft_strrchr(arg, '.'), ".cub") != 0)
		return (-1);
	fd = open(arg, O_RDONLY);
	return (fd);
}

t_cube	*start(char *arg)
{
	t_cube	*cube;
	int		fd;
	char	*line;
	char	*map;

	cube = (t_cube *)malloc(1 * sizeof(t_cube));
	if (!cube)
		return (NULL);
	cube->source = struct_init(cube);
	map = tmpstr(cube);
	if (!cube->source)
		return (null_free(cube));
	fd = ft_open(arg);
	if (fd < 0)
	{
		free(cube->source);
		free(cube);
		printf("Please give a valid file :D\n");
		return (NULL);
	}
	while (cube->utils.i < 6)
	{
		line = get_next_line(fd);
		source_fill(line, cube);
		free(line);
	}
	cube->utils.i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map = cube_strjoin(map, line, 2);
		line = get_next_line(fd);
	}
	map_calculator(cube, map);
	if (map_formator(cube, map) == 1)
		return (NULL);
	return (cube);
}

void	print_help(char *exec)
{
	printf("===============================HELP");
	printf("===============================\n");
	printf("|| Name of program: %s\t\t\t\t\t||\n", exec);
	printf("|| launch program : ./%s <*.cub>\t\t\t\t||\n", exec);
	printf("|| Control        :\t\t\t\t\t\t||\n");
	printf("||\t  - [Esc] : close the program\t\t\t\t||\n");
	printf("||\t  - [W]   : move straight \t\t\t\t||\n");
	printf("||\t  - [A]   : move left\t\t\t\t\t||\n");
	printf("||\t  - [S]   : move back\t\t\t\t\t||\n");
	printf("||\t  - [D]   : move right\t\t\t\t\t||\n");
	printf("||\t  - [↑]   : move straight\t\t\t\t||\n");
	printf("||\t  - [↓]   : move back\t\t\t\t\t||\n");
	printf("||\t  - [→]   : move camera right\t\t\t\t||\n");
	printf("||\t  - [←]   : move camera left\t\t\t\t||\n");
	printf("=====================================");
	printf("=============================\n");
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	if (argc == 2)
		cube = start(argv[1]);
	else if (argc == 1)
	{
		print_help(&argv[0][2]);
		return (1);
	}
	else
	{
		printf("ARG ERROR\n");
		return (1);
	}
	if (cube != NULL && printf("plop\n"))
		ft_graphic(cube);
	return (0);
}
