# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 18:49:28 by tosilva           #+#    #+#              #
#    Updated: 2022/11/07 21:51:52 by lprates          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
### Variables																 ###
################################################################################

########################################
## Target Name						  ##
########################################

NAME	= cub3D


########################################
## Folders & Files					  ##
########################################

DEBUG_FILES	= $(NAME).dSYM/

# DEFAULT FOLDERS
LIB_DIR	= lib/
BIN_DIR	= bin/
INC_DIR	= inc/
SRC_DIR	= src/
OBJ_DIR	= obj/
DEP_DIR	= dep/

# LIBRARIES
LIBFT_DIR	= ${addprefix $(LIB_DIR), libft/}
LIBFT_FILE	= libft.a
LIBFT		:= ${addprefix $(LIBFT_DIR), ${addprefix $(BIN_DIR), $(LIBFT_FILE)}}

LIBMLX_DIR	= ${addprefix $(LIB_DIR), minilibx-linux/}
LIBMLX_FILE	= libmlx.a
LIBMLX		:= ${addprefix $(LIBMLX_DIR), $(LIBMLX_FILE)}


# FOLDERS
COLOURS_DIR		= colours/
DRAW_DIR		= draw/
GAME_DIR		= game/
MLX_DIR			= mlx/
PARSER_DIR		= parser/
SINGLETON_DIR	= singleton/

ALL_DIRS	:= $(COLOURS_DIR) $(DRAW_DIR) $(GAME_DIR) $(MLX_DIR) $(PARSER_DIR) $(SINGLETON_DIR)

# FILES
HFILES	:= colours.h \
			constants.h \
			data.h \
			cub3d.h
CFILES	:= main.c

COLOURS_FILES	= colours.c \
					colours_utils.c
DRAW_FILES		= draw.c \
					draw_utils.c
GAME_FILES		= game.c \
					hooks.c \
					hooks_utils.c \
					movement.c
MLX_FILES 		= mlx_images.c \
					mlx_utils.c
PARSER_FILES	= parser.c \
					parser_utils_1.c \
					parser_utils_2.c \
					parser_colour.c \
					parser_map.c \
					parser_map_utils_1.c \
					parser_map_utils_2.c \
					parser_texture.c
SINGLETON_FILES	= singletons.c

# FILES AND THEIR FOLDERS
HFILES_SRC	:= ${foreach file, $(INC_DIR), ${addprefix $(INC_DIR), $(HFILES)}}
CFILES_SRC	:= ${foreach file, $(SRC_DIR), ${addprefix $(SRC_DIR), $(CFILES)}}

COLOURS_SRC		:= ${foreach file, $(COLOURS_DIR), ${addprefix $(SRC_DIR)$(COLOURS_DIR), $(COLOURS_FILES)}}
DRAW_SRC		:= ${foreach file, $(DRAW_DIR), ${addprefix $(SRC_DIR)$(DRAW_DIR), $(DRAW_FILES)}}
GAME_SRC		:= ${foreach file, $(GAME_DIR), ${addprefix $(SRC_DIR)$(GAME_DIR), $(GAME_FILES)}}
MLX_SRC			:= ${foreach file, $(MLX_DIR), ${addprefix $(SRC_DIR)$(MLX_DIR), $(MLX_FILES)}}
PARSER_SRC		:= ${foreach file, $(PARSER_DIR), ${addprefix $(SRC_DIR)$(PARSER_DIR), $(PARSER_FILES)}}
SINGLETON_SRC		:= ${foreach file, $(SINGLETON_DIR), ${addprefix $(SRC_DIR)$(SINGLETON_DIR), $(SINGLETON_FILES)}}

INCS	:= $(HFILES_SRC)
SRCS	:= $(CFILES_SRC)
SRCS	+= $(COLOURS_SRC) $(DRAW_SRC) $(GAME_SRC) $(MLX_SRC) $(PARSER_SRC) $(SINGLETON_SRC)
OBJS	:= ${subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o)}
DEPS	:= ${subst $(SRC_DIR), $(DEP_DIR), $(SRCS:.c=.d)}


########################################
## Colors							  ##
########################################

