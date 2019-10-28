/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:53:34 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/19 19:53:35 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	execute_actions(t_app *app, t_event e)
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

void	key_events(SDL_Event *event, t_app *app)
{
	t_event		e;

	e.m = 0;
	e.r = 0;
	(event->K_K == SDL_SCANCODE_ESCAPE) ? exit_message("Done!\n") : 0;
	(event->K_K == SDL_SCANCODE_UP) ? (e.m = 1) : 0;
	(event->K_K == SDL_SCANCODE_DOWN) ? (e.m = -1) : 0;
	(event->K_K == SDL_SCANCODE_RIGHT) ? (e.r = -1) : 0;
	(event->K_K == SDL_SCANCODE_LEFT) ? (e.r = 1) : 0;
	execute_actions(app, e);
}

void	sdl_events(SDL_Event *e, t_app *app)
{
	while (SDL_PollEvent(e))
	{
		(e->E_TYPE == SDL_KEYDOWN) ? key_events(e, app) : 0;
		(e->E_TYPE == SDL_QUIT) ? exit_message("Done!\n") : 0;
	}
}

t_sdl	*init_sdl(void)
{
	t_sdl *sdl;

	sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit_message("Error in init sdl");
	if (!(sdl->window = SDL_CreateWindow("Wolf3D",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H,
	SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI)))
		exit_message("Error creating window");
	if (!(sdl->rend = SDL_CreateRenderer(sdl->window, -1,
							SDL_RENDERER_ACCELERATED)))
		exit_message("Error in creating renderer");
	if (!(sdl->sur = SDL_CreateRGBSurface(0,
			SCREEN_W, SCREEN_H, 32, 0, 0, 0, 0)))
		exit_message("Error in creating surface");
	return (sdl);
}

char	*handle_args(int argc, char **argv)
{
	char		*tmp_argv;

	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "-h"))
			print_usage();
		tmp_argv = argv[1];
	}
	else
	{
		tmp_argv = (char*)ft_memalloc(sizeof(char) * 15);
		ft_strcpy(tmp_argv, "./maps/2.m");
	}
	return (tmp_argv);
}

int		main(int argc, char **argv)
{
	SDL_Event	event;
	t_sdl		*sdl;
	t_app		app;
	int			*tmp_arr;

	app.file = handle_args(argc, argv);
	if (!(app.game = init_game(app.file)))
		exit_message("Something went wrong");
	app.sdl = init_sdl();
	sdl = app.sdl;
	while (1)
	{
		sdl_events(&event, &app);
		tmp_arr = get_pixels_map(app.game);
		SDL_LockSurface(sdl->sur);
		ft_memcpy(sdl->sur->pixels, tmp_arr, sdl->sur->pitch * sdl->sur->h);
		ft_memdel((void **)&tmp_arr);
		SDL_UnlockSurface(sdl->sur);
		sdl->text = SDL_CreateTextureFromSurface(sdl->rend, sdl->sur);
		SDL_RenderCopy(sdl->rend, sdl->text, NULL, NULL);
		SDL_RenderPresent(sdl->rend);
		SDL_DestroyTexture(sdl->text);
	}
	return (1);
}
