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

void	sdl_events(SDL_Event *e, t_app *app)
{
	while (SDL_PollEvent(e))
	{
		(e->E_TYPE == SDL_KEYDOWN) ? key_events(e, app) : 0;
		(e->E_TYPE == SDL_QUIT) ? exit_message("Done!") : 0;
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
	char		*const_ch;

	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "-h"))
			print_usage();
		tmp_argv = argv[1];
	}
	else
	{
		const_ch = "./maps/2.m";
		if (!(tmp_argv = ft_strnew(ft_strlen(const_ch))))
			exit_message("Memory error");
		ft_strcpy(tmp_argv, const_ch);
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