# Reset
COLOR_RESET		=[0m

COLORF_RED		=[31m
COLORF_GREEN	=[32m
COLORF_YELLOW	=[33m
COLORF_CYAN		=[36m

CL_NORM_OK		:=$(COLORF_GREEN)
CL_NORM_WARN	:=$(COLORF_YELLOW)
CL_NORM_ERROR	:=$(COLORF_RED)
CL_NORM_NUM		:=$(COLORF_CYAN)


########################################
## Commands & Flags					  ##
########################################

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra # -03
DEBFLAGS	= -g -fsanitize=address
INCFLAGS	:= -I./$(LIBFT_DIR)$(INC_DIR) -I./$(LIBMLX_DIR) -I./$(INC_DIR)
LIBFLAGS	:= -L./$(LIBFT_DIR)$(BIN_DIR) -lft -L./$(LIBMLX_DIR) -lmlx -L/usr/lib -lbsd -lXext -lX11 -lm -lz
# (Linux) -> sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev
#PKGFLAGS	= 'pkg-config readline --cflags' 'pkg-config readline --libs'


NORM		= norminette
NORM_COLORS	:= sed "s/OK!/$(CL_NORM_OK)OK!$/$(COLOR_RESET)/g"
NORM_COLORS	+= | sed -E "s/Error(!|:)/$(CL_NORM_ERROR)Error\1$/$(COLOR_RESET)/g"
NORM_COLORS	+= | sed -E "s/Warning(!|:)/$(CL_NORM_WARN)Warning\1$/$(COLOR_RESET)/g"
NORM_COLORS	+= | sed -E "s/line:[[:blank:]]+([0-9]+)/$(CL_NORM_NUM)\1$/$(COLOR_RESET)/g"
NORM_COLORS	+= | sed -E "s/col:[[:blank:]]+([0-9]+)/$(CL_NORM_NUM)\1$/$(COLOR_RESET)/g"

MKDIR	= mkdir -p
RM		= rm -fr


#########################################
## User input						   ##
#########################################

folder	:=



################################################################################
### Rules																	 ###
################################################################################

.DELETE_ON_ERROR:

########################################
## Compile							  ##
########################################

all: libft libmlx target

libft $(LIBFT): | $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR)

libmlx $(LIBMLX): | $(LIBMLX_DIR)
	@$(MAKE) -C $(LIBMLX_DIR)

target: msg_compiling $(NAME) msg_created

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	@$(CC) $(CFLAGS) $(PKGFLAGS) $(INCFLAGS) $^ $(LIBFLAGS) -o $@

$(OBJS): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d | ${foreach dir, $(OBJ_DIR), ${addprefix $(OBJ_DIR), $(ALL_DIRS)}}
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@
	@echo "⬜\c"

$(DEPS): $(DEP_DIR)%.d: $(SRC_DIR)%.c $(LIBFT) $(LIBMLX) | ${foreach dir, $(DEP_DIR), ${addprefix $(DEP_DIR), $(ALL_DIRS)}}
	@$(CC) $(CFLAGS) $(INCFLAGS) -M \
		-MT '${patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$<} \
			${patsubst $(SRC_DIR)%.c,$(DEP_DIR)%.d,$<}' $< \
		-MF ${patsubst $(SRC_DIR)%.c,$(DEP_DIR)%.d,$<}

bonus:


########################################
## Debug							  ##
########################################

debug: CFLAGS += $(DEBFLAGS)
debug: debug_libft all

debug_libft:
	@$(MAKE) debug -C $(LIBFT_DIR)


########################################
## Make dirs						  ##
########################################

$(OBJ_DIR) $(DEP_DIR):
	@$(MKDIR) $@

${foreach dir, $(OBJ_DIR), ${addprefix $(OBJ_DIR), $(ALL_DIRS)}}: | $(OBJ_DIR)
	@$(MKDIR) $@

${foreach dir, $(DEP_DIR), ${addprefix $(DEP_DIR), $(ALL_DIRS)}}: | $(DEP_DIR)
	@$(MKDIR) $@

########################################
## Norm								  ##
########################################

norm:
	@echo "[ .. ] Norminette [ .. ]"
	@echo
	@echo "▱▱▱▱▱ HEADERS ▱▱▱▱▱"
	@$(NORM) $(INCS) | $(NORM_COLORS)
	@echo
	@echo "▱▱▱▱▱ SOURCES  ▱▱▱▱▱"
	@$(NORM) $(SRCS) | $(NORM_COLORS)
	@echo

norm_libft:
	@$(MAKE) norm folder=$(folder) -C $(LIBFT_DIR)


########################################
## Clear							  ##
########################################

clean:
	@$(MAKE) $@ -C $(LIBMLX_DIR)
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) $@ -C $(LIBFT_DIR)
	@$(RM) $(NAME)

clean_dep:
	@$(MAKE) $@ -C $(LIBFT_DIR)
	@$(RM) $(DEP_DIR)

clean_debug:
	@$(MAKE) $@ -C $(LIBFT_DIR)
	@$(RM) $(DEBUG_FILES)

clean_all: fclean clean_dep clean_debug
clean_all: msg_deleted


########################################
## Reload							  ##
########################################

re_debug: fclean debug

re: fclean all


########################################
##	PRINT VARIABLES					  ##
########################################

print-%:
	@echo $*=$($*)


########################################
## Messages							  ##
########################################

msg_compiling:
	@echo
	@echo "[ ... ] Creating ./$(NAME) [ ... ]"

msg_created:
	@echo "$(COLORF_GREEN)"
	@cat ./font/created.txt
	@echo "$(COLOR_RESET)"

msg_deleted:
	@echo "$(COLORF_RED)"
	@cat ./font/deleted.txt
	@echo "$(COLOR_RESET)"



################################################################################
### Phony																	 ###
################################################################################

.PHONY: all libft libmlx target bonus
.PHONY: debug debug_libft
.PHONY: norm norm_libft
.PHONY: clean fclean clean_dep clean_debug clean_all
.PHONY: re_debug re
.PHONY: msg_compiling msg_created msg_deleted



################################################################################
### Includes																 ###
################################################################################

-include ${shell find . -maxdepth 2 -type f -name '*.d'}
