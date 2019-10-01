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

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int			world_map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int		get_hex_color(t_vec c)
{
	return c.x * 0x10000 + c.y * 0x100 + c.z;
}

void	exit_message(const char *str)
{
	ft_putendl(str);
	exit(0);
}

void	key_events(SDL_Event *event, t_app *app)
{
	(event->K_K == SDL_SCANCODE_ESCAPE) ? exit(0) : 0;
	// (event->K_K == SDL_SCANCODE_UP) ? (app->game->color.r += 5) : 0;
	(event->K_K == SDL_SCANCODE_UP) ? (app->game->color.y += 5) : 0;
	(event->K_K == SDL_SCANCODE_UP) ? (app->game->color.z += 5) : 0;
	// (event->K_K == SDL_SCANCODE_DOWN) ? (mlx->scene->cam.d.x -= 5) : 0;
	// (event->K_K == SDL_SCANCODE_LEFT) ? (mlx->scene->cam.d.y += 5) : 0;
	// (event->K_K == SDL_SCANCODE_RIGHT) ? (mlx->scene->cam.d.y -= 5) : 0;
}

void	sdl_events(SDL_Event *event, t_app *app)
{
	while (SDL_PollEvent(event))
	{
		(event->E_TYPE == SDL_KEYDOWN) ? key_events(event, app): 0;
		(event->E_TYPE == SDL_QUIT) ? exit(1) : 0;
		// (event->E_TYPE == SDL_MOUSEBUTTONDOWN) ? some() : 0;
		// (event->E_TYPE == SDL_MOUSEWHEEL) ? some() : 0;
		// (event->E_TYPE == SDL_MOUSEMOTION) ? some() : 0;
	}
}

void	init_sdl(t_sdl *sdl)
{
	sdl = (t_sdl*)ft_memalloc(sizeof(t_sdl));
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
}

int*	drawFunc(int color)
{
	int i;
	int j;
	int *pict;

	i = 0;
	pict = (int *)ft_memalloc(800*800 * sizeof(int));
	while (i++ < 800)
	{
		j = 0;
		while (j++ < 800)
		{
			if (i >400 && i < 600)
				pict[800 * i + j] = color;
		}
	}
	return pict;
}

int		main(int argc, char **argv)
{
	SDL_Event	event;
	t_app		app;
	t_sdl		sdl;

	printf("KEK\n");
	init_sdl(app.sdl);
	// sdl = *app.sdl;
	// app.game = (t_game *)ft_memalloc(sizeof(t_game));
	// app.game->color.x = 255;
	// app.game->color.y = 0;
	// app.game->color.z = 0;
	// while (1)
	// {
	// 	free(sdl.sur->pixels);
	// 	sdl_events(&event, &app);
	// 	sdl.sur->pixels = drawFunc(get_hex_color(app.game->color));
	// 	sdl.text = SDL_CreateTextureFromSurface(sdl.rend, sdl.sur);
	// 	SDL_RenderCopy(sdl.rend, sdl.text, NULL, NULL);
	// 	SDL_RenderPresent(sdl.rend);
	// 	SDL_DestroyTexture(sdl.text);
	// }
	// TTF_Quit();
	// SDL_Quit();
	return (0);
}
