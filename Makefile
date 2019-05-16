# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:20 by bcarlier          #+#    #+#              #
#    Updated: 2019/05/16 15:12:56 by bcarlier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=lem_in
LIBFT=$(PATH_LIB)libft.a

# --- 1.Source/Header ----------------------------------------------------------

SRC=main \
	lem_libft
INCLUDES=	$(PATH_HDR)libft.h \
			$(PATH_HDR)lem_in.h

# --- 2.Path -------------------------------------------------------------------

PATH_HDR=./includes/
PATH_OBJ=./srcs/obj/
PATH_SRC=./srcs/
PATH_LIB=./libft/

# --- 3.Object -----------------------------------------------------------------

OBJ=$(SRC:%=$(PATH_OBJ)%.o)

#--- 4.Variables ---------------------------------------------------------------

CC_FLAGS=-pedantic -g3 -O3 -Werror -Wall -Wextra
CC_LIB=-L$(PATH_LIB) -lft
CC_O=gcc $(CC_FLAGS) -c -I$(PATH_HDR)
CC_C=gcc $(CC_FLAGS) -o $(NAME) $(OBJ) -I$(PATH_HDR) $(CC_LIB)

# Text Style
BOLD=\033[1m
_DIM=\033[2m
ITAL=\033[3m
UNDR=\033[4m
INVR=\033[7m
HIDE=\033[8m
STRK=\033[9m
RST_A=\033[0m
RST_B=\033[21m
RST_D=\033[22m
RST_U=\033[24m
RST_I=\033[27m
RST_H=\033[28m
RST_S=\033[29m

# Foreground Color
RST_FG=\033[39m
FG_BLA=\033[30m
FG_RED=\033[31m
FG_GRE=\033[32m
FG_YEL=\033[33m
FG_BLU=\033[34m
FG_PUR=\033[35m
FG_CYA=\033[36m
FG_WHI=\033[97m
FG_LGRA=\033[37m
FG_DGRA=\033[90m
FG_LRED=\033[91m
FG_LGRE=\033[92m
FG_LYEL=\033[93m
FG_LBLU=\033[94m
FG_LPUR=\033[95m
FG_LCYA=\033[96m

# Background Color
RST_BG=\033[49m
BG_BLA=\033[40m
BG_RED=\033[41m
BG_GRE=\033[42m
BG_YEL=\033[43m
BG_BLU=\033[44m
BG_PUR=\033[45m
BG_CYA=\033[46m
BG_WHI=\033[107m
BG_LGRA=\033[47m
BG_DGRA=\033[100m
BG_LRED=\033[101m
BG_LGRE=\033[102m
BG_LYEL=\033[103m
BG_LBLU=\033[104m
BG_LPUR=\033[105m
BG_LCYA=\033[106m

# --- 5.Rules ------------------------------------------------------------------

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INCLUDES)
	-@printf "$(FG_LYEL)Object files creation:   $(FG_GRE)$(BOLD)Done.$(RST_A)  \n"
	@$(CC_C)
	-@printf "$(FG_LYEL)Compiling $(NAME):        $(FG_GRE)$(BOLD)Done.$(RST_A)\n"

$(LIBFT):
	-@printf "===== SUBPROCESS - libft =====\n"
	@make -sC $(PATH_LIB)
	-@printf "===== SUBPROCESS - Over ======\n"

$(PATH_OBJ)%.o:$(PATH_SRC)%.c $(INCLUDES)
	-@printf "$(FG_CYA)Creating $@ $(RST_A)\n"
	@$(CC_O) $< -o $@

clean:
	@rm -f $(OBJ)
	@make -sC $(PATH_LIB) clean >> /dev/null
	-@printf "$(FG_LRED)Deleting object files:   $(FG_GRE)$(BOLD)Done.$(RST_A)\n"

fclean: clean
	@rm -f $(NAME)
	@make -sC $(PATH_LIB) fclean >> /dev/null
	-@printf "$(FG_LRED)Removing $(NAME):      $(FG_GRE)$(BOLD)Done.$(RST_A)\n"
	
re: fclean all

.PHONY: all clean fclean re
