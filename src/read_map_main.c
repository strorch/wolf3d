/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:25:24 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/29 22:25:25 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void		free_util_map(t_util_map *ms)
{
	free_trible_pointer(ms->ch_keys, ms->map_sz);
	ft_memdel((void **)&ms->map_sz);
	ft_memdel((void **)&ms);
}

static t_map	*map_init(t_util_map *ms, int **keys)
{
	t_map	*map;

	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		return (NULL);
	map->h = ms->map_sz->x;
	map->w = ms->map_sz->y;
	map->keys = keys;
	return (map);
}

static t_user	*init_user(t_vec *user_pos)
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

static t_vec	*read_map(t_game **game_h, char *fname)
{
	t_game			*game;
	int				**keys;
	t_vec			*user_pos;
	t_util_map		*ms;

	game = *game_h;
	if (!(ms = get_main_struct(fname)))
		return (NULL);
	if (!(keys_validation(ms->ch_keys, ms->map_sz)))
		exit_message("Keys is not valid");
	if (!(keys = tranform_to_int(ms->ch_keys, ms->map_sz)))
		exit_message("Parsing unexpected error");
	if (!(user_pos = find_user_pos(ms->ch_keys, ms->map_sz)))
		exit_message("User search error");
	if (!(game->map = map_init(ms, keys)))
		exit_message("Error while map initialization");
	free_util_map(ms);
	return (user_pos);
}

t_game			*init_game(char *fname)
{
	t_game	*game;
	t_vec	*user_pos;

	if (!(game = (t_game *)ft_memalloc(sizeof(t_game))))
		return (NULL);
	if (!(user_pos = read_map(&game, fname)))
		exit_message("Error while file parsing");
	if (!(game->user = init_user(user_pos)))
		exit_message("Error while user defining");
	ft_memdel((void **)&user_pos);
	if (!(game->text = get_textures()))
		exit_message("Error while textures defining");
	return (game);
}
