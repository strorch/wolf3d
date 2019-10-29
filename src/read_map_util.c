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

t_vec			*find_user_pos(char ***map, t_vec *map_sz)
{
	int		i;
	int		j;
	t_vec	*pos;

	i = -1;
	while (++i < map_sz->x)
	{
		j = -1;
		while (++j < map_sz->y)
			if (!ft_strcmp(map[i][j], "U"))
			{
				if (!(pos = (t_vec *)ft_memalloc(sizeof(t_vec))))
					return (NULL);
				pos->x = i;
				pos->y = j;
				return (pos);
			}
	}
	return (NULL);
}

int				**tranform_to_int(char ***map, t_vec *map_sz)
{
	int		i;
	int		j;
	int		**res;

	if (!(res = (int **)ft_memalloc(sizeof(int *) * map_sz->x)))
		return (NULL);
	i = -1;
	while (++i < map_sz->x)
	{
		j = -1;
		if (!(res[i] = (int *)ft_memalloc(sizeof(int) * map_sz->y)))
			return (NULL);
		while (++j < map_sz->y)
			res[i][j] = ft_atoi(map[i][j]);
	}
	return (res);
}

void			free_trible_pointer(char ***mem, t_vec *map_sz)
{
	int		i;
	int		j;

	i = -1;
	while (++i < map_sz->x)
	{
		j = -1;
		while (++j < map_sz->y)
			ft_memdel((void **)&mem[i][j]);
		ft_memdel((void **)&mem[i]);
	}
	ft_memdel((void **)&mem);
}

t_util_map		*get_main_struct(char *fname)
{
	int				fd;
	t_vec			*map_sz;
	char			***ch_keys;
	t_util_map		*util_map;

	fd = open(fname, O_RDONLY);
	if (!(map_sz = get_map_size(fd)))
		exit_message("Error while reading sizes");
	if (!(ch_keys = readf(fd, map_sz)))
		exit_message("Error while map parsing");
	if (!(util_map = (t_util_map *)ft_memalloc(sizeof(t_util_map))))
	{
		free_trible_pointer(ch_keys, map_sz);
		ft_memdel((void **)&map_sz);
		return (NULL);
	}
	util_map->ch_keys = ch_keys;
	util_map->map_sz = map_sz;
	close(fd);
	return (util_map);
}
