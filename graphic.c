/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:17:43 by abitonti          #+#    #+#             */
/*   Updated: 2023/09/23 03:07:17 by abitonti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void ft_hook(void* param)
{
	t_cube		*cube;
	int			dx;
	int			dy;
	float		speed;
	int32_t		mx;
	int32_t		my;

	dx = 0;
	dy = 0;
	speed = 1;
	cube = (t_cube *) param;
	mx = WIDTH / 2;
	my = HEIGHT / 2;
	mlx_get_mouse_pos(cube->mlx, &mx, &my);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_SUPER))
		speed = 0.5;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_SHIFT))
		speed = 2.5;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
	{
		dy -= round(50 * sin(cube->angle * M_PI / 1800) * speed);
		dx += round(50 * cos(cube->angle * M_PI / 1800) * speed);
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
	{
		dy += round(50 * sin(cube->angle * M_PI / 1800) * speed);
		dx -= round(50 * cos(cube->angle * M_PI / 1800) * speed);
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
	{
		dy -= round(50 * cos(cube->angle * M_PI / 1800) * speed);
		dx -= round(50 * sin(cube->angle * M_PI / 1800) * speed);
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
	{
		dy += round(50 * cos(cube->angle * M_PI / 1800) * speed);
		dx += round(50 * sin(cube->angle * M_PI / 1800) * speed);
	}
	if (dx > 0  && (cube->map[cube->ypos / 1000][(cube->xpos + 200) / 1000] == '0' || cube->map[cube->ypos / 1000][(cube->xpos + 20) / 1000] == 'D'))
		cube->xpos += dx;
	if (dx < 0  && (cube->map[cube->ypos / 1000][(cube->xpos - 200) / 1000] == '0' || cube->map[cube->ypos / 1000][(cube->xpos - 200) / 1000] == 'D'))
		cube->xpos += dx;
	if (dy > 0  && (cube->map[(cube->ypos + 200) / 1000][cube->xpos / 1000] == '0' || cube->map[(cube->ypos + 200) / 1000][cube->xpos / 1000] == 'D'))
		cube->ypos += dy;
	if (dy < 0  && (cube->map[(cube->ypos - 200) / 1000][cube->xpos / 1000] == '0' || cube->map[(cube->ypos - 200) / 1000][cube->xpos / 1000] == 'D'))
		cube->ypos += dy;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT) || ((mx < (WIDTH / 2) - 5) && cube->utils.mouse == true))
	{
		cube->angle = (cube->angle + 80) % 3600;
		if (cube->utils.mouse == true)
			mlx_set_mouse_pos(cube->mlx, WIDTH / 2, HEIGHT / 2);
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT) || ((mx > (WIDTH / 2) + 5) && cube->utils.mouse == true))
	{
		cube->angle = (cube->angle + 3520) % 3600;
		if (cube->utils.mouse == true)
			mlx_set_mouse_pos(cube->mlx, WIDTH / 2, HEIGHT / 2);
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_SPACE) && cube->utils.mouse == true)
	{
		cube->utils.mouse = false;
		mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_NORMAL);
	}
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_M) && cube->utils.mouse == false)
	{
		cube->utils.mouse = true;
		mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_HIDDEN);
	}
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

float	ft_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	ft_nextwall_y(float a, t_cube *cube, int s, t_point *p)
{
	int		y;
	int		x;

	if (!a || a == 1800)
		return (100000);
	if (a < 1800)
		s = -1;
	y = cube->ypos + s * (cube->ypos % 1000) + (1 + s) * (1000 - cube->ypos % 1000);
	x = cube->xpos - (y - cube->ypos) / tan(a * M_PI / 1800);
	if (!y || y / 1000 > cube->mapheight - 1 || x < 0 || x / 1000 > cube->mapwidth - 1)
		return (100000);
	while (cube->map[y / 1000 + s][x / 1000] == '0' || ((cube->map[y / 1000 + s][x / 1000] == 'D') && abs(cube->ypos - y) < 1000 && abs(cube->xpos / 1000 - x / 1000) <= 1))
	{
		y += (1 + 2 * s) * 1000;
		x = cube->xpos - (y - cube->ypos) / tan(a * M_PI / 1800);
		if (!y || y / 1000 > cube->mapheight - 1 || x < 0 || x / 1000 > cube->mapwidth - 1)
			return (100000);
	}
	if (p && p->distance > (cube->ypos - y) / sin(a * M_PI / 1800))
	{
		p->distance = (cube->ypos - y) / sin(a * M_PI / 1800);
		p->texture = cube->textures[1 + s];
		p->x = (x % 1000) * p->texture->width / 1000;
	}
	return ((cube->ypos - y) / sin(a * M_PI / 1800));
}

float	ft_nextwall_x(float a, t_cube *cube, int s, t_point *p)
{
	int		y;
	int		x;

	if (a == 900 || a == 2700)
		return (100000);
	if (a < 900 || a > 2700)
		s = 0;
	x = cube->xpos + s * (cube->xpos % 1000) + (1 + s) * (1000 - cube->xpos % 1000);
	y = cube->ypos - (x - cube->xpos) * tan(a * M_PI / 1800);
	if (!x || x / 1000 > cube->mapwidth - 1 || y / 1000 < 0 || y / 1000 > cube->mapheight - 1)
		return (100000);
	while (cube->map[y / 1000][x / 1000 + s] == '0' || (cube->map[y / 1000][x / 1000 + s] == 'D' && abs(cube->xpos - x) < 1000 && abs(cube->ypos / 1000 - y / 1000) <= 1))
	{
		x += (1 + 2 * s) * 1000;
		y = cube->ypos - (x - cube->xpos) * tan(a * M_PI / 1800);
		if (!x || x / 1000 > cube->mapwidth - 1 || y / 1000 < 0 || y / 1000 > cube->mapheight - 1)
			return (100000);
	}
	if (p && p->distance > (x - cube->xpos) / cos(a * M_PI / 1800))
	{
		p->distance = (x - cube->xpos) / cos(a * M_PI / 1800);
		p->texture = cube->textures[3 + s];
		p->x = (y % 1000) * p->texture->width / 1000;
	}
	return ((x - cube->xpos) / cos(a * M_PI / 1800));
}


void	ft_displayme(t_cube *cube, int size)
{
	int	a[2];
	int	b[2];
	int	i;
	int	j;
	float	distance;

	a[0] = cube->xpos * cube->imap->width / (1000 * cube->mapwidth);
	a[1] = cube->ypos * cube->imap->height / (1000 * cube->mapheight);
	i = - size;
	while(i <= size)
	{
		j = - size;
		while(j <= size)
			mlx_put_pixel(cube->imap, a[0] + i, a[1] + j++, 0xFF0000FF);
		i++;
	}
	distance = ft_min(ft_nextwall_y((float)cube->angle, cube, 0, 0), ft_nextwall_x((float)cube->angle, cube, -1, 0));
	distance *= (float) cube->imap->width / (1000 * (float) cube->mapwidth);
	b[0] = a[0] + round(distance * cos(cube->angle * M_PI / 1800));
	b[1] = a[1] - round(distance * sin(cube->angle * M_PI / 1800));
	drawline(cube->imap, a, b);
}

void	ft_mapsize(t_cube	*cube, int res[2])
{
	int	mapsize[2];

	if (cube->mlx->width / cube->mlx->height > cube->mapwidth / cube->mapheight)
	{
		mapsize[1] = cube->mlx->height / 2;
		mapsize[0] = mapsize[1] * cube->mapwidth / cube->mapheight;
	}
	else
	{
		mapsize[0] = cube->mlx->width / 2;
		mapsize[1] = mapsize[0] * cube->mapheight / cube->mapwidth;
	}
	if (res)
	{
		res[0] = mapsize[0];
		res[1] = mapsize[1];
	}
	else
	{
		mlx_resize_image(cube->image, cube->mlx->width, cube->mlx->height);
		mlx_resize_image(cube->imap, mapsize[0], mapsize[1]);
		cube->resize = false;
	}
}

void	ft_displaymap(void *param)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	i;
	uint32_t	j;
	t_cube		*cube;

	cube = (t_cube *) param;
	if (cube->resize)
		ft_mapsize(cube, 0);
	y = -1;
	while (++y < cube->imap->height)
	{
		x = -1;
		while (++x < cube->imap->width)
		{
			i = x * cube->mapwidth / cube->imap->width;
			j = y * cube->mapheight / cube->imap->height;
			if (cube->map[j][i] == ' ' || !x || !y || (x + 1) * cube->mapwidth / cube->imap->width > i || (y + 1) * cube->mapheight / cube->imap->height > j)
				mlx_put_pixel(cube->imap, x, y, 0xFFFFFF00);
			else if (cube->map[j][i] == '1')
				mlx_put_pixel(cube->imap, x, y, 0xFFFFFFFF);
			else if (cube->map[j][i] == '0')
				mlx_put_pixel(cube->imap, x, y, 0x000000FF);
			else if (cube->map[j][i] == 'D')
				mlx_put_pixel(cube->imap, x, y, 0xDEB887FF);
		}
	}
	ft_displayme(cube, cube->imap->width / (100 * cube->mapwidth));
}

uint32_t	ft_color(uint32_t param)
{
	uint8_t		*rgb;
	uint32_t	res;

	rgb = (uint8_t *)&param;
	res = (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | rgb[3]);
	return (res);
}

void	ft_drawcol(t_cube *cube,t_point point, uint32_t x)
{
	int			height;
	int			i;
	uint32_t	y;
	int			h;

	height = 2 * cube->image->height * atan(500 / point.distance) * 2 * cube->mlx->width / (cube->mlx->height * M_PI);
	i = -1;
	while (++i < height)
	{
		y = ((int) cube->image->height - height) / 2 + i;
		h = i * point.texture->height / height;
		if (y >= 0 && y < cube->image->height)
			mlx_put_pixel(cube->image, x, y, ft_color(((uint32_t *)point.texture->pixels)[point.x + h * point.texture->width]));
	}
}

void	ft_displayworld(void *param)
{
	t_cube		*cube;
	uint32_t	x;
	float		angle;
	t_point		point;

	cube = (t_cube *) param;
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

void	ft_displaybackground(void *param)
{
	uint32_t	x;
	uint32_t	y;
	t_cube		*cube;

	cube = (t_cube *) param;
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

void ft_graphic(t_cube *cube)
{
	int	mapsize[2];

	cube->map = cube->utils.map;
	cube->mapwidth = cube->utils.lenght;
	cube->mapheight = cube->utils.height;
	cube->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	textinit(cube);
	cube->image = mlx_new_image(cube->mlx, cube->mlx->width, cube->mlx->height);
	ft_mapsize(cube, mapsize);
	cube->imap = mlx_new_image(cube->mlx, mapsize[0], mapsize[1]);
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	mlx_image_to_window(cube->mlx, cube->imap, 0, 0);
	mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(cube->mlx, ft_displaybackground, cube);
	mlx_loop_hook(cube->mlx, ft_displayworld, cube);
	mlx_loop_hook(cube->mlx, ft_displaymap, cube);
	mlx_loop_hook(cube->mlx, ft_hook, cube);
	mlx_resize_hook(cube->mlx, ft_resizehook, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
	cube->mlx = 0;
}