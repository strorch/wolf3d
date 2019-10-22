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

static t_vec	*find_user_pos(char **map)
{
	return (NULL);
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

void	init_user(t_user **user_h)
{
	t_user	*user;
	t_vec	dir;
	t_vec	pos;
	t_vec	plane;
	app.game->user = (t_user *)ft_memalloc(sizeof(t_user));

	user = *user_h;
	dir.x = -1;
	dir.y = 0;
	pos.x = 2;
	pos.y = 1.5;
	plane.x = 0;
	plane.y = 0.66;
	user->cam.dir = dir;
	user->cam.pos = pos;
	user->cam.plane = plane;
}

int		**get_textures()
{
	int **texture = (int **)ft_memalloc(sizeof(int *) * 8);
	for (int i = 0; i < 8; i++) {
		texture[i] = (int *)ft_memalloc(sizeof(int) * texWidth * texHeight);
	}

	for(int x = 0; x < texWidth; x++)
		for(int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y);
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor;
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			texture[4][texWidth * y + x] = 256 * xorcolor;
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16);
			texture[6][texWidth * y + x] = 65536 * ycolor;
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;
		}
	return texture;
}

void			read_map(char *fname)
{
	t_map			*map;
	t_game			*game;
	int				fd;
	t_vec			*map_sz;
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

	for (int i = 0; i < map_sz->x; i++) {
		for (int j = 0; j < map_sz->y; j++) {
			printf("%s ", ch_keys[i][j]);
		}
		printf("\n");
	}

//	if (!())
	system("leaks wolf3d");
	map->h = map_sz->x;
	map->w = map_sz->y;
//	map->keys = keys;
//	borders_check(map);
	ft_memdel((void **)&map_sz);
	game->map = map;
	exit(1);
}

t_game			*init_game(char *fname)
{
	t_game	*game;

	game = (t_game *)ft_memalloc(sizeof(t_game));
	game->text = get_textures();
	return game;
}
