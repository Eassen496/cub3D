/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/24 01:12:07 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(int memory)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(memory);
	if (!ptr)
		return (NULL);
	while (i < memory)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char	*tmpstr(t_cube *cube)
{
	char	*map;

	map = ft_calloc(1 * sizeof(char));
	if (!map)
	{
		free(cube->source);
		free(cube);
		return (NULL);
	}
	return (map);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dup;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
