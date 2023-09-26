/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/26 03:46:24 by ale-roux         ###   ########.fr       */
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
	if (cube->utils.map != NULL)
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
	cube->anim = 0;
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

void	textinit(t_cube *cube)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(cube->source->north);
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->textures[0] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png(cube->source->south);
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->textures[1] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png(cube->source->west);
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->textures[2] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png(cube->source->east);
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->textures[3] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
}
