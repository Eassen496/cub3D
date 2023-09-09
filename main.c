/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/10 01:09:09 by abitonti         ###   ########.fr       */
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

void	*ft_calloc(size_t memory)
{
	char			*ptr;
	unsigned int	i;

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

int	ft_strncmp(char *s1, char *s2, size_t n)
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

//program
/*
void	map_calculator(t_cube *cube)
{
	//calculate the size of the map
}
*/

t_source	*struct_init(t_cube *cube)
{
	t_source *source;

	source = (t_source *)malloc(1 * sizeof(t_source));
	if (!source)
	{
		free(cube);
		return (NULL);
	}
	cube->utils.i = 0;
	cube->utils.lenght = 0;
	cube->utils.height = 0;
	cube->utils.map = ft_calloc(1 * sizeof(char));
	if (!cube->utils.map)
	{
		free(source);
		free(cube);
		return (NULL);
	}
	source->north = NULL;
	source->south = NULL;
	source->east = NULL;
	source->west = NULL;
	source->floor = NULL;
	source->ceiling = NULL;
	return (source);
}

void	source_fill2(char *line, t_cube *cube)
{
	if (ft_strncmp(line, "F ", 2) == 0 && cube->source->floor == NULL)
	{
		cube->source->floor = ft_strdup(ft_strchr(line, ' '));
		cube->utils.i++;
		printf("F to pay respect\n");
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && cube->source->ceiling == NULL)
	{
		cube->source->ceiling = ft_strdup(ft_strchr(line, ' '));
		cube->utils.i++;
		printf("C\n");
	}
}

void	source_fill(char *line, t_cube *cube)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && cube->source->north == NULL)
	{
		cube->source->north = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
		printf("NO\n");
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && cube->source->south == NULL)
	{
		cube->source->south = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
		printf("SO\n");
	}
	else if (ft_strncmp(line, "WE ", 3) == 0 && cube->source->west == NULL)
	{
		cube->source->west = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
		printf("WE\n");
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && cube->source->east == NULL)
	{
		cube->source->east = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
		printf("EA\n");
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

void	start(char *arg)
{
	t_cube	*cube;
	int		fd;
	char	*line;

	cube = (t_cube *)malloc(1 * sizeof(t_cube));
	if (!cube)
		return ;
	cube->source = struct_init(cube);
	if (!cube)
		return ;
	fd = ft_open(arg);
	if (fd < 0)
	{
		free(cube->source);
		free(cube);
		printf("Please give a valid file :D\n");
		return ;
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
		cube->utils.map = cube_strjoin(cube->utils.map, line, 2);
		line = get_next_line(fd);
	}
	//map_calculator(cube);
	printf("%s", cube->utils.map);
}

void	print_help(char *exec)
{
	printf("===============================HELP");
	printf("===============================\n");
	printf("|| Name of program: %s\t\t\t\t\t||\n", exec);
	printf("|| launch program : ./%s <*.cub>\t\t\t\t||\n", exec);
	printf("|| Control        :\t\t\t\t\t\t||\n");
	printf("||\t  - [Esc]  : close the program\t\t\t\t||\n");
	printf("||\t  - [W]  : move straight \t\t\t\t||\n");
	printf("||\t  - [A]  : move left\t\t\t\t\t||\n");
	printf("||\t  - [S]  : move back\t\t\t\t\t||\n");
	printf("||\t  - [D]  : move right\t\t\t\t\t||\n");
	printf("||\t  - [↑]  : move straight\t\t\t\t||\n");
	printf("||\t  - [↓]  : move back\t\t\t\t\t||\n");
	printf("||\t  - [→]  : move camera right\t\t\t\t||\n");
	printf("||\t  - [←]  : move camera left\t\t\t\t||\n");
	printf("=====================================");
	printf("=============================\n");
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	uint32_t 	color;
	mlx_image_t	*image;

	image = ((t_cube *) param)->image;
	for (uint32_t x = 0; x < image->width; ++x)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			/*color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);*/
			if (y < image->height / 2)
				color = 0xFFFFFFFF;
			else
				color = 0xFFFFFF00;
			mlx_put_pixel(image, x, y, color);
		}
	}
}

void ft_hook(void* param)
{
	t_cube	*cube;

	cube = (t_cube *) param;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_UP))
		cube->image->instances[0].y -= 5;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN))
		cube->image->instances[0].y += 5;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
		cube->image->instances[0].x -= 5;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
		cube->image->instances[0].x += 5;
}

void	mapinit(t_cube *cube)
{
	int	i;
	int	j;

	cube->mapheight = 15;
	cube->mapwidth = 10;
	cube->map = malloc(cube->mapheight * sizeof(char *));
	i = -1;
	while (++i < cube->mapheight)
	{
		j = -1;
		cube->map[i] = malloc(cube->mapwidth * sizeof (char));
		while (++j < cube->mapwidth)
		{
			if (i % (cube->mapheight - 1) && j % (cube->mapwidth - 1))
				cube->map[i][j] = '0';
			else
				cube->map[i][j] = '1';
		}
	}
}

void	ft_displaymap(t_cube *cube)
{
	uint32_t	x;
	uint32_t	y;
	int	i;
	int	j;

	y = -1;
	while (++y < cube->imap->height)
	{
		x = -1;
		while (++x < cube->imap->width)
		{
			j = x * cube->mapwidth / (cube->imap->width + 1);
			i = y * cube->mapheight / (cube->imap->height + 1);
			if (!(x % (cube->imap->width - 1)) || !(x % (cube->imap->width / cube->mapwidth)))
				mlx_put_pixel(cube->imap, x, y, 0x333333FF);
			else if (!(y % (cube->imap->height - 1)) || !(y % (cube->imap->height / cube->mapheight)))
				mlx_put_pixel(cube->imap, x, y, 0x333333FF);
			else if (cube->map[i][j] == '1')
				mlx_put_pixel(cube->imap, x, y, 0xFFFFFFFF);
			else if (cube->map[i][j] == '0')
				mlx_put_pixel(cube->imap, x, y, 0x000000FF);
		}
	}
}

int	main(int argc, char **argv)
{
	t_cube		cube;

	if (argc == 2)
		start(argv[1]);
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
	mapinit(&cube);
	cube.mlx = mlx_init(800, 600, "cub3D", 1);
	cube.image = mlx_new_image(cube.mlx, cube.mlx->width, cube.mlx->height);
	cube.imap = mlx_new_image(cube.mlx, cube.mlx->width / 4, cube.mlx->width * cube.mapheight / (cube.mapwidth * 4));
	mlx_image_to_window(cube.mlx, cube.image, 0, 0);
	mlx_image_to_window(cube.mlx, cube.imap, 0, 0);
	ft_randomize(&cube);
	//mlx_loop_hook(mlx, ft_randomize, mlx);
	//mlx_resize_hook(mlx, ft_resize, );
	ft_displaymap(&cube);
	mlx_loop_hook(cube.mlx, ft_hook, &cube);
	mlx_loop(cube.mlx);
	mlx_terminate(cube.mlx);
	return (0);
}
