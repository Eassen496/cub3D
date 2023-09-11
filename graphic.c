/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:17:43 by abitonti          #+#    #+#             */
/*   Updated: 2023/09/11 03:19:51 by abitonti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


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
	if (mlx_is_key_down(cube->mlx, MLX_KEY_UP) && cube->map[cube->xpos/100][(cube->ypos-20)/100] != '1')
		cube->ypos -= 5;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN) && cube->map[cube->xpos/100][(cube->ypos+20)/100] != '1')
		cube->ypos += 5;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT) && cube->map[(cube->xpos-20)/100][cube->ypos/100] != '1')
		cube->xpos -= 5;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT) && cube->map[(cube->xpos+20)/100][cube->ypos/100] != '1')
		cube->xpos += 5;
}

void	mapinit(t_cube *cube)
{
	int	i;
	int	j;

	cube->mapheight = 15;
	cube->mapwidth = 10;
	cube->xpos = 500;
	cube->ypos = 750;
	cube->map = malloc(cube->mapheight * sizeof(char *));
	i = -1;
	while (++i < cube->mapwidth)
	{
		j = -1;
		cube->map[i] = malloc(cube->mapheight * sizeof (char));
		while (++j < cube->mapheight)
		{
			if (i % (cube->mapwidth - 1) && j % (cube->mapheight - 1))
				cube->map[i][j] = '0';
			else
				cube->map[i][j] = '1';
		}
	}
}

void	ft_displayme(t_cube *cube, int size)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = cube->xpos * cube->imap->width / (100 * cube->mapwidth);
	y = cube->ypos * cube->imap->height / (100 * cube->mapheight);
	i = - size;
	while(i <= size)
	{
		j = - size;
		while(j <= size)
			mlx_put_pixel(cube->imap, x + i, y + j++, 0xFF0000FF);
		i++;
	}
}

void	ft_displaymap(void *param)
{
	uint32_t	x;
	uint32_t	y;
	int	i;
	int	j;
	t_cube	*cube;

	cube = (t_cube *) param;
	y = -1;
	while (++y < cube->imap->height)
	{
		x = -1;
		while (++x < cube->imap->width)
		{
			i = x * cube->mapwidth / cube->imap->width;
			j = y * cube->mapheight / cube->imap->height;
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
	ft_displayme(cube, cube->imap->width / (10 * cube->mapwidth));
}

void ft_graphic(void)
{
	t_cube		cube;

	mapinit(&cube);
	cube.mlx = mlx_init(800, 600, "cub3D", 1);
	cube.image = mlx_new_image(cube.mlx, cube.mlx->width, cube.mlx->height);
	cube.imap = mlx_new_image(cube.mlx, cube.mlx->width / 4, cube.mlx->width * cube.mapheight / (cube.mapwidth * 4));
	mlx_image_to_window(cube.mlx, cube.image, 0, 0);
	mlx_image_to_window(cube.mlx, cube.imap, 0, 0);
	ft_randomize(&cube);
	//mlx_loop_hook(mlx, ft_randomize, mlx);
	//mlx_resize_hook(mlx, ft_resize, );
	//ft_displaymap(&cube);
	mlx_loop_hook(cube.mlx, ft_displaymap, &cube);
	mlx_loop_hook(cube.mlx, ft_hook, &cube);
	mlx_loop(cube.mlx);
	mlx_terminate(cube.mlx);
}