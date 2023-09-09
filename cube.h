/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:11:39 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/10 00:12:11 by abitonti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "MLX42.h"

typedef struct s_utils
{
	int		i;
	size_t	lenght;
	size_t	height;
	char	*map;
}				t_utils;

typedef struct s_source
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
}				t_source;

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
}				t_cube;

char	*get_next_line(int fd);

#endif