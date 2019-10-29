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

# include "libft.h"
# define SCREEN_H 800
# define SCREEN_W 800

# define T_WIDTH 64
# define T_HEIGHT 64

# define ITEMS_NUM 10

# define K_K key.keysym.scancode
# define E_TYPE type
# define W_E window.event

# include <math.h>
# include <time.h>

# ifdef linux
#  include <SDL2/SDL.h>
# else
#  include "SDL.h"
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

typedef struct	s_util_map
{
	t_vec		*map_sz;
	char		***ch_keys;
}				t_util_map;

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

typedef struct	s_event
{
	int			m;
	int			r;
}				t_event;

typedef struct	s_app
{
	t_sdl		*sdl;
	t_game		*game;
	char		*file;
}				t_app;

typedef struct	s_floor_obj
{
	int			side;
	t_vec		raydir;
	t_vec		map;
	double		wall_x;
	double		perp_wall_dist;
	int			x;
	int			y;
	int			draw_end;
	t_vec		pos;
	int			**res_map_h;
	t_game		game;
}				t_floor_obj;

/*
** read_map.c
*/
t_game			*init_game(char *fname);

/*
** game_main.c
*/
int				*get_pixels_map(t_game *game_h);

/*
** utils.c
*/
void			exit_message(const char *str);
void			print_usage(void);

/*
** colors.c
*/
int				get_hex_color(t_vec c);

/*
** validation.c
*/
int				validate_params(int argc, char **argv);

/*
** textures.c
*/
int				**get_textures(void);

/*
** keys_validation.c
*/
int				keys_validation(char ***map, t_vec *map_sz);

/*
** game_floor.c
*/
void			draw_floor();

#endif
