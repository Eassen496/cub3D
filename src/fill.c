/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/27 00:48:51 by abitonti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	finish_all(t_cube *cube)
{
	if (cube->source->north == NULL)
		cube->source->north = ft_calloc(1 * sizeof(char));
	if (cube->source->south == NULL)
		cube->source->south = ft_calloc(1 * sizeof(char));
	if (cube->source->west == NULL)
		cube->source->west = ft_calloc(1 * sizeof(char));
	if (cube->source->east == NULL)
		cube->source->east = ft_calloc(1 * sizeof(char));
	cube->utils.map = NULL;
}

int	test(t_cube *cube, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		finish_all(cube);
		return (1);
	}
	close(fd);
	return (0);
}

void	source_fill3(char *line, t_cube *cube)
{
	if (ft_strncmp(line, "WE ", 3) == 0 && cube->source->west == NULL)
	{
		cube->source->west = ft_strdup(ft_strchr(line, '.'));
		if (test(cube, cube->source->west) == 1)
			cube->utils.i = 6;
		cube->utils.i++;
	}
}

void	source_fill2(char *line, t_cube *cube)
{
	if (ft_strncmp(line, "F ", 2) == 0 && cube->utils.floor == false)
	{
		cube->source->floor = ft_source_filling(line + 2, cube);
		if (cube->utils.i == 7)
			return (finish_all(cube));
		cube->utils.floor = true;
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && cube->utils.ceiling == false)
	{
		cube->source->ceiling = ft_source_filling(line + 2, cube);
		if (cube->utils.i == 7)
			return (finish_all(cube));
		cube->utils.ceiling = true;
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && cube->source->east == NULL)
	{
		cube->source->east = ft_strdup(ft_strchr(line, '.'));
		if (test(cube, cube->source->east) == 1)
			cube->utils.i = 6;
		cube->utils.i++;
	}
	else
		source_fill3(line, cube);
}

void	source_fill(char *line, t_cube *cube)
{
	if (line == NULL)
	{
		cube->utils.i = 7;
		finish_all(cube);
		return ;
	}
	else if (ft_strncmp(line, "NO ", 3) == 0 && cube->source->north == NULL)
	{
		cube->source->north = ft_strdup(ft_strchr(line, '.'));
		if (test(cube, cube->source->north) == 1)
			cube->utils.i = 6;
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && cube->source->south == NULL)
	{
		cube->source->south = ft_strdup(ft_strchr(line, '.'));
		if (test(cube, cube->source->south) == 1)
			cube->utils.i = 6;
		cube->utils.i++;
	}
	else
		source_fill2(line, cube);
	free(line);
}
