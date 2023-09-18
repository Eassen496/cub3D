/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:17:43 by abitonti          #+#    #+#             */
/*   Updated: 2023/09/18 23:32:18 by ale-roux         ###   ########.fr       */
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
	int		dx;
	int		dy;

	dx = 0;
	dy = 0;
	cube = (t_cube *) param;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
	{
		dy -= round(5 * sin(cube->angle * M_PI / 180));
		dx += round(5 * cos(cube->angle * M_PI / 180));
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
	{
		dy += round(5 * sin(cube->angle * M_PI / 180));
		dx -= round(5 * cos(cube->angle * M_PI / 180));
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
	{
		dy -= round(5 * cos(cube->angle * M_PI / 180));
		dx -= round(5 * sin(cube->angle * M_PI / 180));
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
	{
		dy += round(5 * cos(cube->angle * M_PI / 180));
		dx += round(5 * sin(cube->angle * M_PI / 180));
	}
	if (dx > 0  && cube->map[cube->ypos / 100][(cube->xpos + 20) / 100] == '0')
		cube->xpos += dx;
	if (dx < 0  && cube->map[cube->ypos / 100][(cube->xpos - 20) / 100] == '0')
		cube->xpos += dx;
	if (dy > 0  && cube->map[(cube->ypos + 20) / 100][cube->xpos / 100] == '0')
		cube->ypos += dy;
	if (dy < 0  && cube->map[(cube->ypos - 20) / 100][cube->xpos / 100] == '0')
		cube->ypos += dy;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
		cube->angle = (cube->angle + 4) % 360;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
		cube->angle = (cube->angle + 356) % 360;
}
/*
void	mapinit(t_cube *cube)
{
	int	i;
	int	j;

	cube->angle = 90;
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
*/
static void	drawline(mlx_image_t *image, int *a, int *b)
{
	int	max;
	int	x;
	int	y;
	int	i;

	max = 1;
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

float	ft_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_nextwall_y(float a, t_cube *cube, int s)
{
	int		y;
	int		x;

	x = cube->xpos;
	y = cube->ypos;
	y += s * (y % 100) + (1 + s) * (100 - y % 100);
	x -= (y - cube->ypos) / tan(a * M_PI / 180);
	if (!y || y / 100 == cube->mapheight - 1 || x / 100 < 0 || x / 100 > cube->mapwidth - 1)
		return (10000);
	while (cube->map[y / 100 + s][x / 100] != '1')
	{
		y += (1 + 2 * s) * 100;
		x -= (1 + 2 * s) * 100 / tan(a * M_PI / 180);
		if (!y || y / 100 == cube->mapheight - 1 || x / 100 < 0 || x / 100 > cube->mapwidth - 1)
			return (10000);
	}
	printf("%d %d\n", x, y);
	return ((cube->ypos - y) / sin(a * M_PI / 180));
}

float	ft_nextwall_x(float a, t_cube *cube, int s)
{
	int		y;
	int		x;

	x = cube->xpos;
	y = cube->ypos;
	x += s * (x % 100) + (1 + s) * (100 - x % 100);
	y -= (x - cube->xpos) * tan(a * M_PI / 180);
	if (!x || x / 100 == cube->mapwidth - 1 || y / 100 < 0 || y / 100 > cube->mapheight - 1)
		return (10000);
	while (cube->map[y / 100][x / 100 + s] != '1')
	{
		x += (1 + 2 * s) * 100;
		y -= (1 + 2 * s) * 100 * tan(a * M_PI / 180);
		if (!x || x / 100 == cube->mapwidth - 1 || y / 100 < 0 || y / 100 > cube->mapheight - 1)
			return (10000);
	}
	printf("%d %d %f\n", x, y, a);
	return ((x - cube->xpos) / cos(a * M_PI / 180));
}


void	ft_displayme(t_cube *cube, int size)
{
	int	a[2];
	int	b[2];
	int	i;
	int	j;
	float	distance;

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
	distance = ft_min(ft_nextwall_y((float)cube->angle, cube, -1), ft_nextwall_x((float)cube->angle, cube, 0));
	printf("%f\n", distance);
	distance *= (float) cube->imap->width / (100 * (float) cube->mapwidth);
	b[0] = a[0] + round(distance * cos(cube->angle * M_PI / 180));
	b[1] = a[1] - round(distance * sin(cube->angle * M_PI / 180));
	drawline(cube->imap, a, b);
}

void	ft_displaymap(void *param)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	i;
	uint32_t	j;
	t_cube		*cube;

	cube = (t_cube *) param;
	y = -1;
	while (++y < cube->imap->height)
	{
		x = -1;
		while (++x < cube->imap->width)
		{
			i = x * cube->mapwidth / cube->imap->width;
			j = y * cube->mapheight / cube->imap->height;
			if (cube->map[j][i] == ' ' || !x || !y || (x + 1) * cube->mapwidth / cube->imap->width > i || (y + 1) * cube->mapheight / cube->imap->height > j)
				mlx_put_pixel(cube->imap, x, y, 0x333333FF);
			else if (cube->map[j][i] == '1')
				mlx_put_pixel(cube->imap, x, y, 0xFFFFFFFF);
			else if (cube->map[j][i] == '0')
				mlx_put_pixel(cube->imap, x, y, 0x000000FF);
		}
	}
	ft_displayme(cube, cube->imap->width / (10 * cube->mapwidth));
}

void	ft_displayworld(void *param)
{
	t_cube		*cube;
	uint32_t	x;
	float		angle;
	float		distance;

	cube = (t_cube *) param;
	x = -1;
	while (++x < cube->image->width)
	{
		angle = cube->angle - 45 + 90 * x / cube->image->width;
		while (1)
		{
			if (angle < 180)
				distance = ft_nextwall_y(angle, cube, -1);
		}
	}
}

void ft_graphic(t_cube *cube)
{
	cube->map = cube->utils.map;
	cube->mapwidth = cube->utils.lenght;
	cube->mapheight = cube->utils.height;
	cube->mlx = mlx_init(1200, 900, "cub3D", 1);
	cube->image = mlx_new_image(cube->mlx, cube->mlx->width, cube->mlx->height);
	cube->imap = mlx_new_image(cube->mlx, cube->mlx->width / 2, cube->mlx->width * cube->mapheight / (cube->mapwidth * 2));
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	mlx_image_to_window(cube->mlx, cube->imap, 0, 0);
	//ft_randomize(cube);
	//mlx_loop_hook(mlx, ft_randomize, mlx);
	//mlx_resize_hook(mlx, ft_resize, );
	//ft_displaymap(cube);
	mlx_loop_hook(cube->mlx, ft_displaymap, cube);
	mlx_loop_hook(cube->mlx, ft_hook, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
}