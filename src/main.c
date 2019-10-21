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

#define texWidth 64
#define texHeight 64

#define K_K key.keysym.scancode
#define E_TYPE type
#define W_E window.event

void	key_events(SDL_Event *event, t_app *app)
{
	t_map		*map;
	t_camera	c;
	t_vec		d;
	t_vec		p;
	t_vec		pl;
	float			posX;
	float			posY;

	posX = (*app).game->user->cam.pos.x;
	posY = (*app).game->user->cam.pos.y;
	map = (*app).game->map;
	c = (*app).game->user->cam;
	d = c.dir;
	p = c.pos;
	pl = c.plane;

	(event->K_K == SDL_SCANCODE_ESCAPE) ? exit_message("Done!\n") : 0;
	if (event->K_K == SDL_SCANCODE_UP)
	{
		double	w = 0.25;
		if(map->keys[(int)(p.x + d.x * (c.mv_speed + w))][(int)p.y - (int)(d.y * w)] == 0) posX += d.x * c.mv_speed;
		if(map->keys[(int)p.x - (int)(d.x * w)][(int)(p.y + d.y * (c.mv_speed + w))] == 0) posY += d.y * c.mv_speed;
	}
	else if (event->K_K == SDL_SCANCODE_DOWN)
	{
		double	w = -0.25;
		if(map->keys[(int)(p.x + d.x * (c.mv_speed + w))][(int)p.y - (int)(d.y * w)] == 0) posX -= d.x * c.mv_speed;
		if(map->keys[(int)p.x - (int)(d.x * w)][(int)(p.y + d.y * (c.mv_speed + w))] == 0) posY -= d.y * c.mv_speed;
	}
	else if (event->K_K == SDL_SCANCODE_RIGHT)
	{
		(*app).game->user->cam.dir.x = d.x * cos(-c.rot_speed) - d.y * sin(-c.rot_speed);
		(*app).game->user->cam.dir.y = d.x * sin(-c.rot_speed) + d.y * cos(-c.rot_speed);
		(*app).game->user->cam.plane.x = pl.x * cos(-c.rot_speed) - pl.y * sin(-c.rot_speed);
		(*app).game->user->cam.plane.y = pl.x * sin(-c.rot_speed) + pl.y * cos(-c.rot_speed);
	}
	else if (event->K_K == SDL_SCANCODE_LEFT)
	{
		(*app).game->user->cam.dir.x = d.x * cos(c.rot_speed) - d.y * sin(c.rot_speed);
		(*app).game->user->cam.dir.y = d.x * sin(c.rot_speed) + d.y * cos(c.rot_speed);
		(*app).game->user->cam.plane.x = pl.x * cos(c.rot_speed) - pl.y * sin(c.rot_speed);
		(*app).game->user->cam.plane.y = pl.x * sin(c.rot_speed) + pl.y * cos(c.rot_speed);
	}
	(*app).game->user->cam.pos.x = posX;
	(*app).game->user->cam.pos.y = posY;
}

void	resize_window(t_map *m, int new_width, int new_height)
{
	printf("HELLO!\n");
//	m->w = new_width;
//	m->h = new_height;
//	!(m->screen = SDL_GetWindowSurface(m->window))
//	? put_error(SDL_GetError()) : 0;
//	m->image = m->screen->pixels;
}

void	sdl_events(SDL_Event *e, t_app *app)
{
	while (SDL_PollEvent(e))
	{
		(e->E_TYPE == SDL_KEYDOWN) ? key_events(e, app) : 0;
		(e->E_TYPE == SDL_QUIT) ? exit_message("Done!\n") : 0;
		(e->W_E == SDL_WINDOWEVENT_RESIZED) ? resize_window(app->game->map, e->window.data1, e->window.data2) : 0;
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
										 SDL_WINDOW_ALLOW_HIGHDPI)))
		exit_message("Error creating window");
	if (!(sdl->rend = SDL_CreateRenderer(sdl->window, -1,
							SDL_RENDERER_ACCELERATED)))
		exit_message("Error in creating renderer");
	if (!(sdl->sur = SDL_CreateRGBSurface(0, SCREEN_W, SCREEN_H, 32, 0, 0, 0, 0)))
		exit_message("Error in creating surface");
	return (sdl);
}

void	init_user(t_user **user_h)
{
	t_user	*user;
	t_vec	dir;
	t_vec	pos;
	t_vec	plane;

	user = *user_h;
	dir.x = -1;
	dir.y = 0;
	pos.x = 2;
	pos.y = 1.5;
	plane.x = 0;
	plane.y = 0.66;
	user->cam.dir = dir;
	user->cam.pos = pos;
	user->cam.plane = plane;
}

int		**get_textures()
{
	int **texture = (int **)ft_memalloc(sizeof(int *) * 8);
	for (int i = 0; i < 8; i++) {
		texture[i] = (int *)ft_memalloc(sizeof(int) * texWidth * texHeight);
	}

	for(int x = 0; x < texWidth; x++)
		for(int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y);
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor;
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			texture[4][texWidth * y + x] = 256 * xorcolor;
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16);
			texture[6][texWidth * y + x] = 65536 * ycolor;
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;
		}
	return texture;
}

int		main(int argc, char **argv)
{
	SDL_Event	event;
	t_sdl		*sdl;
	t_app		app;
	t_map		*map;
	int			*tmp_arr;
    char        **tmp_argv;

    if (argc == 2) {
        if (!ft_strcmp(argv[1], "-h"))
            print_usage();
        tmp_argv = argv;
    } else {
        tmp_argv = (char**)ft_memalloc(sizeof(char*) * 2);
        tmp_argv[1] = (char*)ft_memalloc(sizeof(char) * 15);
        ft_strcpy(tmp_argv[1], "./maps/2.m");
        printf("%s\n", tmp_argv[1]);
    }
	if (!(map = read_map(tmp_argv))) {
		exit_message("Wrong map");
	}
	app.sdl = init_sdl();
	sdl = app.sdl;
	app.game = (t_game *)ft_memalloc(sizeof(t_game));
	app.game->map = map;
	app.game->user = (t_user *)ft_memalloc(sizeof(t_user));
	app.game->text = get_textures();
	init_user(&app.game->user);

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
	TTF_Quit();
	SDL_Quit();
	return (0);
}
