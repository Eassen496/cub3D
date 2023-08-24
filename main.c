/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:19:57 by ale-roux          #+#    #+#             */
/*   Updated: 2023/08/23 21:46:14 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    init(char *arg)
{
    t_cube  cube;
    int     fd;
    char    *line;
    int     i;

    cube = (t_cube *)malloc(1 * sizeof(t_cube));
    if (!cube)
        return ;
    cube->source = (t_source *)malloc(1 * sizeof(t_source));
    if (!cube->source)
    {
        free(cube);
        return ;
    }
    while (i < 6)
    {
        line = get_next_line(fd);
        if (ft_strncmp(line, "NO ", 3) && cube->source.north == NULL)
        {
            cube->source.north = ft_strdup(ft_strchr(line, '.'));
            i++;
        }
        else if (ft_strncmp(line, "SO ", 3) && cube->source.south == NULL)
        {
            cube->source.south = ft_strdup(ft_strchr(line, '.'));
            i++;
        }
        else if (ft_strncmp(line, "WE ", 3) && cube->source.west == NULL)
        {
            cube->source.west = ft_strdup(ft_strchr(line, '.'));
            i++;
        }
        else if (ft_strncmp(line, "EA ", 3) && cube->source.east == NULL)
        {
            cube->source.east = ft_strdup(ft_strchr(line, '.'));
            i++;
        }
        else if (ft_strncmp(line, "F ", 2) && cube->source.floor == NULL)
        {
            cube->source.floor = ft_strdup(ft_strchr(line, '.'));
            i++;
        }
        else if (ft_strncmp(line, "C ", 2) && cube->source.ceiling == NULL)
        {
            cube->source.ceiling = ft_strdup(ft_strchr(line, '.'));
            i++;
        }
        free(line);
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
        init(argv[1]);
    else
    {
        printf("ARG ERROR\n");
        return (1);
    }
}
