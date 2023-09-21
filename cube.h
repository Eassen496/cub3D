/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:11:39 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/20 07:12:55 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "MLX42.h"
# define HEIGHT 1600
# define WIDHT 900

typedef struct s_utils
{
	int		i;
	int		lenght;
	int		height;
	bool	floor;
	bool	ceiling;
	char	**map;
}				t_utils;

typedef struct s_source
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	uint32_t	floor;
	uint32_t	ceiling;
}				t_source;


typedef struct s_texture
{
	int			height;
	int			width;
	uint32_t	**mat;
}				t_texture;

typedef struct s_point
{
	float		distance;
	int			height;
	uint32_t	*column;
}				t_point;

typedef struct s_cube
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_source	*source;
	t_utils		utils;
	int			mapwidth;
	int			mapheight;
	mlx_image_t	*imap;
	char		**map;
	int			xpos;
	int			ypos;
	int			angle;
	t_texture	textures[4];
}				t_cube;

char	*get_next_line(int fd);
void	ft_graphic(t_cube *cube);

#endif