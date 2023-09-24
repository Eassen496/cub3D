/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:17:43 by abitonti          #+#    #+#             */
/*   Updated: 2023/09/25 00:51:35 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	ft_displayworld(t_cube *cube)
{
	uint32_t	x;
	float		angle;
	t_point		point;

	x = -1;
	while (++x < cube->image->width)
	{
		point.distance = 100000;
		angle = (cube->angle + 4050 - 900 * x / cube->image->width) % 3600;
		ft_nextwall_y(angle, cube, 0, &point);
		ft_nextwall_x(angle, cube, -1, &point);
		ft_drawcol(cube, point, x);
	}
}

void	ft_displaybackground(t_cube *cube)
{
	uint32_t	x;
	uint32_t	y;

	x = -1;
	while (++x < cube->image->width)
	{
		y = -1;
		while (++y < cube->image->height)
		{
			if (y < cube->image->height / 2)
				mlx_put_pixel(cube->image, x, y, cube->source->ceiling);
			else
				mlx_put_pixel(cube->image, x, y, cube->source->floor);
		}
	}
}

void	ft_resizehook(int32_t width, int32_t height, void *param)
{
	t_cube	*cube;

	(void) height;
	(void) width;
	cube = (t_cube *) param;
	cube->resize = true;
}

void	ft_display(void *param)
{
	t_cube		*cube;

	cube = (t_cube *) param;
	ft_displaybackground(cube);
	ft_displayworld(cube);
	ft_displaymap(cube, -1, -1);
}

void	ft_graphic(t_cube *cube)
{
	int	mapsize[2];

	cube->map = cube->utils.map;
	cube->mw = cube->utils.lenght;
	cube->mh = cube->utils.height;
	cube->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	textinit(cube);
	cube->image = mlx_new_image(cube->mlx, cube->mlx->width, cube->mlx->height);
	ft_mapsize(cube, mapsize);
	cube->imap = mlx_new_image(cube->mlx, mapsize[0], mapsize[1]);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	mlx_image_to_window(cube->mlx, cube->imap, 0, 0);
	mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(cube->mlx, ft_display, cube);
	mlx_loop_hook(cube->mlx, ft_hook, cube);
	mlx_cursor_hook(cube->mlx, ft_mousehook, cube);
	mlx_resize_hook(cube->mlx, ft_resizehook, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
	cube->mlx = 0;
}
