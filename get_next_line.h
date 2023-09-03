/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:41:41 by ale-roux          #+#    #+#             */
/*   Updated: 2023/08/29 21:41:42 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct s_line
{
	char			*buff;
	int				start;
	int				end;
	int				i;
	struct s_line	*next;
}	t_line;

char	*get_next_line(int fd);

#endif
