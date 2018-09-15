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

NAME = wolf
LIBFTA = libft/libft.a

CC = gcc

#CFLAGS = -Wall -Wextra -Werror
#CFLAGS += -g

INCLUDES = -I./includes/

LIBFT_DIR = ./libft/
LIB_FLAGS = -L$(LIBFT_DIR) -lft

INCLUDES	+=	-I./frameworks/SDL2.framework/Headers
INCLUDES	+=  -I./frameworks/SDL2_image.framework/Headers
INCLUDES	+=  -I./frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h
INCLUDES	+=  -F./frameworks 

FRAMEWORKS	=	-framework OpenGL -framework AppKit \
					-framework SDL2 -framework SDL2_image -framework SDL2_ttf -rpath ./frameworks 

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SOURCES = main.c

OBJ = $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(LIBFTA) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_FLAGS) -o $(NAME) $(INCLUDES) $(FRAMEWORKS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c ./includes/wolf.h
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
