/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/08/31 00:18:01 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "cube.h"
#include "get_next_line.h"

//get_next_line

static int	freeall(t_line **line)
{
	t_line	*next;

	while (*line)
	{
		free((*line)->buff);
		next = (*line)->next;
		free(*line);
		*line = next;
	}
	return (1);
}

static int	new_tline(t_line **line)
{
	*line = malloc(sizeof(t_line));
	if (!(*line))
		return (0);
	(*line)->buff = malloc(100);
	if (!((*line)->buff))
	{
		free(*line);
		*line = 0;
		return (0);
	}
	(*line)->next = 0;
	(*line)->i = 0;
	(*line)->start = 0;
	(*line)->end = 0;
	return (1);
}

static int	get_next_buff(int fd, int n, t_line *line)
{
	if (!(line->i))
		line->end = read(fd, line->buff, 100);
	if (line->end == -1 || (line->end == 0 && n == 0))
		return (0);
	while (line->i < line->end && (line->buff)[line->i] != '\n')
		(line->i)++;
	if (line->i == 100)
	{
		if (!new_tline(&(line->next)))
			return (0);
		return (get_next_buff(fd, n + line->i - line->start, line->next));
	}
	if ((line->buff)[line->i] == '\n')
		(line->i)++;
	return (n + line->i - line->start);
}

static void	fillsol(char *sol, int n, t_line **line)
{
	int		j;
	t_line	*next;

	while (*line)
	{
		j = (*line)->start - 1;
		while (++j < (*line)->i)
			sol[n++] = ((*line)->buff)[j];
		if (j == (*line)->end)
		{
			free((*line)->buff);
			next = (*line)->next;
			free(*line);
			*line = next;
		}
		else
		{
			(*line)->start = j;
			break ;
		}
	}
	sol[n] = 0;
	return ;
}

char	*get_next_line(int fd)
{
	static t_line	*line[256];
	int				size;
	char			*sol;

	if (fd < 0 || fd == 1 || fd == 2 || fd > 255)
		return (0);
	if (!line[fd] && !new_tline(&(line[fd])))
		return (0);
	size = get_next_buff(fd, 0, line[fd]);
	if (!size && freeall(&(line[fd])))
		return (0);
	sol = malloc(size + 1);
	if (!sol && freeall(&(line[fd])))
		return (0);
	fillsol(sol, 0, &(line[fd]));
	return (sol);
}

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

int	main(int argc, char **argv)
{
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
	return (0);
}
