/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:56:35 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/22 16:56:18 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_H
# define RB_TREE_H

/*
** stdlib for malloc/free
** stddef for size_t
*/

# include "libft.h"
# include <stdlib.h>
# include <stddef.h>

/*
** The 1st bit of our flag is the color.
** The 2nd bit indicates the starting room.
** The 3rd bit indicates the final room.
*/

typedef struct		s_link
{
	void			*origin;
	void			*target;
	int				solution;
	int				etape;
	struct s_link	*reverse;
	struct s_link	*next;
}					t_link;

typedef struct		s_road
{
	t_link			*km;
	size_t			length;
	struct s_road	*next;
}					t_road;

# define RB_RED 1

typedef struct			s_tree_data
{
	char				*line;
	size_t				fin;
	long long			x;
	long long			y;
}						t_tree_data;

typedef struct			s_rb_node
{
	struct s_rb_node	*left;
	struct s_rb_node	*right;
	struct s_rb_node	*parent;
	long long			x;
	long long			y;
	size_t				nbr_link;
	size_t				visited;
	t_link				*link;
	char				*name;
	size_t				flag;
}						t_rb_node;

void					rb_balance(t_rb_node **node, int am_i_left);
int						rb_insert(t_rb_node **root, t_rb_node *node);
void					lem_free_tree(t_rb_node **node);
t_rb_node				*lem_find_node(t_rb_node *root, const char *name);

#endif
