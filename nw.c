void	map_calculator(t_cube *cube)
{
	int		i;
	size_t	lenght;

	i = 0;
	while (cube->utils->map[i])
	{
		lenght = 0;
		while (cube->utils->map[i++] != '\n' && cube->utils->map[i])
			lenght++;
		if (cube->utils->lenght < lenght)
			cube->utils->lenght = lenght;
		cube->utils->height++;
		i++;
	}
}

t_source	*struct_init(t_cube *cube)
{
	t_source *source;

	source = (t_source *)malloc(1 * sizeof(t_source));
	if (!source)
	{
		free(cube);
		return (NULL);
	}
	cube->utils.i = 0;
	cube->utils.lenght = 0;
	cube->utils.height = 0;
	source->north = NULL;
	source->south = NULL;
	source->east = NULL;
	source->west = NULL;
	source->floor = NULL;
	source->ceiling = NULL;
	return (source);
}

char    *tmpstr(t_cube cube)
{
    char    *map;

    map = ft_calloc(1);
    if (!map)
	{
		free(source);
		free(cube);
		return (NULL);
	}
    return (map);
}

void	start(char *arg)
{
	t_cube	*cube;
	int	 	fd;
	char	*line;

	cube = (t_cube *)malloc(1 * sizeof(t_cube));
	if (!cube)
		return ;
	cube->source = struct_init(cube);
	map = tmpstr(cub);
	if (!cube)
		return ;
	fd = ft_open(arg);
	if (fd < 0)
	{
		free(cube->source);
		free(cube);
		printf("Please give a valid file :D\n");
		return ;
	}
	while (cube->utils.i < 6)
	{
		line = get_next_line(fd);
		source_fill(line, cube);
		free(line);
	}
	cube->utils.i = 0;
	line = get_next_line(fd);
	while (line)
	{
		cube->utils.map = cube_strjoin(cube->utils.map, line, 2);
		line = get_next_line(fd);
	}
	//map_calculator(cube);
	printf("%s", cube->utils.map);
}