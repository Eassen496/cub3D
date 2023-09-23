int	ft_open(char *arg)
{
	int	fd;

	if (ft_strcmp(ft_strrchr(arg, '.'), ".cub") != 0)
		return (-1);
	fd = open(arg, O_RDONLY);
	return (fd);
}

void	*fdfree(t_cube *cube)
{
	free(cube->source);
	free(cube);
	printf("Please give a valid file :D\n");
	return (NULL);
}