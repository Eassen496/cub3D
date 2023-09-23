/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/24 01:38:17 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	ft_open(char *arg)
{
	int	fd;

	if (ft_strcmp(ft_strrchr(arg, '.'), ".cub") != 0)
		return (-1);
	fd = open(arg, O_RDONLY);
	return (fd);
}

void	*fdfree(t_cube *cube)
{
	free(cube->source);
	free(cube);
	printf("Please give a valid file :D\n");
	return (NULL);
}
