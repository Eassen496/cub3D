/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/24 01:36:55 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

uint32_t	uintfree(int one, int two, int tree)
{
	int	a;

	a = 255;
	return (one << 24 | two << 16 | tree << 8 | a);
}

uint32_t	ft_uint32(int one, int two, int tree, int *tab)
{
	uint32_t	ret;

	ret = uintfree(one, two, tree);
	free(tab);
	return (ret);
}
