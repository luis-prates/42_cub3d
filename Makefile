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
	$(MAKE) -C mlx_linux/

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(INCLUDES)


clean:
	$(MAKE) clean -C ./libft
	$(MAKE) -C mlx_linux/ clean
	$(RM)   $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		$(RM)   $(NAME)

re: fclean  $(NAME)

bonus: $(NAME)

.PHONY:         all clean fclean bonus

#	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
