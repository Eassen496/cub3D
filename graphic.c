/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:17:43 by abitonti          #+#    #+#             */
/*   Updated: 2023/09/20 07:10:51 by ale-roux         ###   ########.fr       */
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
	mx = HEIGHT / 2;
	my = WIDHT / 2;
	mlx_get_mouse_pos(cube->mlx, &mx, &my);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_SUPER))
		speed = 0.5;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_SHIFT))
		speed = 2.5;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
	{
		dy -= round(5 * sin(cube->angle * M_PI / 1800) * speed);
		dx += round(5 * cos(cube->angle * M_PI / 1800) * speed);
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
	{
		dy += round(5 * sin(cube->angle * M_PI / 1800) * speed);
		dx -= round(5 * cos(cube->angle * M_PI / 1800) * speed);
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
	{
		dy -= round(5 * cos(cube->angle * M_PI / 1800) * speed);
		dx -= round(5 * sin(cube->angle * M_PI / 1800) * speed);
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
	{
		dy += round(5 * cos(cube->angle * M_PI / 1800));
		dx += round(5 * sin(cube->angle * M_PI / 1800));
	}
	if (dx > 0  && (cube->map[cube->ypos / 100][(cube->xpos + 20) / 100] == '0' || cube->map[cube->ypos / 100][(cube->xpos + 20) / 100] == 'D'))
		cube->xpos += dx;
	if (dx < 0  && (cube->map[cube->ypos / 100][(cube->xpos - 20) / 100] == '0' || cube->map[cube->ypos / 100][(cube->xpos - 20) / 100] == 'D'))
		cube->xpos += dx;
	if (dy > 0  && (cube->map[(cube->ypos + 20) / 100][cube->xpos / 100] == '0' || cube->map[(cube->ypos + 20) / 100][cube->xpos / 100] == 'D'))
		cube->ypos += dy;
	if (dy < 0  && (cube->map[(cube->ypos - 20) / 100][cube->xpos / 100] == '0' || cube->map[(cube->ypos - 20) / 100][cube->xpos / 100] == 'D'))
		cube->ypos += dy;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT) || mx < (HEIGHT / 2) - 5)
	{
		cube->angle = (cube->angle + 80) % 3600;
		mlx_set_mouse_pos(cube->mlx, HEIGHT / 2, WIDHT / 2);
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT) || mx > (HEIGHT / 2) + 5)
	{
		cube->angle = (cube->angle + 3520) % 3600;
		mlx_set_mouse_pos(cube->mlx, HEIGHT / 2, WIDHT / 2);
	}
}

void	textinit(t_cube *cube)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (++i < 4)
	{
		cube->textures[i].height = 4;
		cube->textures[i].width = 4;
		cube->textures[i].mat = malloc(cube->textures[i].width * sizeof(uint32_t*));
		x = -1;
		while (++x < cube->textures[i].width)
		{
			y = -1;
			cube->textures[i].mat[x] = malloc(cube->textures[i].height * sizeof(uint32_t));
			while (++y < cube->textures[i].height)
			{
				cube->textures[i].mat[x][y] = 0xFFFFFFFF;
				if ((x + y) % 2)
					cube->textures[i].mat[x][y] = 0x000000FF;
			}
		}
	}
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

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
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

