clear_terminal := clear
compile := gcc
compile_option := -O3 -c
enable_warnings := -Wall -Wextra
#header_file := ./minishell.h
library_option := -l
NAME := cub3d
norminette := norminette
output_name_option := -o
program_file := ./${NAME}
remove_file := rm
remove_file_option := -f
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
source_files := $(call rwildcard,src,*.c)
object_files := $(source_files:.c=.o)
include_dirs := includes libs/libft/ libs/mlx_linux /usr/include
includes := $(addprefix -I, $(include_dirs))
libft = -L libs/libft -lft
mlxlib := -Llibs/mlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
turn_warnings_into_errors := -Werror

default_rule: clear_terminal remove_program norminette compile execute_program

clear_terminal:
	@${clear_terminal}

remove_program:
	@${remove_file} ${remove_file_option} ${program_file}

norminette:
	@$(eval norminette_errors=`${norminette} ${header_file} ${source_files} | grep --invert-match 'OK'`)
#	@if [ "${norminette_errors}" != "" ]; then\
		echo "${norminette_errors}";\
		exit 1;\
	fi

compile: libft.a minilibx ${program_file}

execute_program:
	@${program_file}

libft.a:
	make -C libs/libft/
	make bonus -C libs/libft/

minilibx:
	make -C libs/mlx_linux/

# The "all", "${NAME}", "clean", "fclean" and "re" make rules are mandatory
# by 42's Norm (version 3 at the time of writting this comment).

all: libft.a minilibx ${program_file}

%.o: %.c
	@${compile} \
		${enable_warnings} \
		${turn_warnings_into_errors} \
		${compile_option} $< \
		${output_name_option} $@ \
		${includes}

${NAME}: ${object_files}
	@${compile} \
		${enable_warnings} \
		${turn_warnings_into_errors} \
		${output_name_option} ${program_file} \
		${object_files} \
		${mlxlib} \
		${includes} ${libft}

clean:
	make clean -C ./libs/libft
	make clean -C ./libs/mlx_linux
	@${remove_file} ${remove_file_option} ${object_files}

fclean: clean
	make fclean -C ./libs/libft
	make clean -C ./libs/mlx_linux
	@${remove_file} ${remove_file_option} ${program_file}

re: fclean all

.PHONY: default_rule clear_terminal remove_program norminette compile execute_program all clean fclean re
