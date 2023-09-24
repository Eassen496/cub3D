/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:17:43 by abitonti          #+#    #+#             */
/*   Updated: 2023/09/25 00:51:23 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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

void	ft_drawcol(t_cube *c, t_point p, uint32_t x)
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
