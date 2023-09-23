/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/24 01:37:04 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	map_verif_bis(int x, int y, char **map)
{
	if (map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
		return (1);
	if (map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
		return (1);
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
			if (map[y][x] == '0' || map[y][x] == 'D')
			{
				if (x == 0 || x == max_x - 1 || y == 0 || y == max_y - 1)
					return (1);
				if (map_verif_bis(x, y, map) == 1)
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
	if (map_verif(cube->utils.map, cube->utils.height,
			cube->utils.lenght, cube) == 1)
		return (ft_freeall(cube, NULL));
	return (0);
}

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
	}
}
