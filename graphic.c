/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:17:43 by abitonti          #+#    #+#             */
/*   Updated: 2023/09/12 23:50:43 by abitonti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube->h"


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
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W) && cube->map[cube->xpos/100][(cube->ypos-20)/100] != '1')
	{
		cube->ypos -= 5 * round(sin(cube->orientation * M_PI / 180));
		cube->xpos += 5 * round(cos(cube->orientation * M_PI / 180));
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S) && cube->map[cube->xpos/100][(cube->ypos+20)/100] != '1')
	{
		cube->ypos += 5 * round(sin(cube->orientation * M_PI / 180));
		cube->xpos -= 5 * round(cos(cube->orientation * M_PI / 180));
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A) && cube->map[(cube->xpos-20)/100][cube->ypos/100] != '1')
	{
		cube->ypos -= 5 * round(cos(cube->orientation * M_PI / 180));
		cube->xpos -= 5 * round(sin(cube->orientation * M_PI / 180));
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D) && cube->map[(cube->xpos+20)/100][cube->ypos/100] != '1')
	{
		cube->ypos += 5 * round(cos(cube->orientation * M_PI / 180));
		cube->xpos += 5 * round(sin(cube->orientation * M_PI / 180));
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
		cube->orientation = (cube->orientation + 5) % 360;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
		cube->orientation = (cube->orientation + 355) % 360;
}

void	mapinit(t_cube *cube)
{
	int	i;
	int	j;

	cube->orientation = 90;
	cube->mapheight = 10;
	cube->mapwidth = 15;
	cube->xpos = 150;
	cube->ypos = 150;
	cube->map = malloc(cube->mapwidth * sizeof(char *));
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

static void	drawline(mlx_image_t *image, int *a, int *b)
{
	int	max;
	int	x;
	int	y;
	int	i;

	max = 0;
	if (a[0] - b[0] > max)
		max = a[0] - b[0];
	if (a[1] - b[1] > max)
		max = a[1] - b[1];
	if (b[0] - a[0] > max)
		max = b[0] - a[0];
	if (b[1] - a[1] > max)
		max = b[1] - a[1];
	i = -1;
	while (++i <= max)
	{
		x = round((a[0] * i + b[0] * (max - i)) / max);
		y = round((a[1] * i + b[1] * (max - i)) / max);
		mlx_put_pixel(image, x, y, 0xFF0000FF);
	}
}

void	ft_displayme(t_cube *cube, int size)
{
	int	a[2];
	int	b[2];
	int	i;
	int	j;

	a[0] = cube->xpos * cube->imap->width / (100 * cube->mapwidth);
	a[1] = cube->ypos * cube->imap->height / (100 * cube->mapheight);
	i = - size;
	while(i <= size)
	{
		j = - size;
		while(j <= size)
			mlx_put_pixel(cube->imap, a[0] + i, a[1] + j++, 0xFF0000FF);
		i++;
	}
	b[0] = a[0] + round(3 * size * cos(cube->orientation * M_PI / 180));
	b[1] = a[1] - round(3 * size * sin(cube->orientation * M_PI / 180));
	drawline(cube->imap, a, b);
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
			if (!(x % (cube->imap->width - 1)) || !(x % ((cube->imap->width) / cube->mapwidth)))
				mlx_put_pixel(cube->imap, x, y, 0x333333FF);
			else if (!(y % (cube->imap->height - 1)) || !(y % ((cube->imap->height) / cube->mapheight)))
				mlx_put_pixel(cube->imap, x, y, 0x333333FF);
			else if (cube->map[i][j] == '1')
				mlx_put_pixel(cube->imap, x, y, 0xFFFFFFFF);
			else if (cube->map[i][j] == '0')
				mlx_put_pixel(cube->imap, x, y, 0x000000FF);
		}
	}
	ft_displayme(cube, cube->imap->width / (10 * cube->mapwidth));
}

void ft_graphic(t_cube *cube)
{
	mapinit(cube);
	cube->mlx = mlx_init(1200, 900, "cub3D", 1);
	cube->image = mlx_new_image(cube->mlx, cube->mlx->width, cube->mlx->height);
	cube->imap = mlx_new_image(cube->mlx, cube->mlx->width / 4, cube->mlx->width * cube->mapheight / (cube->mapwidth * 4));
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	mlx_image_to_window(cube->mlx, cube->imap, 0, 0);
	ft_randomize(&cube);
	//mlx_loop_hook(mlx, ft_randomize, mlx);
	//mlx_resize_hook(mlx, ft_resize, );
	//ft_displaymap(&cube);
	mlx_loop_hook(cube->mlx, ft_displaymap, &cube);
	mlx_loop_hook(cube->mlx, ft_hook, &cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
}