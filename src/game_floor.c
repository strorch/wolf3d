#include "wolf.h"

void	draw_floor(
		int side,
		t_vec raydir,
		t_vec map,
		double wall_x,
		double perp_wall_dist,
		int x,
		int y,
		int draw_end,
		t_vec pos,
		int **res_map_h,
		t_game game
		)
{
	t_vec floor_wall;
	int *res_map;

	res_map = *res_map_h;
	if (side == 0 && raydir.x > 0)
	{
		floor_wall.x = map.x;
		floor_wall.y = map.y + wall_x;
	}
	else if (side == 0 && raydir.x < 0)
	{
		floor_wall.x = map.x + 1.0;
		floor_wall.y = map.y + wall_x;
	}
	else if (side == 1 && raydir.y > 0)
	{
		floor_wall.x = map.x + wall_x;
		floor_wall.y = map.y;
	}
	else
	{
		floor_wall.x = map.x + wall_x;
		floor_wall.y = map.y + 1.0;
	}
	double dist_wall;
	double dist_player;
	double current_dist;
	dist_wall = perp_wall_dist;
	dist_player = 0.0;
	if (draw_end < 0)
		draw_end = SCREEN_H;
	y = draw_end;
	double weight;
	t_vec current_floor;
	t_vec floor_tex;
	while (++y < SCREEN_H)
	{
		current_dist = SCREEN_H / (2.0 * y - SCREEN_H);
		weight = (current_dist - dist_player) / (dist_wall - dist_player);
		current_floor.x = weight * floor_wall.x + (1.0 - weight) * pos.x;
		current_floor.y = weight * floor_wall.y + (1.0 - weight) * pos.y;
		floor_tex.x = (int)(current_floor.x * T_WIDTH) % T_WIDTH;
		floor_tex.y = (int)(current_floor.y * T_HEIGHT) % T_HEIGHT;
		res_map[SCREEN_H * y + x] = (game.text[3][(int)(T_WIDTH
														* floor_tex.y + floor_tex.x)] >> 1) & 8355711;
		res_map[SCREEN_H * (SCREEN_H - y) + x] = game.text[6][(int)(T_WIDTH
																	* floor_tex.y + floor_tex.x)];
	}
}