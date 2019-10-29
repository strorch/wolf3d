/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:44:58 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/29 18:45:00 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static t_vec	get_floor_wall(t_floor_obj o)
{
	t_vec floor_wall;

	if (o.side == 0 && o.raydir.x > 0)
	{
		floor_wall.x = o.map.x;
		floor_wall.y = o.map.y + o.wall_x;
	}
	else if (o.side == 0 && o.raydir.x < 0)
	{
		floor_wall.x = o.map.x + 1.0;
		floor_wall.y = o.map.y + o.wall_x;
	}
	else if (o.side == 1 && o.raydir.y > 0)
	{
		floor_wall.x = o.map.x + o.wall_x;
		floor_wall.y = o.map.y;
	}
	else
	{
		floor_wall.x = o.map.x + o.wall_x;
		floor_wall.y = o.map.y + 1.0;
	}
	return (floor_wall);
}

void			draw_floor(t_floor_obj o, int **res_map_h, t_game game)
{
	int		*res_map;
	t_vec	floor_wall;
	double	dist_wall;
	double	dist_player;
	double	current_dist;
	double	weight;
	t_vec	current_floor;
	t_vec	floor_tex;

	res_map = *res_map_h;
	floor_wall = get_floor_wall(o);
	dist_wall = o.p_w_d;
	dist_player = 0.0;
	if (o.draw_end < 0)
		o.draw_end = SCREEN_H;
	o.y = o.draw_end;
	while (++o.y < SCREEN_H)
	{
		current_dist = SCREEN_H / (2.0 * o.y - SCREEN_H);
		weight = (current_dist - dist_player) / (dist_wall - dist_player);
		current_floor.x = weight * floor_wall.x + (1.0 - weight) * o.pos.x;
		current_floor.y = weight * floor_wall.y + (1.0 - weight) * o.pos.y;
		floor_tex.x = (int)(current_floor.x * T_WIDTH) % T_WIDTH;
		floor_tex.y = (int)(current_floor.y * T_HEIGHT) % T_HEIGHT;
		res_map[SCREEN_H * o.y + o.x] = (game.text[3][(int)(T_WIDTH
						* floor_tex.y + floor_tex.x)] >> 1) & 8355711;
		res_map[SCREEN_H * (SCREEN_H
	- o.y) + o.x] = game.text[6][(int)(T_WIDTH * floor_tex.y + floor_tex.x)];
	}
}
