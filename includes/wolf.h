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
# define SCREEN_H 800
# define SCREEN_W 800

# include <math.h>
# include <pwd.h>
# include <time.h>

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
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef struct	s_camera
{
	t_vec		dir;
	t_vec		pos;
	t_vec		plane;
	float		mv_speed;
	float		rot_speed;
}				t_camera;

typedef struct	s_user
{
	t_camera	cam;
}				t_user;

typedef struct	s_map
{
	int			**keys;
	int			h;
	int			w;
}				t_map;

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
	t_user		*user;
	t_map		*map;
	int			**text;
}				t_game;

typedef struct	s_app
{
	t_sdl		*sdl;
	t_game		*game;
}				t_app;

/*
** read_map.c
*/
t_map			*read_map(char **argv);

/*
** game_main.c
*/
int				*get_pixels_map(t_game *game_h);

/*
** utils.c
*/
void			exit_message(const char *str);

/*
** colors.c
*/
int				get_hex_color(t_vec c);

/*
** validation.c
*/
int				validate_params(int argc, char **argv);

#endif
