NAME=cub3D
# MFLAGS = -lmlx -framework OpenGL -framework Appkit
FLAGS= -Werror -Wextra -Wall -fsanitize=address -g

PARSE= main.c\
	   parsing/func_utils/utils_1.c parsing/utils_parse.c parsing/parse_config.c parsing/get_next_line.c \
	   parsing/func_utils/utils_2.c

EXEC=

OBJ=$(PARSE:.c=.o) $(EXEC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) cub3D.h
	@cc $(FLAGS) $(MFLAGS) $(OBJ) -o $(NAME)
	@echo "Compilation done;"

%.o:%.c cub3D.h
	@cc $(FLAGS) $(MFLAGS) -c $< -o $@
clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)

re: fclean all