NAME = ./cub3D
INCLUDE_DIRS := includes
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
SRC = $(wildcard *.c)
OBJ := $(SRC:.c=.o)
RM = rm -f
MAKE = make

all: libft.a minilibx $(NAME) 

libft.a:
	make -C libft/
	make bonus -C libft/

minilibx:
	$(MAKE) -C mlx/

%.o: %.c
	$(CC) -Imlx -c $^ -o $@ $(INCLUDES)

$(NAME): $(OBJ)
	$(CC) $^ -Lmlx/ -lmlx -framework OpenGL -framework AppKit -Llibft -lft -o $@ $(INCLUDES)


clean:
	$(MAKE) clean -C ./libft
	$(MAKE) -C mlx/ clean
	$(RM)   $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		$(RM)   $(NAME)

re: fclean  $(NAME)

bonus: $(NAME)

.PHONY:         all clean fclean bonus

#	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@