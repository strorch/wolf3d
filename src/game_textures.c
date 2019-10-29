/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:24:36 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/29 19:24:37 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_vec			calc_text_x(double wall_x, t_floor_obj o)
{
	t_vec	tex;

	tex.x = (int)(wall_x * (double)T_WIDTH);
	if (o.side == 0 && o.raydir.x > 0)
		tex.x = T_WIDTH - tex.x - 1;
	if (o.side == 1 && o.raydir.y < 0)
		tex.x = T_WIDTH - tex.x - 1;
	return (tex);
}

int				calc_res_map(t_game game,
						int **res_map_h, t_floor_obj o, t_util_tex ut)
{
	int		color;
	int		d;
	int		y;
	int		*res_map;

	res_map = *res_map_h;
	y = o.draw_start - 1;
	while (++y < o.draw_end)
	{
		d = y * 256 - SCREEN_H * 128 + o.line_height * 128;
		ut.tex.y = ((d * T_HEIGHT) / o.line_height) / 256;
		color = game.text[ut.tex_num][(int)(T_HEIGHT * ut.tex.y + ut.tex.x)];
		if (o.side == 1)
			color = (color >> 1) & 8355711;
		res_map[SCREEN_H * y + o.x] = color;
	}
	return (y);
}

t_floor_obj		draw_textures(t_floor_obj o, int **res_map_h, t_game game)
{
	t_util_tex ut;

	ut.tex_num = game.map->keys[(int)o.map.x][(int)o.map.y] - 1;
	if (o.side == 0)
		ut.wall_x = o.pos.y + o.p_w_d * o.raydir.y;
	else
		ut.wall_x = o.pos.x + o.p_w_d * o.raydir.x;
	ut.wall_x -= floor(ut.wall_x);
	ut.tex = calc_text_x(ut.wall_x, o);
	o.y = calc_res_map(game, res_map_h, o, ut);
	o.wall_x = ut.wall_x;
	return (o);
}
