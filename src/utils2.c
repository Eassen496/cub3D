/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/24 01:12:53 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1)
		return (-1);
	while (s1[i] && s1[i] == s2[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && n > 0 && s2[i])
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	free_strjoin(char *s1, char *s2, int opt)
{
	if (opt == 0)
		free(s1);
	if (opt == 1)
		free(s2);
	else if (opt == 2)
	{
		free(s1);
		free(s2);
	}
	return ;
}

char	*empty_malloc(char *s1, char *s2, int opt)
{
	char	*ret;

	ret = (char *)malloc(1 * sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	free_strjoin(s1, s2, opt);
	return (ret);
}
