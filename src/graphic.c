/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:17:43 by abitonti          #+#    #+#             */
/*   Updated: 2023/09/24 03:16:17 by abitonti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_mousehook(double xpos, double ypos, void *param)
{
	t_cube		*c;

	(void) ypos;
	c = (t_cube *) param;
	if (!c->utils.mouse)
		return ;
	if (xpos < c->mlx->width / 2 - 5)
	{
		c->angle = (c->angle + 50) % 3600;
		mlx_set_mouse_pos(c->mlx, c->mlx->width / 2, c->mlx->height / 2);
	}
	if (xpos > c->mlx->width / 2 + 5)
	{
		c->angle = (c->angle + 3550) % 3600;
		mlx_set_mouse_pos(c->mlx, c->mlx->width / 2, c->mlx->height / 2);
	}
}

void	ft_collision(t_cube *c, int dx, int dy)
{
	if (dx > 0 && c->map[c->ypos / 1000][(c->xpos + 200) / 1000] != '1')
		c->xpos += dx;
	if (dx < 0 && c->map[c->ypos / 1000][(c->xpos - 200) / 1000] != '1')
		c->xpos += dx;
	if (dy > 0 && c->map[(c->ypos + 200) / 1000][c->xpos / 1000] != '1')
		c->ypos += dy;
	if (dy < 0 && c->map[(c->ypos - 200) / 1000][c->xpos / 1000] != '1')
		c->ypos += dy;
}

void	ft_move(t_cube *c, float speed, int dx, int dy)
{
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT_SUPER))
		speed = 0.5;
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT_SHIFT))
		speed = 2.5;
	if (mlx_is_key_down(c->mlx, MLX_KEY_W))
	{
		dy -= round(50 * sin(c->angle * M_PI / 1800) * speed);
		dx += round(50 * cos(c->angle * M_PI / 1800) * speed);
	}
	if (mlx_is_key_down(c->mlx, MLX_KEY_S))
	{
		dy += round(50 * sin(c->angle * M_PI / 1800) * speed);
		dx -= round(50 * cos(c->angle * M_PI / 1800) * speed);
	}
	if (mlx_is_key_down(c->mlx, MLX_KEY_A))
	{
		dy -= round(50 * cos(c->angle * M_PI / 1800) * speed);
		dx -= round(50 * sin(c->angle * M_PI / 1800) * speed);
	}
	if (mlx_is_key_down(c->mlx, MLX_KEY_D))
	{
		dy += round(50 * cos(c->angle * M_PI / 1800) * speed);
		dx += round(50 * sin(c->angle * M_PI / 1800) * speed);
	}
	ft_collision(c, dx, dy);
}

void	ft_hook(void *param)
{
	t_cube		*c;

	c = (t_cube *) param;
	if (mlx_is_key_down(c->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(c->mlx);
	ft_move(c, 1, 0, 0);
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT))
		c->angle = (c->angle + 80) % 3600;
	if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT))
		c->angle = (c->angle + 3520) % 3600;
	if (mlx_is_key_down(c->mlx, MLX_KEY_SPACE) && c->utils.mouse == true)
	{
		c->utils.mouse = false;
		mlx_set_cursor_mode(c->mlx, MLX_MOUSE_NORMAL);
	}
	else if (mlx_is_key_down(c->mlx, MLX_KEY_M) && c->utils.mouse == false)
	{
		c->utils.mouse = true;
		mlx_set_cursor_mode(c->mlx, MLX_MOUSE_HIDDEN);
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

int ft_nextwhile_y(int x, int y, int s, t_cube *c)
{
	if (c->map[y / 1000 + s][x / 1000] == '0' ||
		((c->map[y / 1000 + s][x / 1000] == 'D') &&
		abs(c->ypos - y) < 1000 && abs(c->xpos / 1000 - x / 1000) <= 1))
		return (1);
	else
		return (0);
}

float	ft_nextwall_y(float a, t_cube *c, int s, t_point *p)
{
	int		y;
	int		x;

	if (!a || a == 1800)
		return (100000);
	if (a < 1800)
		s = -1;
	y = c->ypos + s * (c->ypos % 1000) + (1 + s) * (1000 - c->ypos % 1000);
	x = c->xpos - (y - c->ypos) / tan(a * M_PI / 1800);
	if (!y || y / 1000 > c->mh - 1 || x < 0 || x / 1000 > c->mw - 1)
		return (100000);
	while (ft_nextwhile_y(x, y, s, c))
	{
		y += (1 + 2 * s) * 1000;
		x = c->xpos - (y - c->ypos) / tan(a * M_PI / 1800);
		if (!y || y / 1000 > c->mh - 1 || x < 0 || x / 1000 > c->mw - 1)
			return (100000);
	}
	if (p && p->distance > (c->ypos - y) / sin(a * M_PI / 1800))
	{
		p->distance = (c->ypos - y) / sin(a * M_PI / 1800);
		p->texture = c->textures[1 + s];
		p->x = (x % 1000) * p->texture->width / 1000;
	}
	return ((c->ypos - y) / sin(a * M_PI / 1800));
}

int ft_nextwhile_x(int x, int y, int s, t_cube *c)
{
	if (c->map[y / 1000][x / 1000 + s] == '0' ||
		(c->map[y / 1000][x / 1000 + s] == 'D' &&
		abs(c->xpos - x) < 1000 && abs(c->ypos / 1000 - y / 1000) <= 1))
		return (1);
	else
		return (0);
}

float	ft_nextwall_x(float a, t_cube *c, int s, t_point *p)
{
	int		y;
	int		x;

	if (a == 900 || a == 2700)
		return (100000);
	if (a < 900 || a > 2700)
		s = 0;
	x = c->xpos + s * (c->xpos % 1000) + (1 + s) * (1000 - c->xpos % 1000);
	y = c->ypos - (x - c->xpos) * tan(a * M_PI / 1800);
	if (!x || x / 1000 > c->mw - 1 || y < 0 || y / 1000 > c->mh - 1)
		return (100000);
	while (ft_nextwhile_x(x, y, s, c))
	{
		x += (1 + 2 * s) * 1000;
		y = c->ypos - (x - c->xpos) * tan(a * M_PI / 1800);
		if (!x || x / 1000 > c->mw - 1 || y < 0 || y / 1000 > c->mh - 1)
			return (100000);
	}
	if (p && p->distance > (x - c->xpos) / cos(a * M_PI / 1800))
	{
		p->distance = (x - c->xpos) / cos(a * M_PI / 1800);
		p->texture = c->textures[3 + s];
		p->x = (y % 1000) * p->texture->width / 1000;
	}
	return ((x - c->xpos) / cos(a * M_PI / 1800));
}


void	ft_displayme(t_cube *c, int size)
{
	int		a[2];
	int		b[2];
	int		i;
	int		j;
	float	distance;

	a[0] = c->xpos * c->imap->width / (1000 * c->mw);
	a[1] = c->ypos * c->imap->height / (1000 * c->mh);
	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
			mlx_put_pixel(c->imap, a[0] + i, a[1] + j++, 0xFF0000FF);
		i++;
	}
	distance = ft_min(ft_nextwall_y(c->angle, c, 0, 0),
			ft_nextwall_x(c->angle, c, -1, 0));
	distance *= (float) c->imap->width / (1000 * (float) c->mw);
	b[0] = a[0] + round(distance * cos(c->angle * M_PI / 1800));
	b[1] = a[1] - round(distance * sin(c->angle * M_PI / 1800));
	drawline(c->imap, a, b);
}

void	ft_mapsize(t_cube	*cube, int res[2])
{
	int	mapsize[2];

	if (cube->mlx->width / cube->mlx->height > cube->mw / cube->mh)
	{
		mapsize[1] = cube->mlx->height / 2;
		mapsize[0] = mapsize[1] * cube->mw / cube->mh;
	}
	else
	{
		mapsize[0] = cube->mlx->width / 2;
		mapsize[1] = mapsize[0] * cube->mh / cube->mw;
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

void	ft_displaymap(t_cube *c, uint32_t x, uint32_t y)
{
	uint32_t	i;
	uint32_t	j;

	if (c->resize)
		ft_mapsize(c, 0);
	while (++y < c->imap->height)
	{
		x = -1;
		while (++x < c->imap->width)
		{
			i = x * c->mw / c->imap->width;
			j = y * c->mh / c->imap->height;
			if (c->map[j][i] == ' ' || !x || !y ||
				(x + 1) * c->mw / c->imap->width > i ||
				(y + 1) * c->mh / c->imap->height > j)
				mlx_put_pixel(c->imap, x, y, 0xFFFFFF00);
			else if (c->map[j][i] == '1')
				mlx_put_pixel(c->imap, x, y, 0xFFFFFFFF);
			else if (c->map[j][i] == '0')
				mlx_put_pixel(c->imap, x, y, 0x000000FF);
			else if (c->map[j][i] == 'D')
				mlx_put_pixel(c->imap, x, y, 0xDEB887FF);
		}
	}
	ft_displayme(c, c->imap->width / (100 * c->mw));
}

uint32_t	ft_color(uint32_t param)
{
	uint8_t		*rgb;
	uint32_t	res;

	rgb = (uint8_t *)&param;
	res = (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | rgb[3]);
	return (res);
}

void	ft_drawcol(t_cube *c,t_point p, uint32_t x)
{
	int			height;
	int			i;
	uint32_t	y;
	int			h;

	height = 2 * c->image->height * atan(500 / p.distance)
		* 2 * c->mlx->width / (c->mlx->height * M_PI);
	i = -1;
	while (++i < height)
	{
		y = ((int) c->image->height - height) / 2 + i;
		h = i * p.texture->height / height;
		if (y >= 0 && y < c->image->height)
			mlx_put_pixel(c->image, x, y, ft_color(((uint32_t *)
						p.texture->pixels)[p.x + h * p.texture->width]));
	}
}

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

void ft_graphic(t_cube *cube)
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
