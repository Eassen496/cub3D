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
