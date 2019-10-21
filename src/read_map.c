/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:53:44 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/19 19:53:46 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		str_array_size(char **array)
{
	int i;

	if (!array)
		return 0;
	i = -1;
	while (array[++i] != 0);
	return (i);
}

static t_vec	*get_map_size(const int fd)
{
	t_vec	*size;
	char	*size_str;
	char	**splitted_size;
	int		res;

	res = ft_get_next_line(fd, &size_str);
	if (res == -1) {
		return NULL;
	}
	splitted_size = ft_strsplit(size_str, ' ');

	for (int i = 0; splitted_size[i] != 0; i++) {
		printf("%i - %s\n", i, splitted_size[i]);
	}
	printf("num - %i\n", str_array_size(splitted_size));

	if (str_array_size(splitted_size) < 2) {
		ft_del_str(splitted_size);
		ft_memdel((void **)&size_str);
		return (NULL);
	}
	size = (t_vec *)ft_memalloc(sizeof(t_vec));
	size->x = ft_atoi(splitted_size[0]);
	size->y = ft_atoi(splitted_size[1]);
	ft_del_str(splitted_size);
	ft_memdel((void **)&size_str);
	return (size);
}

static int		*set_line(const char *str, int sz_alloc)
{
	int		*line;
	char	**split;
	int		i;

	if (!(split = ft_strsplit(str, ' ')) || (str_array_size(split) != (int)sz_alloc)) {
//		printf("KEK1\n");
		return NULL;
	}
//	printf("FUCK\n");
	if (!(line = (int *)ft_memalloc(sizeof(int) * sz_alloc))) {
//		printf("KEK2\n");
		return NULL;
	}
	i = 0;
//	printf("FUCK\n");
	while (i < sz_alloc)
	{
		printf("%s:%i ", split[i], sz_alloc);
        line[i] = ft_atoi(split[i]);
		i++;
	}
	ft_del_str(split);
	for (i = 0; i < sz_alloc; i++) {
		printf("%i:%i ", line[i], i);
	}
    printf("\n");
	return line;
}

static int		**readf(int fd, t_vec *map_sz)
{
	int		i;
	int		j;
	char	*str;
	int		res_fd;
	int		**res;

	i = 0;
	str = NULL;
	res = (int **)ft_memalloc(sizeof(int *) * map_sz->x);
	while (i < map_sz->x)
	{
		if (str)
			ft_memdel((void **)&str);
		res_fd = ft_get_next_line(fd, &str);
		printf("\n%s\n", str);
		if (res_fd == -1)
			return (NULL);
		else if (res_fd == 0)
			break;
		else if (!(res[i] = set_line(str, (int)map_sz->y))) {
			free(str);
			for (int j = 0; j < map_sz->y; j++) {
				printf("a:%i ", res[i][j]);
			}
			printf("\n");
		}
		i++;
	}

	return (res);
}

t_map			*read_map(char **argv)
{
	t_map   		*map;
	int				fd;
	const char		*fname;
	t_vec			*map_sz;
	int				**keys;

	fname = argv[1];
	fd = open(fname, O_RDONLY);
	if (fd == -1) {
		printf("HERE1\n");
		return (NULL);
	}
	if (!(map_sz = get_map_size(fd))) {
		printf("HERE2\n");
		return (NULL);
	}
	printf("SIZE RES = %i %i\n", (int)map_sz->x, (int)map_sz->y);
	if (!(keys = readf(fd, map_sz))) {
		printf("HERE3\n");
		return (NULL);
	}
	printf("OK\n");

	map = (t_map *)ft_memalloc(sizeof(t_map));
	map->h = map_sz->x;
	map->w = map_sz->y;
	map->keys = keys;
	ft_memdel((void **)&map_sz);

	return (map);
}
