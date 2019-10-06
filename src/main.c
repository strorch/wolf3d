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

void	update_point(t_vec *vec_h)
{
	t_vec vec;

	vec = *vec_h;
	// vec.x
}

void	key_events(SDL_Event *event, t_app *app)
{
	(event->K_K == SDL_SCANCODE_ESCAPE) ? exit_message("Done!\n") : 0;

	// (event->K_K == SDL_SCANCODE_DOWN)	? (app->game.user.cam.pos. += 5) : 0;
	// if (event->K_K == SDL_SCANCODE_UP)
	// {
	// 	if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
	// 	if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	// }
	// else if (event->K_K == SDL_SCANCODE_DOWN)
	// {
	// 	if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
	// 	if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	// }
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

t_sdl	*get_new_sdl(void)
{
	t_sdl *sdl;

	sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit_message("Error in init sdl");
	if (!(sdl->window = SDL_CreateWindow("Wolf3D",
						SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
						SDL_WINDOW_SHOWN)))
		exit_message("Error creating window");
	if (!(sdl->rend = SDL_CreateRenderer(sdl->window, -1,
							SDL_RENDERER_ACCELERATED)))
		exit_message("Error in creating renderer");
	if (!(sdl->sur = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0)))
		exit_message("Error in creating surface");
	return (sdl);
}

int		main(int argc, char **argv)
{
	SDL_Event	event;
	t_sdl		*sdl;
	t_app		app;
	int			*tmp_arr;

	app.sdl = get_new_sdl();
	sdl = app.sdl;
	app.game = (t_game *)ft_memalloc(sizeof(t_game));
	app.game->color.x = 255;
	app.game->color.y = 0;
	app.game->color.z = 0;
	while (1)
	{
		sdl_events(&event, &app);

		tmp_arr = get_pixels_map();
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
