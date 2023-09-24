/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/24 02:45:34 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	heeeeeelp(t_cube *cube, int fd, char *map, char *line)
{
	while (cube->utils.i < 6)
	{
		line = get_next_line(fd);
		source_fill(line, cube);
	}
	if (cube->utils.i == 7)
	{
		nullreturn(ft_freeall(cube, map));
		return (1);
	}
	cube->utils.i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map = cube_strjoin(map, line, 2);
		line = get_next_line(fd);
	}
	map_calculator(cube, map);
	if (map_formator(cube, map) == 1)
		return (1);
	return (0);
}

t_cube	*start(char *arg)
{
	t_cube	*cube;
	int		error;
	int		fd;
	char	*map;

	cube = malloc(sizeof(t_cube));
	if (!cube)
		return (NULL);
	cube->source = struct_init(cube);
	map = tmpstr(cube);
	if (!cube->source)
		return (null_free(cube));
	fd = ft_open(arg);
	if (fd < 0)
		return (fdfree(cube));
	error = heeeeeelp(cube, fd, map, NULL);
	if (error == 1)
		return (NULL);
	return (cube);
}

void	print_help(char *exec)
{
	printf("===============================HELP");
	printf("===============================\n");
	printf("|| Name of program: %s\t\t\t\t\t||\n", exec);
	printf("|| launch program : ./%s <*.cub>\t\t\t\t||\n", exec);
	printf("|| Control        :\t\t\t\t\t\t||\n");
	printf("||\t  - [Esc] \t\t: close the program\t\t||\n");
	printf("||\t  - [W]   \t\t: move straight \t\t||\n");
	printf("||\t  - [A]   \t\t: move left\t\t\t||\n");
	printf("||\t  - [S]   \t\t: move back\t\t\t||\n");
	printf("||\t  - [D]   \t\t: move right\t\t\t||\n");
	printf("||\t  - [→]   \t\t: move camera right\t\t||\n");
	printf("||\t  - [←]   \t\t: move camera left\t\t||\n");
	printf("||\t  - [O]   \t\t: hide minimap\t\t\t||\n");
	printf("||\t  - [P]   \t\t: show minimap\t\t\t||\n");
	printf("||\t  - [M]   \t\t: activate mouse\t\t||\n");
	printf("||\t  - [SPACE]   \t\t: desactivate mouse\t\t||\n");
	printf("||\t  - [Left Shift]\t: run\t\t\t\t||\n");
	printf("||\t  - [Left Cmd]\t\t: walk slowly\t\t\t||\n");
	printf("=====================================");
	printf("=============================\n");
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	if (argc == 2)
		cube = start(argv[1]);
	else if (argc == 1)
	{
		print_help(&argv[0][2]);
		return (1);
	}
	else
		return (write(2, "ARG ERROR\n", 10));
	if (cube != NULL)
		ft_graphic(cube);
	else
		return (write(2, "ERROR\n", 6));
	ft_freeall(cube, 0);
	cube = 0;
	system("leaks cub3d");
	return (0);
}
