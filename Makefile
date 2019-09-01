# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:20 by bcarlier          #+#    #+#              #
#    Updated: 2019/09/01 23:09:20 by aulopez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=lem-in
LIBFT=$(PATH_LIB)libft.a

FLAGS=-Werror -Wall -Wextra
LIB_RULE=
CC_O=gcc $(FLAGS) -c -I$(PATH_HDR)
CC_C=gcc $(FLAGS) -o $(NAME) $(OBJ) -I$(PATH_HDR) -L$(PATH_LIB) -lft
OBJ=$(SRC:%=$(PATH_OBJ)%.o)

# --- 1.Source/Header ----------------------------------------------------------

SRC=main \
	printer \
	printer_sort \
	parser_ant \
	parser_room \
	parser_tube \
	parser_master \
	rb_insert \
	rb_balance \
	rb_function \
	algo_dijkstra \
	algo_pathsolver \
	algo_roadlist \
		algo_roadlist_longest \
		algo_roadlist_utils \
	algo_benjaug \
		algo_benjaug_case \
	ft_lnk_ \
	get_ \
	ft_lnod_ \
	ft_stack_
INCLUDES=	$(PATH_HDR)libft.h \
			$(PATH_HDR)lem_in.h \
			$(PATH_HDR)rb_tree.h

# --- 2.Path -------------------------------------------------------------------

PATH_SRC_ALGO=./srcs/algorithm/
PATH_SRC_PARSER=./srcs/parser/
PATH_SRC_TREE=./srcs/rb_tree/
PATH_SRC_PRINT=./srcs/print/
PATH_SRC_LIB=./srcs/lib/
PATH_SRC_MAIN=./srcs/
PATH_HDR=./includes/
PATH_OBJ=./srcs/obj/
PATH_LIB=./libft/

# --- 3.Rules ------------------------------------------------------------------

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INCLUDES)
	-@printf " ==> Creating $(NAME)\n"
	@$(CC_C)

$(LIBFT):
	-@printf " ==> Creating $(LIBFT:$(PATH_LIB)%=%)\n"
	@make -sC $(PATH_LIB) $(LIB_RULE)

$(PATH_OBJ)%.o:$(PATH_SRC_MAIN)%.c $(INCLUDES)
	-@printf " >O $(FLAGS) $(@:srcs/obj/%.o=%)\n"
	@$(CC_O) $< -o $@
$(PATH_OBJ)%.o:$(PATH_SRC_PARSER)%.c $(INCLUDES)
	-@printf " >O $(FLAGS) $(@:srcs/obj/%.o=%)\n"
	@$(CC_O) $< -o $@
$(PATH_OBJ)%.o:$(PATH_SRC_TREE)%.c $(INCLUDES)
	-@printf " >O $(FLAGS) $(@:srcs/obj/%.o=%)\n"
	@$(CC_O) $< -o $@
$(PATH_OBJ)%.o:$(PATH_SRC_ALGO)%.c $(INCLUDES)
	-@printf " >O $(FLAGS) $(@:srcs/obj/%.o=%)\n"
	@$(CC_O) $< -o $@
$(PATH_OBJ)%.o:$(PATH_SRC_LIB)%.c $(INCLUDES)
	-@printf " >O $(FLAGS) $(@:srcs/obj/%.o=%)\n"
	@$(CC_O) $< -o $@
$(PATH_OBJ)%.o:$(PATH_SRC_PRINT)%.c $(INCLUDES)
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

.PHONY: all clean fclean re O3
