void	finish_all(t_cube *cube)
{
	if (cube->source->north == NULL)
		cube->source->north = ft_calloc(1 * sizeof(char));
	if (cube->source->south == NULL)
		cube->source->south = ft_calloc(1 * sizeof(char));
	if (cube->source->west == NULL)
		cube->source->west = ft_calloc(1 * sizeof(char));
	if (cube->source->east == NULL)
		cube->source->east = ft_calloc(1 * sizeof(char));
}

void	source_fill2(char *line, t_cube *cube)
{
	if (ft_strncmp(line, "F ", 2) == 0 && cube->utils.floor == false)
	{
		cube->source->floor = ft_source_filling(line);
		cube->utils.floor = true;
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && cube->utils.ceiling == false)
	{
		cube->source->ceiling = ft_source_filling(line);
		cube->utils.ceiling = true;
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && cube->source->east == NULL)
	{
		cube->source->east = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
	}
    free(line);
}

void	source_fill(char *line, t_cube *cube)
{
	if (line == NULL)
	{
		cube->utils.i = 7;
		finish_all(cube);
		return ;
	}
	else if (ft_strncmp(line, "NO ", 3) == 0 && cube->source->north == NULL)
	{
		cube->source->north = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && cube->source->south == NULL)
	{
		cube->source->south = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
    }
	else if (ft_strncmp(line, "WE ", 3) == 0 && cube->source->west == NULL)
	{
		cube->source->west = ft_strdup(ft_strchr(line, '.'));
		cube->utils.i++;
	}
	else
		source_fill2(line, cube);
}
