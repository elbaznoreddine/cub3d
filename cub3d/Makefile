# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 11:46:20 by yzoullik          #+#    #+#              #
#    Updated: 2025/07/05 16:04:37 by yzoullik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
HEADER = cub3d.h

SRC =	cub3d.c\
		get_next_line.c\
		get_next_line_utils.c\
		split.c\
		draw.c\


NAMEB = cub3d_bonus
HEADERB = bonus/cub3d_bonus.h

SRCB =	bonus/so_long_bonus.c\
		bonus/get_next_line_bonus.c\
		bonus/get_next_line_utils_bonus.c\
		bonus/split_bonus.c\
		bonus/pars_bonus.c\
		bonus/utils_bonus.c\
		bonus/pars_utils_bonus.c\
		bonus/render_bonus.c\
		bonus/pars_utils2_bonus.c\
		bonus/ai_bonus.c
		
OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)

MLX_DIR = ./minilibx-linux
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -fsanitize=address -g3
MLXFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext

all: $(NAME)

bonus : $(NAMEB)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	cc $(CFLAGS)  $(OBJ) -o $(NAME) $(MLXFLAGS)

$(NAMEB): $(OBJB)
	make -C $(MLX_DIR)
	cc $(CFLAGS) $(OBJB) -o $(NAMEB) $(MLXFLAGS)

%.o: %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c $(HEADERB)
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME) $(NAMEB)

re: fclean all

.PHONY: clean