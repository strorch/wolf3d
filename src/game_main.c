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

int		*get_pixels_map(t_game *game_h)
{
	clock_t		start;
	clock_t		end;
	double		cpu_time_used;
	t_game		game;
	t_user		user;
	int			*res_map;
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
	int			x;

	game = *game_h;
	user = *game.user;
	start = clock();
	res_map = (int *)ft_memalloc(SCREEN_W * SCREEN_H * sizeof(int));
	pos.x = user.cam.pos.x;
	pos.y = user.cam.pos.y;
	dir.x = user.cam.dir.x;
	dir.y = user.cam.dir.y;
	plane.x = user.cam.plane.x;
	plane.y = user.cam.plane.y;
	x = -1;
	while (++x < SCREEN_W)
	{
		t_vec raydir;
		t_vec side_dist;
		t_vec delta_dist;
		t_vec step;
		t_vec map;
		double perp_wall_dist;
		int hit;
		int side;

		hit = 0;
		raydir.x = dir.x + plane.x * (2 * x / (double)SCREEN_W - 1);
		raydir.y = dir.y + plane.y * (2 * x / (double)SCREEN_H - 1);
		map.x = (int)pos.x;
		map.y = (int)pos.y;
		delta_dist.x = fabs(1 / raydir.x);
		delta_dist.y = fabs(1 / raydir.y);
		if (raydir.x < 0)
		{
			step.x = -1;
			side_dist.x = (pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - pos.x) * delta_dist.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1;
			side_dist.y = (pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - pos.y) * delta_dist.y;
		}
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			if (game.map->keys[(int)map.x][(int)map.y] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map.x - pos.x + (1 - step.x) / 2) / raydir.x;
		else
			perp_wall_dist = (map.y - pos.y + (1 - step.y) / 2) / raydir.y;
		int line_height;
		int draw_start;
		int draw_end;
		line_height = (int)(SCREEN_H / perp_wall_dist);
		draw_start = -line_height / 2 + SCREEN_H / 2;
		draw_end = line_height / 2 + SCREEN_H / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= SCREEN_H)
			draw_end = SCREEN_H - 1;
/*
** texturing calculations
*/
		int tex_num;
		double wall_x;
		tex_num = game.map->keys[(int)map.x][(int)map.y] - 1;
		if (side == 0)
			wall_x = pos.y + perp_wall_dist * raydir.y;
		else
			wall_x = pos.x + perp_wall_dist * raydir.x;
		wall_x -= floor((wall_x));
		int tex_x;
		int tex_y;
		tex_x = (int)(wall_x * (double)T_WIDTH);
		if (side == 0 && raydir.x > 0)
			tex_x = T_WIDTH - tex_x - 1;
		if (side == 1 && raydir.y < 0)
			tex_x = T_WIDTH - tex_x - 1;
		int y;
		int color;
		int d;
		y = draw_start - 1;
		while (++y < draw_end)
		{
			d = y * 256 - SCREEN_H * 128 + line_height * 128;
			tex_y = ((d * T_HEIGHT) / line_height) / 256;
			color = game.text[tex_num][T_HEIGHT * tex_y + tex_x];
			if (side == 1)
				color = (color >> 1) & 8355711;
			res_map[SCREEN_H * y + x] = color;
		}
		draw_floor(side, raydir, map, wall_x, perp_wall_dist, x, y, draw_end, pos, &res_map, game);
	}
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	game.user->cam.mv_speed = cpu_time_used * 5.0;
	game.user->cam.rot_speed = cpu_time_used * 3.0;
	return (res_map);
}
