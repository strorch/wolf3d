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
	int			*map;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			w;
	int			h;
	int			x;

	game = *game_h;
	user = *game.user;
	start = clock();
	map = (int *)ft_memalloc(SCREEN_W * SCREEN_H * sizeof(int));
	pos_x = user.cam.pos.x;
	pos_y = user.cam.pos.y;
	dir_x = user.cam.dir.x;
	dir_y = user.cam.dir.y;
	plane_x = user.cam.plane.x;
	plane_y = user.cam.plane.y;
	w = SCREEN_W;
	h = SCREEN_H;
	x = -1;
	while (++x < w)
	{
		double c_x;
		double c_y;
		double raydir_x;
		double raydir_y;
		double side_dist_x;
		double side_dist_y;
		int map_x;
		int map_y;
		double delta_dist_x;
		double delta_dist_y;
		double perp_wall_dist;
		int step_x;
		int step_y;
		int hit;
		int side;

		hit = 0;
		c_x = 2 * x / (double)w - 1;
		c_y = 2 * x / (double)h - 1;
		raydir_x = dir_x + plane_x * c_x;
		raydir_y = dir_y + plane_y * c_y;
		map_x = (int)pos_x;
		map_y = (int)pos_y;
		delta_dist_x = fabs(1 / raydir_x);
		delta_dist_y = fabs(1 / raydir_y);
		if (raydir_x < 0)
		{
			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if (raydir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game.map->keys[map_x][map_y] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / raydir_x;
		else
			perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / raydir_y;
		int line_height;
		int draw_start;
		int draw_end;
		line_height = (int)(h / perp_wall_dist);
		draw_start = -line_height / 2 + h / 2;
		draw_end = line_height / 2 + h / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= h)
			draw_end = h - 1;
/*
** texturing calculations
*/
		int tex_num;
		double wall_x;
		tex_num = game.map->keys[map_x][map_y] - 1;
		if (side == 0)
			wall_x = pos_y + perp_wall_dist * raydir_y;
		else
			wall_x = pos_x + perp_wall_dist * raydir_x;
		wall_x -= floor((wall_x));
		int tex_x;
		int tex_y;
		tex_x = (int)(wall_x * (double)T_WIDTH);
		if (side == 0 && raydir_x > 0)
			tex_x = T_WIDTH - tex_x - 1;
		if (side == 1 && raydir_y < 0)
			tex_x = T_WIDTH - tex_x - 1;
		int y;
		int color;
		int d;
		y = draw_start - 1;
		while (++y < draw_end)
		{
			d = y * 256 - h * 128 + line_height * 128;
			tex_y = ((d * T_HEIGHT) / line_height) / 256;
			color = game.text[tex_num][T_HEIGHT * tex_y + tex_x];
			if (side == 1)
				color = (color >> 1) & 8355711;
			map[SCREEN_H * y + x] = color;
		}
/*
** FLOOR CASTING
*/
		double floor_wall_x;
		double floor_wall_y;
		if (side == 0 && raydir_x > 0)
		{
			floor_wall_x = map_x;
			floor_wall_y = map_y + wall_x;
		}
		else if (side == 0 && raydir_x < 0)
		{
			floor_wall_x = map_x + 1.0;
			floor_wall_y = map_y + wall_x;
		}
		else if (side == 1 && raydir_y > 0)
		{
			floor_wall_x = map_x + wall_x;
			floor_wall_y = map_y;
		}
		else
		{
			floor_wall_x = map_x + wall_x;
			floor_wall_y = map_y + 1.0;
		}
		double dist_wall;
		double dist_player;
		double current_dist;
		dist_wall = perp_wall_dist;
		dist_player = 0.0;
		if (draw_end < 0)
			draw_end = h;
		y = draw_end;
		double weight;
		double current_floor_x;
		double current_floor_y;
		int floor_tex_x;
		int floor_tex_y;
		while (++y < h)
		{
			current_dist = h / (2.0 * y - h);
			weight = (current_dist - dist_player) / (dist_wall - dist_player);
			current_floor_x = weight * floor_wall_x + (1.0 - weight) * pos_x;
			current_floor_y = weight * floor_wall_y + (1.0 - weight) * pos_y;
			floor_tex_x = (int)(current_floor_x * T_WIDTH) % T_WIDTH;
			floor_tex_y = (int)(current_floor_y * T_HEIGHT) % T_HEIGHT;
			map[SCREEN_H * y + x] = (game.text[3][T_WIDTH
					* floor_tex_y + floor_tex_x] >> 1) & 8355711;
			map[SCREEN_H * (h - y) + x] = game.text[6][T_WIDTH
					* floor_tex_y + floor_tex_x];
		}
	}
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	game.user->cam.mv_speed = cpu_time_used * 5.0;
	game.user->cam.rot_speed = cpu_time_used * 3.0;
	return (map);
}
