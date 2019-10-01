/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 20:55:17 by mstorcha          #+#    #+#             */
/*   Updated: 2018/09/15 20:55:18 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "../libft/libft.h"
# define HEIGHT 800
# define WIDTH 800

# include <math.h>
# include <pwd.h>

# ifdef linux
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
#  include <SDL2/SDL_ttf.h>
# else
#  include "SDL.h"
#  include "SDL_image.h"
#  include "SDL_ttf.h"
# endif

typedef struct	s_vec
{
	int			x;
	int			y;
	int			z;
}				t_vec;


typedef struct	s_camera
{
	t_vec		dir;
	t_vec		pox;
}				t_camera;

typedef struct	s_user
{
	t_camera	cam;
}				t_user;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*rend;
	SDL_Surface		*sur;
	SDL_Texture		*text;
	SDL_Event		event;
}				t_sdl;

typedef struct	s_game
{
	t_vec		color;
	t_user		user;
}				t_game;

typedef struct	s_app
{
	t_sdl		*sdl;
	t_game		*game;
}				t_app;

#endif
