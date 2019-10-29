/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:44:46 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/29 21:44:48 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	execute_actions(t_app *app, t_event e)
{
	float		w;
	t_camera	c;
	t_vec		d;
	t_vec		p;
	t_vec		pl;

	w = e.m * 0.25;
	c = (*app).game->user->cam;
	d = c.dir;
	p = c.pos;
	pl = c.plane;
	if ((*app).game->map->keys[(int)(p.x +
				d.x * (c.mv_speed + w))][(int)p.y - (int)(d.y * w)] == 0)
		(*app).game->user->cam.pos.x += e.m * d.x * c.mv_speed;
	if ((*app).game->map->keys[(int)p.x -
				(int)(d.x * w)][(int)(p.y + d.y * (c.mv_speed + w))] == 0)
		(*app).game->user->cam.pos.y += e.m * d.y * c.mv_speed;
	(*app).game->user->cam.dir.x = d.x * cos(e.r * c.rot_speed)
				- d.y * sin(e.r * c.rot_speed);
	(*app).game->user->cam.dir.y = d.x * sin(e.r * c.rot_speed)
				+ d.y * cos(e.r * c.rot_speed);
	(*app).game->user->cam.plane.x = pl.x * cos(e.r * c.rot_speed)
				- pl.y * sin(e.r * c.rot_speed);
	(*app).game->user->cam.plane.y = pl.x * sin(e.r * c.rot_speed)
				+ pl.y * cos(e.r * c.rot_speed);
}

void		key_events(SDL_Event *event, t_app *app)
{
	t_event		e;

	e.m = 0;
	e.r = 0;
	(event->K_K == SDL_SCANCODE_ESCAPE) ? exit_message("Done!") : 0;
	(event->K_K == SDL_SCANCODE_UP) ? (e.m = 1) : 0;
	(event->K_K == SDL_SCANCODE_DOWN) ? (e.m = -1) : 0;
	(event->K_K == SDL_SCANCODE_RIGHT) ? (e.r = -1) : 0;
	(event->K_K == SDL_SCANCODE_LEFT) ? (e.r = 1) : 0;
	execute_actions(app, e);
}
