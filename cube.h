/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:11:39 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/13 03:49:38 by abitonti         ###   ########.fr       */
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

typedef struct s_utils
{
	int		i;
	int		lenght;
	int		height;
	char	**map;
}				t_utils;

typedef struct s_source
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		*floor;
	int		*ceiling;
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
	int			xpos;
	int			ypos;
	int			angle;
}				t_cube;

char	*get_next_line(int fd);
void	ft_graphic(t_cube *cube);

#endif