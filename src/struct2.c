/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/26 03:12:51 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	animated_init6(t_cube *cube)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("images/sprite/f-respect-21.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[20] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-22.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[21] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-23.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[22] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
}

void	animated_init5(t_cube *cube)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("images/sprite/f-respect-17.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[16] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-18.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[17] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-19.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[18] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-20.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[19] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	animated_init6(cube);
}

void	animated_init4(t_cube *cube)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("images/sprite/f-respect-13.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[12] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-14.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[13] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-15.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[14] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-16.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[15] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	animated_init5(cube);
}

void	animated_init3(t_cube *cube)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("images/sprite/f-respect-9.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[8] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-10.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[9] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-11.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[10] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-12.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[11] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	animated_init4(cube);
}

void	animated_init2(t_cube *cube)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("images/sprite/f-respect-5.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[4] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-6.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[5] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-7.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[6] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("images/sprite/f-respect-8.png");
	if (!texture && write(2, "Error loading texture file\n", 27))
		exit (ft_freeall(cube, 0));
	cube->animation[7] = mlx_texture_to_image(cube->mlx, texture);
	mlx_delete_texture(texture);
	animated_init3(cube);
}
