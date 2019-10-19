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

static int		str_array_size(const char **array)
{
	int i;
	int counter;

	i = -1;
	while (array[++i])
		counter++;
	return (counter);
}

static t_vec	*get_map_size(const int fd)
{
	t_vec	*size;
	char	*size_str;
	char	**splitted_size;
	int		res;

	res = ft_get_next_line(fd, &size_str);
	if (res == -1)
		return NULL;
	splitted_size = ft_strsplit(size_str, ' ');
	if (str_array_size((const char **)splitted_size) < 2) {
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

static int		set_line(const char *str, int **line_h, int sz_alloc)
{
	int		*line;
	char	**split;
	int		i;

	line = *line_h;
	if ((split = ft_strsplit(str, ' ')) || (str_array_size((const char **)split) != sz_alloc))
	{

	}
	line = (int *)ft_memalloc(sizeof(int) * sz_alloc);
	i = -1;
	while (++i < sz_alloc)
	{
//TODO: 1
	}
	return 1;
}

static int		**readf(int fd, t_vec *map_sz)
{
	int		i;
	int		j;
	char	*str;
	int		res_fd;
	int		**res;

	i = -1;
	res = (int **)ft_memalloc(sizeof(int *) * map_sz->x);
	while (++i < map_sz->x)
	{
		res_fd = ft_get_next_line(fd, &str);
		if (res_fd == -1)
			return (NULL);
		else if (res_fd == 0)
			free(str);
		else if (set_line(str, &res[i], map_sz->y)) {
//TODO: 1
		}
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
	if (fd == -1)
		return (NULL);
	if (!(map_sz = get_map_size(fd)))
		return (NULL);
	if (!(keys = readf(fd, map_sz)))
		return (NULL);
	map = (t_map *)ft_memalloc(sizeof(t_map));
	map->h = map_sz->x;
	map->w = map_sz->y;
	map->keys = keys;
	ft_memdel((void **)&map_sz);
//TODO: 1

	return (map);
}
