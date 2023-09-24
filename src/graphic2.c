/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:17:43 by abitonti          #+#    #+#             */
/*   Updated: 2023/09/25 00:57:02 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	drawline(mlx_image_t *image, int *a, int *b)
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

int	ft_nextwhile_y(int x, int y, int s, t_cube *c)
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

int	ft_nextwhile_x(int x, int y, int s, t_cube *c)
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
