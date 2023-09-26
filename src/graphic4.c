/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   graphic4.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ale-roux <ale-roux@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/08/23 21:19:57 by ale-roux		  #+#	#+#			 */
/*   Updated: 2023/09/26 03:06:44 by ale-roux		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../include/cube.h"

void	animated_init1(t_cube *cube)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("images/sprite/f-respect-1.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[0] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-2.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[1] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-3.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[2] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-4.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[3] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	animated_init2(cube);
}

void	start_anim(t_cube *cube)
{
	mlx_resize_image(cube->animation[cube->anim - 1], WIDTH, HEIGHT);
	mlx_image_to_window(cube->mlx, cube->animation[cube->anim - 1], 0, 0);
	cube->animation[cube->anim - 1]->enabled = true;
	cube->anim++;
	if (cube->anim == 23)
	{
		mlx_image_to_window(cube->mlx, cube->image, 0, 0);
		mlx_image_to_window(cube->mlx, cube->imap, 0, 0);
		cube->anim = 0;
	}
}

void	hook_animation(void *param)
{
	static double	fps = 0;
	t_cube			*cube;

	cube = (t_cube *)param;
	if (mlx_get_time() < fps + 0.06)
		return ;
	fps = mlx_get_time();
	if (!cube->anim)
		return ;
	start_anim(cube);
}