/*float	ft_nextwall_y(float a, t_cube *cube, int s)
{
	int		y;
	int		x;

	if (!a || a == 1800)
		return (10000);
	if (a < 1800)
		s = -1;
	x = cube->xpos;
	y = cube->ypos;
	y += s * (y % 100) + (1 + s) * (100 - y % 100);
	x -= (y - cube->ypos) / tan(a * M_PI / 1800);
	if (!y || y / 100 > cube->mapheight - 1 || x < 0 || x / 100 > cube->mapwidth - 1)
		return (10000);
	while (cube->map[y / 100 + s][x / 100] != '1' && ((cube->map[y / 100 + s][x / 100] != 'D') && ((cube->ypos - y) / sin(a * M_PI / 1800) > 200)))
	{
		y += (1 + 2 * s) * 100;
		x = cube->xpos - (y - cube->ypos) / tan(a * M_PI / 1800);
		if (!y || y / 100 > cube->mapheight - 1 || x < 0 || x / 100 > cube->mapwidth - 1)
			return (10000);
	}
	printf("%d %d\n", x, y);
	return ((cube->ypos - y) / sin(a * M_PI / 1800));
}

float	ft_nextwall_x(float a, t_cube *cube, int s)
{
	int		y;
	int		x;

	if (a == 900 || a == 2700)
		return (10000);
	if (a < 900 || a > 2700)
		s = 0;
	x = cube->xpos;
	y = cube->ypos;
	x += s * (x % 100) + (1 + s) * (100 - x % 100);
	y -= (x - cube->xpos) * tan(a * M_PI / 1800);
	if (!x || x / 100 > cube->mapwidth - 1 || y / 100 < 0 || y / 100 > cube->mapheight - 1)
		return (10000);
	while (cube->map[y / 100][x / 100 + s] != '1' || (cube->map[y / 100][x / 100 + s] != 'D' && (x - cube->xpos) / cos(a * M_PI / 1800) < 200))
	{
		x += (1 + 2 * s) * 100;
		y = cube->ypos - (x - cube->xpos) * tan(a * M_PI / 1800);
		if (!x || x / 100 > cube->mapwidth - 1 || y / 100 < 0 || y / 100 > cube->mapheight - 1)
			return (10000);
	}
	printf("%d %d %f\n", x, y, a);
	return ((x - cube->xpos) / cos(a * M_PI / 1800));
}*/

float	ft_nextwall_y(float a, t_cube *cube, int s, t_point *point)
{
	int		y;
	int		x;

	if (!a || a == 1800)
		return (10000);
	if (a < 1800)
		s = -1;
	x = cube->xpos;
	y = cube->ypos;
	y += s * (y % 100) + (1 + s) * (100 - y % 100);
	x -= (y - cube->ypos) / tan(a * M_PI / 1800);
	if (!y || y / 100 > cube->mapheight - 1 || x < 0 || x / 100 > cube->mapwidth - 1)
		return (10000);
	while (cube->map[y / 100 + s][x / 100] == '0' || ((cube->map[y / 100 + s][x / 100] == 'D') && abs(cube->ypos - y) < 100 && abs(cube->xpos / 100 - x / 100) <= 1))
	{
		y += (1 + 2 * s) * 100;
		x = cube->xpos - (y - cube->ypos) / tan(a * M_PI / 1800);
		if (!y || y / 100 > cube->mapheight - 1 || x < 0 || x / 100 > cube->mapwidth - 1)
			return (10000);
	}
	if (point && point->distance > (cube->ypos - y) / sin(a * M_PI / 1800))
	{
		point->distance = (cube->ypos - y) / sin(a * M_PI / 1800);
		point->height = cube->textures[1 + s].height;
		point->column = cube->textures->mat[cube->textures[1 + s].width * (((-1 - 2 * s) * (x % 100) + 100) % 100) / 100];
	}
	return ((cube->ypos - y) / sin(a * M_PI / 1800));
}

