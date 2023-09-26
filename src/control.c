/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 03:17:43 by abitonti          #+#    #+#             */
/*   Updated: 2023/09/27 00:09:20 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
		speed = 0.75;
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT_SHIFT))
		speed = 3;
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

void	mouse(t_cube *cube, bool state)
{
	cube->utils.mouse = state;
	if (state == false)
		mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_NORMAL);
	else
		mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_HIDDEN);
}

void	ft_hook(void *param)
{
	t_cube		*c;

	c = (t_cube *) param;
	if (mlx_is_key_down(c->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(c->mlx);
	ft_move(c, 1.5, 0, 0);
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT))
		c->angle = (c->angle + 80) % 3600;
	if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT))
		c->angle = (c->angle + 3520) % 3600;
	if (mlx_is_key_down(c->mlx, MLX_KEY_SPACE) && c->utils.mouse == true)
		mouse(c, false);
	else if (mlx_is_key_down(c->mlx, MLX_KEY_M) && c->utils.mouse == false)
		mouse(c, true);
	if (mlx_is_key_down(c->mlx, MLX_KEY_F))
		c->anim = 1;
	if (mlx_is_key_down(c->mlx, MLX_KEY_O))
		c->imap->enabled = false;
	if (mlx_is_key_down(c->mlx, MLX_KEY_P))
		c->imap->enabled = true;
}
