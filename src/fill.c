/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/24 02:35:16 by ale-roux         ###   ########.fr       */
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
}

void	source_fill2(char *line, t_cube *cube)
{
	if (ft_strncmp(line, "F ", 2) == 0 && cube->utils.floor == false)
	{
		cube->source->floor = ft_source_filling(line);
		cube->utils.floor = true;
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && cube->utils.ceiling == false)
	{
		cube->source->ceiling = ft_source_filling(line);
		cube->utils.ceiling = true;
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && cube->source->east == NULL)
	{
		cube->source->east = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
	}
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
	else
		source_fill2(line, cube);
	free(line);
}

uint32_t	ft_source_filling(char *line)
{
	int			*ret;
	int			i;
	int			j;

	i = 0;
	j = 0;
	ret = (int *)malloc(3 * sizeof(int));
	if (!ret)
		return (0);
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
	return (ft_uint32(ret[0], ret[1], ret[2], ret));
}
