# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:20 by bcarlier          #+#    #+#              #
#    Updated: 2019/08/20 13:43:31 by aulopez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=lem-in
LIBFT=$(PATH_LIB)libft.a

FLAGS=-g3 -Wall -Wextra -Werror
LIB_RULE=
CC_O=gcc $(FLAGS) -c -I$(PATH_HDR)
CC_C=gcc $(FLAGS) -o $(NAME) $(OBJ) -I$(PATH_HDR) -L$(PATH_LIB) -lft
OBJ=$(SRC:%=$(PATH_OBJ)%.o)

# --- 1.Source/Header ----------------------------------------------------------

SRC=main \
	parser_ant \
	parser_room \
	parser_tube \
	parser_master \
	rb_insert \
	rb_balance \
	rb_function \
	edmundkarp \
	print \
	s_utils \
	init_edmundkarp \
	ek_pathfinder
INCLUDES=	$(PATH_HDR)libft.h \
			$(PATH_HDR)lem_in.h \
			$(PATH_HDR)rb_tree.h

# --- 2.Path -------------------------------------------------------------------

PATH_HDR=./includes/
PATH_OBJ=./srcs/obj/
PATH_SRC1=./srcs/
PATH_SRC2=./srcs/parser/
PATH_SRC3=./srcs/rb_tree/
PATH_SRC4=./srcs/algorithm/
PATH_LIB=./libft/

# --- 3.Rules ------------------------------------------------------------------

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INCLUDES)
	-@printf " ==> Creating $(NAME)\n"
	@$(CC_C)

$(LIBFT):
	-@printf " ==> Creating $(LIBFT:$(PATH_LIB)%=%)\n"
	@make -sC $(PATH_LIB) $(LIB_RULE)

$(PATH_OBJ)%.o:$(PATH_SRC1)%.c $(INCLUDES)
	-@printf " >O $(FLAGS) $(@:srcs/obj/%.o=%)\n"
	@$(CC_O) $< -o $@
$(PATH_OBJ)%.o:$(PATH_SRC2)%.c $(INCLUDES)
	-@printf " >O $(FLAGS) $(@:srcs/obj/%.o=%)\n"
	@$(CC_O) $< -o $@
$(PATH_OBJ)%.o:$(PATH_SRC3)%.c $(INCLUDES)
	-@printf " >O $(FLAGS) $(@:srcs/obj/%.o=%)\n"
	@$(CC_O) $< -o $@
$(PATH_OBJ)%.o:$(PATH_SRC4)%.c $(INCLUDES)
	-@printf " >O $(FLAGS) $(@:srcs/obj/%.o=%)\n"
	@$(CC_O) $< -o $@


clean:
	-@printf " ===> Removing object file(s)\n"
	@rm -f $(OBJ)
	@make -sC $(PATH_LIB) clean >> /dev/null

fclean: clean
	-@printf " ===> Removing $(NAME)\n"
	@rm -f $(NAME)
	-@printf " ===> Removing $(LIBFT:$(PATH_LIB)%=%)\n"
	@make -sC $(PATH_LIB) fclean >> /dev/null
	
re: fclean all

O3: FLAGS += -O3 -fno-builtin
O3: LIB_RULE = O3
O3: re;
O2: FLAGS += -O2
O2: LIB_RULE = O2
O2: re;
Os: FLAGS += -Os
Os: LIB_RULE = Os
Os: re;
g3: FLAGS = -g3
g3: LIB_RULE = g3
g3: re;
pedantic: FLAGS += -pedantic
pedantic: LIB_RULE = pedantic
pedantic: re;

.PHONY: all clean fclean re O3 O2 Os g3 pedantic
