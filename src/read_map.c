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
	if (!(splitted_size = ft_strsplit(size_str, ' ')))
		return NULL;

	for (int i = 0; splitted_size[i] != 0; i++) {
		printf("%i - %s\n", i, splitted_size[i]);
	}
	printf("num - %i\n", str_array_size(splitted_size));

	if (str_array_size(splitted_size) != 2) {
		return (NULL);
	}
	printf("num - %i\n", str_array_size(splitted_size));
	if (!(size = (t_vec *)ft_memalloc(sizeof(t_vec))))
		return NULL;
	size->x = ft_atoi(splitted_size[0]);
	size->y = ft_atoi(splitted_size[1]);
	if (size->x < 3 || size->y < 3)
		return NULL;
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
		printf("KEK1\n");
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
//		printf("%i %f %s  ", res_fd, map_sz->x, str);
//		printf("\n%s\n", str);
		if (res_fd == -1) {
			return (NULL);
		}
		else if (res_fd == 0) {
			break;
		}
		else if (!(res[i] = set_line(str, (int)map_sz->y)))
			exit_message("Wrong map length");
		i++;
	}
	if (map_sz->x != i)
		exit_message("Alloc error");
	return (res);
}

void			borders_check(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->h)
		if (map->keys[i][0] == 0 || map->keys[i][map->w - 1] == 0)
			exit_message("Borders have 0");
	i = -1;
	while (++i < map->w)
		if (map->keys[map->h - 1][i] == 0 || map->keys[0][i] == 0)
			exit_message("Borders have 0");
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
	if (fd == -1)
		exit_message("file does not exist");
	if (!(map_sz = get_map_size(fd)))
		exit_message("Wrong map sizes");
	printf("SIZE RES = %i %i\n", (int)map_sz->x, (int)map_sz->y);
	if (!(keys = readf(fd, map_sz)) || !(map = (t_map *)ft_memalloc(sizeof(t_map))))
		exit_message("Map parse error");
	map->h = map_sz->x;
	map->w = map_sz->y;
	map->keys = keys;
	printf("HERE\n");
	borders_check(map);
	ft_memdel((void **)&map_sz);
	return (map);
}
