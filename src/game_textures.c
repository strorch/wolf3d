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

t_floor_obj		draw_textures(t_floor_obj o, int **res_map_h, t_game game)
{
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		y;
	int		color;
	int		d;
	int		*res_map;

	res_map = *res_map_h;
	tex_num = game.map->keys[(int)o.map.x][(int)o.map.y] - 1;
	if (o.side == 0)
		wall_x = o.pos.y + o.p_w_d * o.raydir.y;
	else
		wall_x = o.pos.x + o.p_w_d * o.raydir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)T_WIDTH);
	if (o.side == 0 && o.raydir.x > 0)
		tex_x = T_WIDTH - tex_x - 1;
	if (o.side == 1 && o.raydir.y < 0)
		tex_x = T_WIDTH - tex_x - 1;
	y = o.draw_start - 1;
	while (++y < o.draw_end)
	{
		d = y * 256 - SCREEN_H * 128 + o.line_height * 128;
		tex_y = ((d * T_HEIGHT) / o.line_height) / 256;
		color = game.text[tex_num][T_HEIGHT * tex_y + tex_x];
		if (o.side == 1)
			color = (color >> 1) & 8355711;
		res_map[SCREEN_H * y + o.x] = color;
	}
	o.y = y;
	o.wall_x = wall_x;
	return (o);
}
