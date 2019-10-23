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
		return (0);
	i = -1;
	while (array[++i] != 0)
		;
	return (i);
}

static t_vec	*get_map_size(const int fd)
{
	t_vec	*size;
	char	*size_str;
	char	**splitted_size;
	int		res;

	res = ft_get_next_line(fd, &size_str);
	if (!(splitted_size = ft_strsplit(size_str, ' ')))
		;
	if (!(size = (t_vec *)ft_memalloc(sizeof(t_vec))))
		;
	if (str_array_size(splitted_size) != 2)
		exit_message("Wrong map sizes");
	size->x = ft_atoi(splitted_size[0]);
	size->y = ft_atoi(splitted_size[1]);
	if (size->x < 3 || size->y < 3)
		exit_message("Wrong map sizes");
	ft_del_str(splitted_size);
	ft_memdel((void **)&size_str);
	return (size);
}

static char		**set_line_arr(const char *str, int sz_alloc)
{
	char	**split;

	if (!(split = ft_strsplit(str, ' ')))
		;
	if (str_array_size(split) != (int)sz_alloc)
		exit_message("Wrong map sizes");
	return (split);
}

static char		***readf(int fd, t_vec *map_sz)
{
	int		i;
	char	*str;
	char	***res;
	int		res_fd;

	i = -1;
	if (!(res = (char ***)ft_memalloc(sizeof(char **) * map_sz->x)))
		;
	while (++i < map_sz->x)
	{
		res_fd = ft_get_next_line(fd, &str);
		if (res_fd == 0)
			break ;
		else if ((res_fd == -1)
					|| !(res[i] = set_line_arr(str, (int)map_sz->y)))
			;
		ft_memdel((void **)&str);
	}
	if (map_sz->x != i)
		exit_message("Alloc error");
	return (res);
}

t_user			*init_user(t_vec *user_pos)
{
	t_user	*user;
	t_vec	dir;
	t_vec	pos;
	t_vec	plane;

	user = (t_user *)ft_memalloc(sizeof(t_user));
	dir.x = -1;
	dir.y = 0;
	pos.x = user_pos->x;
	pos.y = user_pos->y;
	plane.x = 0;
	plane.y = 0.66;
	user->cam.dir = dir;
	user->cam.pos = pos;
	user->cam.plane = plane;
	return (user);
}

static t_vec	*find_user_pos(char ***map, t_vec *map_sz)
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
					;
				pos->x = i;
				pos->y = j;
				return (pos);
			}
	}
	return (NULL);
}

static int		**tranform_to_int(char ***map, t_vec *map_sz)
{
	int		i;
	int		j;
	int		**res;

	if (!(res = (int **)ft_memalloc(sizeof(int *) * map_sz->x)))
		;
	i = -1;
	while (++i < map_sz->x)
	{
		j = -1;
		if (!(res[i] = (int *)ft_memalloc(sizeof(int) * map_sz->y)))
			;
		while (++j < map_sz->y)
			res[i][j] = ft_atoi(map[i][j]);
	}
	return (res);
}

static void		free_trible_pointer(char ***mem, t_vec *map_sz)
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

t_vec			*read_map(t_game **game_h, char *fname)
{
	int				fd;
	t_game			*game;

	t_vec			*map_sz;
	char			***ch_keys;

	int				**keys;

	t_vec			*user_pos;

	t_map			*map;

	game = *game_h;
	fd = open(fname, O_RDONLY);
	if (!(map_sz = get_map_size(fd)))
		;
	if (!(ch_keys = readf(fd, map_sz)))
		;
	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		;
	if (!(keys_validation(ch_keys, map_sz)))
		;
	if (!(keys = tranform_to_int(ch_keys, map_sz)))
		;
	close(fd);
	if (!(user_pos = find_user_pos(ch_keys, map_sz)))
		;
	free_trible_pointer(ch_keys, map_sz);
	map->h = map_sz->x;
	map->w = map_sz->y;
	map->keys = keys;
	ft_memdel((void **)&map_sz);
	game->map = map;
	return (user_pos);
}

t_game			*init_game(char *fname)
{
	t_game	*game;
	t_vec	*user_pos;

	if (!(game = (t_game *)ft_memalloc(sizeof(t_game))))
		;
	if (!(user_pos = read_map(&game, fname)))
		;
	if (!(game->user = init_user(user_pos)))
		;
	ft_memdel((void **)&user_pos);
	if (!(game->text = get_textures()))
		;
	return (game);
}
