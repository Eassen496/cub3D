/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:11:39 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/25 00:46:32 by ale-roux         ###   ########.fr       */
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
# define HEIGHT 900
# define WIDTH 1200

typedef struct s_utils
{
	int		i;
	int		lenght;
	int		height;
	bool	floor;
	bool	ceiling;
	bool	mouse;
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

typedef struct s_point
{
	float			distance;
	int				x;
	mlx_image_t		*texture;
}					t_point;

typedef struct s_cube
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_source		*source;
	t_utils			utils;
	int				mw;
	int				mh;
	mlx_image_t		*imap;
	char			**map;
	int				xpos;
	int				ypos;
	int				angle;
	mlx_image_t		*textures[4];
	bool			resize;
}					t_cube;

char		*get_next_line(int fd);
void		ft_graphic(t_cube *cube);
int			ft_freeall(t_cube *cube, char *str);
uint32_t	uintfree(int one, int two, int tree);
uint32_t	ft_uint32(int one, int two, int tree, int *tab);
int			ft_strlen(char *str);
void		*ft_calloc(int memory);
char		*tmpstr(t_cube *cube);
char		*ft_strdup(char *s1);
char		*ft_strrchr(char *s, int c);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, int n);
void		free_strjoin(char *s1, char *s2, int opt);
char		*empty_malloc(char *s1, char *s2, int opt);
char		*cube_strjoin(char *s1, char *s2, int opt);
char		*mapsplit(char *map, int lenght);
int			ft_charfind(char *str, char c);
void		*null_free(t_cube *cube);
void		*nullreturn(int i);
int			ft_open(char *arg);
void		*fdfree(t_cube *cube);
void		finish_all(t_cube *cube);
void		source_fill2(char *line, t_cube *cube);
void		source_fill(char *line, t_cube *cube);
int			map_verif_bis(int x, int y, char **map);
int			map_verif(char **map, int max_y, int max_x, t_cube *cube);
int			map_formator(t_cube *cube, char *map);
void		map_calculator(t_cube *cube, char *map);
int			ft_freeall(t_cube *cube, char *str);
t_source	*struct_init(t_cube *cube);
int			startpos(t_cube *cube, int x, int y);
uint32_t	ft_source_filling(char *line);
float		ft_min(float a, float b);
float		ft_max(float a, float b);

#endif