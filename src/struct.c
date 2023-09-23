/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/24 01:38:07 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	ft_freeall(t_cube *cube, char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
		free(str);
	if (cube->mlx)
		mlx_terminate(cube->mlx);
	while (i < cube->utils.height)
		free(cube->utils.map[i++]);
	free(cube->utils.map);
	free(cube->source->north);
	free(cube->source->south);
	free(cube->source->west);
	free(cube->source->east);
	free(cube->source);
	free(cube);
	return (1);
}

t_source	*struct_init(t_cube *cube)
{
	t_source	*source;

	source = malloc(sizeof(t_source));
	if (!source)
	{
		free(cube);
		return (NULL);
	}
	cube->mlx = 0;
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
	cube->utils.floor = false;
	cube->utils.ceiling = false;
	cube->utils.mouse = true;
	cube->utils.animation = false;
	return (source);
}

int	startpos(t_cube *cube, int x, int y)
{
	if (cube->utils.map[y][x] == 'D')
		return (0);
	if (cube->angle != -1)
		return (1);
	if (cube->utils.map[y][x] == 'N')
		cube->angle = 900;
	else if (cube->utils.map[y][x] == 'S')
		cube->angle = 2700;
	else if (cube->utils.map[y][x] == 'E')
		cube->angle = 0;
	else if (cube->utils.map[y][x] == 'W')
		cube->angle = 1800;
	else
		return (1);
	cube->xpos = x * 1000 + 500;
	cube->ypos = y * 1000 + 500;
	cube->utils.map[y][x] = '0';
	return (0);
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