float	ft_nextwall_x(float a, t_cube *cube, int s, t_point *point)
{
	int		y;
	int		x;

	if (a == 900 || a == 2700)
		return (10000);
	if (a < 900 || a > 2700)
		s = 0;
	x = cube->xpos;
	y = cube->ypos;
	x += s * (x % 100) + (1 + s) * (100 - x % 100);
	y -= (x - cube->xpos) * tan(a * M_PI / 1800);
	if (!x || x / 100 > cube->mapwidth - 1 || y / 100 < 0 || y / 100 > cube->mapheight - 1)
		return (10000);
	while (cube->map[y / 100][x / 100 + s] == '0' || (cube->map[y / 100][x / 100 + s] == 'D' && abs(cube->xpos - x) < 100 && abs(cube->ypos / 100 - y / 100) <= 1))
	{
		x += (1 + 2 * s) * 100;
		y = cube->ypos - (x - cube->xpos) * tan(a * M_PI / 1800);
		if (!x || x / 100 > cube->mapwidth - 1 || y / 100 < 0 || y / 100 > cube->mapheight - 1)
			return (10000);
	}
	if (point && point->distance > (x - cube->xpos) / cos(a * M_PI / 1800))
	{
		point->distance = (x - cube->xpos) / cos(a * M_PI / 1800);
		point->height = cube->textures[3 + s].height;
		point->column = cube->textures->mat[cube->textures[3 + s].width * (((1 + 2 * s) * (y % 100) + 100) % 100) / 100];
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
	distance = ft_min(ft_nextwall_y((float)cube->angle, cube, 0, 0), ft_nextwall_x((float)cube->angle, cube, -1, 0));
	printf("%f\n", distance);
	distance *= (float) cube->imap->width / (100 * (float) cube->mapwidth);
	b[0] = a[0] + round(distance * cos(cube->angle * M_PI / 1800));
	b[1] = a[1] - round(distance * sin(cube->angle * M_PI / 1800));
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
				mlx_put_pixel(cube->imap, x, y, 0xFFFFFF00);
			else if (cube->map[j][i] == '1')
				mlx_put_pixel(cube->imap, x, y, 0xFFFFFFFF);
			else if (cube->map[j][i] == '0')
				mlx_put_pixel(cube->imap, x, y, 0x000000FF);
			else if (cube->map[j][i] == 'D')
				mlx_put_pixel(cube->imap, x, y, 0xDEB887FF);
		}
	}
	ft_displayme(cube, cube->imap->width / (10 * cube->mapwidth));
}

void	ft_drawcol(t_cube *cube,t_point point, uint32_t x)
{
	int	height;
	int	i;
	uint32_t	y;

	height = cube->image->height * atan(50 / point.distance) * 8 / (3 * M_PI);
	i = -1;
	while (++i < height)
	{
		y = ((int) cube->image->height - height) / 2 + i;
		if (y >= 0 && y < cube->image->height)
			mlx_put_pixel(cube->image, x, y, point.column[i * point.height / height]);
	}
}

void	ft_displayworld(void *param)
{
	t_cube		*cube;
	uint32_t	x;
	float		angle;
	/*float		distance;
	int			a[2];
	int			b[2];*/
	t_point		point;

	cube = (t_cube *) param;
	x = -1;
	while (++x < cube->image->width)
	{
		point.distance = 10000;
		angle = (cube->angle + 4050 - 900 * x / cube->image->width) % 3600;
		/*distance = ft_min(ft_nextwall_y(angle, cube, 0), ft_nextwall_x(angle, cube, -1));
		a[0] = x;
		b[0] = x;
		a[1] = ft_max(0, cube->image->height * (0.5 - atan(50 / distance) * 8 / (3 * M_PI)));
		b[1] = ft_min(cube->image->height - 1, cube->image->height * (0.5 + atan(50 / distance) * 8 / (3 * M_PI)));
		drawline(cube->image, a, b);*/
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

void ft_graphic(t_cube *cube)
{
	textinit(cube);
	cube->map = cube->utils.map;
	cube->mapwidth = cube->utils.lenght;
	cube->mapheight = cube->utils.height;
	cube->mlx = mlx_init(HEIGHT, WIDHT, "cub3D", 1);
	cube->image = mlx_new_image(cube->mlx, cube->mlx->width, cube->mlx->height);
	cube->imap = mlx_new_image(cube->mlx, cube->mlx->width / 2, cube->mlx->width * cube->mapheight / (cube->mapwidth * 2));
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	mlx_image_to_window(cube->mlx, cube->imap, 0, 0);
	//ft_randomize(cube);
	//mlx_loop_hook(mlx, ft_randomize, mlx);
	//mlx_resize_hook(mlx, ft_resize, );
	//ft_displaymap(cube);
	mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(cube->mlx, ft_displaybackground, cube);
	mlx_loop_hook(cube->mlx, ft_displayworld, cube);
	mlx_loop_hook(cube->mlx, ft_displaymap, cube);
	mlx_loop_hook(cube->mlx, ft_hook, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
}