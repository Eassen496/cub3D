/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitonti <abitonti@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:41:41 by ale-roux          #+#    #+#             */
/*   Updated: 2023/09/09 23:43:45 by abitonti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

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
