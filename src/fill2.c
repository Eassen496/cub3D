/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/27 00:55:24 by abitonti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

uint32_t	ft_source_filling(char *line, t_cube *cube)
{
	int			ret[3];
	int			i;
	int			j;
	int			save;

	i = 0;
	j = -1;
	ret[0] = 0;
	ret[1] = 0;
	ret[2] = 0;
	while (++j < 3)
	{
		save = i;
		while (line[i] <= '9' && line[i] >= '0')
			ret[j] = (ret[j] * 10) + line[i++] - 48;
		if (i == save || ret[j] > 255)
			break ;
		if (!((line[i] == ',' && j < 2) || (line[i] == '\n' && j == 2)))
			break ;
		i++;
	}
	if (j < 3)
		return (cube->utils.i = 7);
	return (ret[0] << 24 | ret[1] << 16 | ret[2] << 8 | 255);
}
