/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/24 01:17:11 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

char	*cube_strjoin(char *s1, char *s2, int opt)
{
	int		i;
	int		x;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	x = ft_strlen(s2);
	if ((i == 0 && x == 0) || s2[0] == '\n')
		return (empty_malloc(s1, s2, opt));
	str = (char *) malloc((i + x + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	x = 0;
	while (s1[x])
		str[i++] = s1[x++];
	x = 0;
	while (s2[x])
		str[i++] = s2[x++];
	str[i] = '\0';
	free_strjoin(s1, s2, opt);
	return (str);
}

char	*mapsplit(char *map, int lenght)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((lenght + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (map[i] != '\n' && map[i] != '\0')
	{
		str[i] = map[i];
		i++;
	}
	while (i < lenght)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_charfind(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	*null_free(t_cube *cube)
{
	free(cube);
	return (NULL);
}

void	*nullreturn(int i)
{
	(void) i;
	return (NULL);
}
