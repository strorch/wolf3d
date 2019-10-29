/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:53:25 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/19 19:53:27 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_cast		get_cast(t_floor_obj tfo, t_vec pos, t_cast cast)
{
	cast.hit = 0;
	cast.delta_dist.x = fabs(1 / tfo.raydir.x);
	cast.delta_dist.y = fabs(1 / tfo.raydir.y);
	if (tfo.raydir.x < 0)
	{
		cast.step.x = -1;
		cast.side_dist.x = (pos.x - tfo.map.x) * cast.delta_dist.x;
	}
	else
	{
		cast.step.x = 1;
		cast.side_dist.x = (tfo.map.x + 1.0 - pos.x) * cast.delta_dist.x;
	}
	if (tfo.raydir.y < 0)
	{
		cast.step.y = -1;
		cast.side_dist.y = (pos.y - tfo.map.y) * cast.delta_dist.y;
	}
	else
	{
		cast.step.y = 1;
		cast.side_dist.y = (tfo.map.y + 1.0 - pos.y) * cast.delta_dist.y;
	}
	return (cast);
}

static t_floor_obj	process_tfo(t_floor_obj tfo,
									t_game game, t_vec pos, t_cast cast)
{
	while (cast.hit == 0)
	{
		if (cast.side_dist.x < cast.side_dist.y)
		{
			cast.side_dist.x += cast.delta_dist.x;
			tfo.map.x += cast.step.x;
			tfo.side = 0;
		}
		else
		{
			cast.side_dist.y += cast.delta_dist.y;
			tfo.map.y += cast.step.y;
			tfo.side = 1;
		}
		if (game.map->keys[(int)tfo.map.x][(int)tfo.map.y] > 0)
			cast.hit = 1;
	}
	if (tfo.side == 0)
		tfo.p_w_d = (tfo.map.x - pos.x + (1 - cast.step.x) / 2) / tfo.raydir.x;
	else
		tfo.p_w_d = (tfo.map.y - pos.y + (1 - cast.step.y) / 2) / tfo.raydir.y;
	tfo.line_height = (int)(SCREEN_H / tfo.p_w_d);
	tfo.draw_start = -tfo.line_height / 2 + SCREEN_H / 2;
	tfo.draw_end = tfo.line_height / 2 + SCREEN_H / 2;
	return (tfo);
}

static t_floor_obj	process_tfo_last(t_floor_obj tfo,
									t_game game, t_vec pos, t_cast cast)
{
	tfo = process_tfo(tfo, game, pos, cast);
	if (tfo.draw_start < 0)
		tfo.draw_start = 0;
	if (tfo.draw_end >= SCREEN_H)
		tfo.draw_end = SCREEN_H - 1;
	return (tfo);
}

int					*get_pixels_map(t_game *game_h)
{
	t_game		game;
	int			*res_map;
	t_floor_obj tfo;
	t_cast		cast;

	game = *game_h;
	res_map = (int *)ft_memalloc(SCREEN_W * SCREEN_H * sizeof(int));
	tfo.x = -1;
	while (++tfo.x < SCREEN_W)
	{
		tfo.raydir.x = game.user->cam.dir.x
				+ game.user->cam.plane.x * (2 * tfo.x / (double)SCREEN_W - 1);
		tfo.raydir.y = game.user->cam.dir.y
				+ game.user->cam.plane.y * (2 * tfo.x / (double)SCREEN_H - 1);
		tfo.map.x = (int)game.user->cam.pos.x;
		tfo.map.y = (int)game.user->cam.pos.y;
		tfo.pos = game.user->cam.pos;
		cast = get_cast(tfo, tfo.pos, cast);
		tfo = process_tfo_last(tfo, game, tfo.pos, cast);
		tfo = draw_textures(tfo, &res_map, game);
		draw_floor(tfo, &res_map, game);
	}
	game.user->cam.mv_speed = 12000.0 / CLOCKS_PER_SEC * 5.0;
	game.user->cam.rot_speed = 12000.0 / CLOCKS_PER_SEC * 3.0;
	return (res_map);
}
