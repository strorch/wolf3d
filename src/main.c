/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 20:58:30 by mstorcha          #+#    #+#             */
/*   Updated: 2018/09/15 20:58:45 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define K_K key.keysym.scancode
#define E_TYPE type

void	exit_message(const char *str)
{
	ft_putendl(str);
	exit(0);
}

void	key_events(SDL_Event *event, t_app *app)
{
	t_map	map;
	t_user	user;

	map = (*app).game->map;
	user = *(*app).game->user;
	(event->K_K == SDL_SCANCODE_ESCAPE) ? exit_message("Done!\n") : 0;

	// (event->K_K == SDL_SCANCODE_DOWN)	? (app->game.user.cam.pos. += 5) : 0;
	if (event->K_K == SDL_SCANCODE_UP)
	{
		if(map.keys[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
		if(map.keys[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	}
	else if (event->K_K == SDL_SCANCODE_DOWN)
	{
		if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
		if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	// else if (event->K_K == SDL_SCANCODE_LEFT)
	// {
 //      //both camera direction and camera plane must be rotated
 //      double oldDirX = dirX;
 //      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
 //      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
 //      double oldPlaneX = planeX;
 //      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
 //      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	// }
	// else if (event->K_K == SDL_SCANCODE_RIGHT)
	// {
 //      //both camera direction and camera plane must be rotated
 //      double oldDirX = dirX;
 //      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
 //      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
 //      double oldPlaneX = planeX;
 //      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
 //      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	// }
}

void	sdl_events(SDL_Event *event, t_app *app)
{
	while (SDL_PollEvent(event))
	{
		(event->E_TYPE == SDL_KEYDOWN) ? key_events(event, app) : 0;
		(event->E_TYPE == SDL_QUIT) ? exit_message("Done!\n") : 0;
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
						SDL_WINDOW_SHOWN)))
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
	pos.x = 22;
	pos.y = 12;
	plane.x = 0;
	plane.y = 0.66;
	user->cam.dir = dir;
	user->cam.pos = pos;
	user->cam.plane = plane;
}

int		main(int argc, char **argv)
{
	SDL_Event	event;
	t_sdl		*sdl;
	t_app		app;
	t_user		user;
	int			*tmp_arr;

	app.sdl = init_sdl();
	sdl = app.sdl;
	app.game = (t_game *)ft_memalloc(sizeof(t_game));
	app.game->map = read_map(argc, argv);
	app.game->user = (t_user *)ft_memalloc(sizeof(t_user));
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
		// break;
	}
	TTF_Quit();
	SDL_Quit();
	return (0);
}
