# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:20 by bcarlier          #+#    #+#              #
#    Updated: 2019/07/09 16:26:06 by aulopez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=lem_in
LIBFT=$(PATH_LIB)libft.a

FLAGS=-Wall -Wextra -Werror
LIB_RULE=
CC_O=gcc $(FLAGS) -c -I$(PATH_HDR)
CC_C=gcc $(FLAGS) -o $(NAME) $(OBJ) -I$(PATH_HDR) -L$(PATH_LIB) -lft
OBJ=$(SRC:%=$(PATH_OBJ)%.o)

# --- 1.Source/Header ----------------------------------------------------------

SRC=main \
	reader_ant \
	reader_room \
	reader_tube \
	reader_master \
	rb_tree \
	rb_function \
	dijkstra \
	lst \
	remove_bad_paths
INCLUDES=	$(PATH_HDR)libft.h \
			$(PATH_HDR)lem_in.h \
			$(PATH_HDR)rb_tree.h

# --- 2.Path -------------------------------------------------------------------

PATH_HDR=./includes/
PATH_OBJ=./srcs/obj/
PATH_SRC=./srcs/
PATH_LIB=./libft/

# --- 3.Rules ------------------------------------------------------------------

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INCLUDES)
	-@printf " ==> Creating $(NAME)\n"
	@$(CC_C)

$(LIBFT):
	-@printf " ==> Creating $(LIBFT:$(PATH_LIB)%=%)\n"
	@make -sC $(PATH_LIB) $(LIB_RULE)

$(PATH_OBJ)%.o:$(PATH_SRC)%.c $(INCLUDES)
	-@printf " >O $(FLAGS) $(@:obj/%.o=%)\n"
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
O3: all;
O2: FLAGS += -O2
O2: LIB_RULE = O2
O2: all;
Os: FLAGS += -Os
Os: LIB_RULE = Os
Os: all;
g3: FLAGS = -g3 -fsanitize=address
g3: LIB_RULE = g3
g3: all;
pedantic: FLAGS += -pedantic
pedantic: LIB_RULE = pedantic
pedantic: all;

.PHONY: all clean fclean re O3 O2 Os g3 pedantic
