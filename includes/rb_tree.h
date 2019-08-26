/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:56:35 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/26 11:48:20 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_H
# define RB_TREE_H

/*
** stdlib for malloc/free
** stddef for size_t
*/

# include <stdlib.h>
# include <stddef.h>

# define RB_RED 1

typedef struct		s_link
{
	void			*origin;
	void			*target;
	struct s_link	*reverse;
	struct s_link	*next;
	size_t			depth;
	size_t			exploration;
	uint8_t			solution;
}					t_link;

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
	char				*name;
	t_link				*link;
	t_link				*origin_link;
	size_t				nbr_link;
	size_t				depth;
	size_t				exploration;
	uint8_t				solution;
	uint8_t				color;
}						t_rb_node;

void					rb_balance(t_rb_node **node, int am_i_left);
int						rb_insert(t_rb_node **root, t_rb_node *node);
void					lem_free_tree(t_rb_node **node);
t_rb_node				*lem_find_node(t_rb_node *root, const char *name);
int						ft_lnknew(t_rb_node *origin, t_rb_node *target);
void					ft_lnkdel(t_rb_node *node);
#endif
