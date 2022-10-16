# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 18:49:28 by tosilva           #+#    #+#              #
#    Updated: 2022/10/16 13:10:37 by tosilva          ###   ########.fr        #
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


# FILES
HFILES	:= colours.h \
			constants.h \
			data.h \
			cub3d.h

CFILES	:= colours.c \
			colours_utils.c \
			mlx_images.c \
			mlx_utils.c \
			parser.c \
			parser_utils_1.c \
			parser_utils_2.c \
			parser_colour.c \
			parser_map.c \
			parser_map_utils_1.c \
			parser_map_utils_2.c \
			parser_texture.c \
			singletons.c \
			main.c

INC	:= ${foreach file, $(INC_DIR), ${addprefix $(INC_DIR), $(HFILES)}}
SRC	:= ${foreach file, $(SRC_DIR), ${addprefix $(SRC_DIR), $(CFILES)}}
OBJ	:= ${subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o)}
DEP	:= ${subst $(SRC_DIR), $(DEP_DIR), $(SRC:.c=.d)}


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

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	@$(CC) $(CFLAGS) $(PKGFLAGS) $(INCFLAGS) $^ $(LIBFLAGS) -o $@

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEP_DIR)%.d | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@
	@echo "⬜\c"

$(DEP): $(DEP_DIR)%.d: $(SRC_DIR)%.c $(LIBFT) $(LIBMLX) | $(DEP_DIR)
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


########################################
## Norm								  ##
########################################

norm:
	@echo "[ .. ] Norminette [ .. ]"
	@echo
	@echo "▱▱▱▱▱ HEADERS ▱▱▱▱▱"
	@$(NORM) $(INC) | $(NORM_COLORS)
	@echo
	@echo "▱▱▱▱▱ SOURCES  ▱▱▱▱▱"
	@$(NORM) $(SRC) | $(NORM_COLORS)
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
