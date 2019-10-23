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
	if ((res == -1)
			|| !(splitted_size = ft_strsplit(size_str, ' '))
			|| str_array_size(splitted_size) != 2
			|| !(size = (t_vec *)ft_memalloc(sizeof(t_vec))))
		return (NULL);
	size->x = ft_atoi(splitted_size[0]);
	size->y = ft_atoi(splitted_size[1]);
	if (size->x < 3 || size->y < 3)
		return (NULL);
	ft_del_str(splitted_size);
	ft_memdel((void **)&size_str);
	return (size);
}

static char		**set_line_arr(const char *str, int sz_alloc)
{
	char	**split;

	if (!(split = ft_strsplit(str, ' '))
			|| (str_array_size(split) != (int)sz_alloc))
		return (NULL);
	return (split);
}

static char		***readf(int fd, t_vec *map_sz)
{
	int		i;
	char	*str;
	char	***res;
	int		res_fd;

	i = -1;
	res = (char ***)ft_memalloc(sizeof(char **) * map_sz->x);
	while (++i < map_sz->x)
	{
		res_fd = ft_get_next_line(fd, &str);
		if (res_fd == 0)
			break ;
		else if ((res_fd == -1) || !(res[i] = set_line_arr(str, (int)map_sz->y)))
			return (NULL);
		ft_memdel((void **)&str);
	}
	if (map_sz->x != i)
		exit_message("Alloc error");
	return (res);
}

int				check_border_item(char *item)
{
	return !ft_strcmp(item, "0") || !ft_strcmp(item, "U");
}

int				borders_check(char ***map, t_vec *map_sz)
{
	int i;

	i = -1;
	while (++i < map_sz->x)
		if (check_border_item(map[i][0]) || check_border_item(map[i][(int)map_sz->y - 1]))
			return 0;
	i = -1;
	while (++i < map_sz->y)
		if (check_border_item(map[(int)map_sz->x - 1][i]) || check_border_item(map[0][i]))
			return 0;
	return 1;
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
	return user;
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
				pos = (t_vec *)ft_memalloc(sizeof(t_vec));
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
	int 	**res;

	res = (int **)ft_memalloc(sizeof(int *) * map_sz->x);
	i = -1;
	while (++i < map_sz->x)
	{
		j = -1;
		res[i] = (int *)ft_memalloc(sizeof(int) * map_sz->y);
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
		{
			ft_memdel((void **)&mem[i][j]);
		}
		ft_memdel((void **)&mem[i]);
	}
	ft_memdel((void **)&mem);
}

t_vec			*read_map(t_game **game_h, char *fname)
{
	t_map			*map;
	t_game			*game;
	int				fd;
	int 			**keys;
	t_vec			*map_sz;
	t_vec			*user_pos;
	char			***ch_keys;

	game = *game_h;
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		exit_message("file does not exist");
	if (!(map_sz = get_map_size(fd)))
		exit_message("Wrong map sizes");
	if (!(ch_keys = readf(fd, map_sz))
			|| !(map = (t_map *)ft_memalloc(sizeof(t_map))))
		exit_message("Map parse error");
	if (!(borders_check(ch_keys, map_sz)))
		exit_message("Borders error");
	keys = tranform_to_int(ch_keys, map_sz);
	if (!(user_pos = find_user_pos(ch_keys, map_sz)))
		exit_message("User is not defined");
	free_trible_pointer(ch_keys, map_sz);
	map->h = map_sz->x;
	map->w = map_sz->y;
	map->keys = keys;
	ft_memdel((void **)&map_sz);
	game->map = map;
	return user_pos;
}

t_game			*init_game(char *fname)
{
	t_game	*game;
	t_vec	*user_pos;

	game = (t_game *)ft_memalloc(sizeof(t_game));
	user_pos = read_map(&game, fname);

	printf("USER: %f %f\n", user_pos->x, user_pos->y);

	for (int i = 0; i < game->map->h; i++) {
		for (int j = 0; j < game->map->w; j++) {
			printf("%i ", game->map->keys[i][j]);
		}
		printf("\n");
	}

	game->user = init_user(user_pos);
	ft_memdel((void **)&user_pos);

	game->text = get_textures();

	return game;
}
