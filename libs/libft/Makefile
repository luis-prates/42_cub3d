CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

NAME = ./libft.a
SOURCES = $(filter-out $(BONUS), $(wildcard ft_*.c))
SOURCES_B = $(wildcard ft_*.c) get_next_line.c get_next_line_utils.c
OBJECTS = $(SOURCES:.c=.o)
OBJECTS_B = $(SOURCES_B:.c=.o)
BONUS	= ft_lstsize.c ft_lstlast.c ft_lstadd_front.c ft_lstadd_back.c \
			ft_lstnew.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
			ft_swap_bonus.c ft_islower_bonus.c ft_isupper_bonus.c \
			ft_iscntrl_bonus.c ft_isgraph_bonus.c ft_ispunct_bonus.c \
			ft_isspace_bonus.c ft_isblank_bonus.c ft_isxdigit_bonus.c \
			ft_putchar_bonus.c ft_putstr_bonus.c ft_putendl_bonus.c \
			ft_putnbr_bonus.c ft_sqrt_bonus.c ft_strcmp_bonus.c \
			ft_strcpy_bonus.c ft_strncpy_bonus.c ft_strstr_bonus.c \
			ft_strcat_bonus.c ft_strncat_bonus.c ft_strndup_bonus.c \
			get_next_line.c get_next_line_utils.c

all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJECTS)
	ar -cr $@ $(OBJECTS)

$(NAME_B): $(OBJECTS_B)
	ar -cr $@ $(OBJECTS_B)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME) $(OBJECTS_B)

re: fclean all

norm: norminette $(SOURCES)

bonus: $(NAME) $(OBJECTS_B)
			ar -rcs $(NAME) $(OBJECTS_B)

so:
	$(CC) -fPIC $(CFLAGS) $(SOURCES_B)
	gcc -shared -o libft.so $(OBJECTS_B)
