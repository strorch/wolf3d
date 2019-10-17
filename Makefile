# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/26 15:48:11 by mstorcha          #+#    #+#              #
#    Updated: 2018/09/15 20:56:33 by mstorcha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### LINUX SDL INSTALLATION

#install sdl2
# sudo apt install libsdl2-dev libsdl2-2.0-0 -y;
#install sdl image
# sudo apt install libjpeg9-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;
#install sdl mixer
# sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;
#install sdl true type fonts
# sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;

NAME = wolf3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror
#CFLAGS += -g

FRAMEWORKS_DIR	= ./frameworks/
LIBFT_DIR		= ./libft/
INCLUDES_DIR	= ./includes/
SRC_DIR			= ./src/
OBJ_DIR			= ./obj/

SOURCES			= \
					main.c \
					game_main.c \
					read_map.c \
					colors.c

ifeq ($(DESKTOP_SESSION),ubuntu)
    INCLUDES	+=	`sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm -ldl
else
	INCLUDES	=	-I$(FRAMEWORKS_DIR)SDL2.framework/Headers/
	INCLUDES	+=  -I$(FRAMEWORKS_DIR)SDL2_image.framework/Headers/
	INCLUDES	+=  -I$(FRAMEWORKS_DIR)SDL2_ttf.framework/Headers/
	INCLUDES	+=  -F$(FRAMEWORKS_DIR)

	FRAMEWORKS	=	-framework OpenGL -framework AppKit \
					-framework SDL2 -framework SDL2_image -framework SDL2_ttf -rpath $(FRAMEWORKS_DIR)
endif

INCLUDES		+=	-I$(INCLUDES_DIR)

LIBFTA			=	$(LIBFT_DIR)libft.a
LIBFTA_FLAGS	=	-L$(LIBFT_DIR) -lft

OBJ = $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(LIBFTA) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFTA_FLAGS) -o $(NAME) $(INCLUDES) $(FRAMEWORKS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES_DIR)*.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(LIBFTA): lib

lib:
	@make all -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@/bin/rm -rf $(OBJ)
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@/bin/rm -f $(NAME)

re: fclean all
