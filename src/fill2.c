/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/26 04:21:25 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

uint32_t	ft_source_filling(char *line, t_cube *cube)
{
	int			*ret;
	int			i;
	int			j;
	int			save;

	i = 0;
	j = 0;
	ret = (int *)malloc(3 * sizeof(int));
	if (!ret)
		return (0);
	ret[0] = 0;
	ret[1] = 0;
	ret[2] = 0;
	while (line[i] > '9' || line[i] < '0')
		i++;
	save = i;
	while (line[i] <= '9' && line[i] >= '0')
		ret[j] = (ret[j] * 10) + line[i++] - 48;
	if (i == save)
		ret[j] = -1;
	i++;
	save = i;
	j++;
	while (line[i] <= '9' && line[i] >= '0')
		ret[j] = (ret[j] * 10) + line[i++] - 48;
	if (i == save)
		ret[j] = -1;
	j++;
	i++;
	save = i;
	while (line[i] <= '9' && line[i] >= '0')
		ret[j] = (ret[j] * 10) + line[i++] - 48;
	if (i == save)
		ret[j] = -1;
	if (ret[0] == -1 || ret[1] == -1 || ret[2] == -1)
	{
		cube->utils.i = 7;
		return (0);
	}
	return (ft_uint32(ret[0], ret[1], ret[2], ret));
}
