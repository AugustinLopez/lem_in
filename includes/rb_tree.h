/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:56:35 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/08 15:25:36 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Should be merged with the other header: here to avoid conflict
*/

#ifndef RB_TREE_H
# define RB_TREE_H

# include <stdint.h>
# include <libft.h>
# include <stdlib.h>
# include <rb_tree.h>

/*
** The 1st bit of our flag is the color.
** The 2nd bit indicates the starting room.
** The 3rd bit indicates the final room.
*/

# define LEM_FALSE 0
# define LEM_TRUE 1
# define LEM_LEFT 0
# define LEM_RIGHT 1

# define RB_RED 1
# define RB_START 3
# define RB_END 4

typedef struct			s_tree_data
{
	char				*line;
	size_t				fin;
	long long			x;
	long long			y;
	int					command;
}						t_tree_data;

typedef struct			s_rb_node
{
	struct s_rb_node	*left;
	struct s_rb_node	*right;
	struct s_rb_node	*parent;
	struct s_rb_node	*prev;
	long long			x;
	long long			y;
	int					flag; //flag and nbr_link could be combined
	size_t				nbr_link;
	t_list				*link;
	char				*name;
}						t_rb_node;

int						rb_insert(t_rb_node **root, t_rb_node *node);
void					lem_free_tree(t_rb_node **node);
t_rb_node				*lem_find_node(t_rb_node *root, const char *name);
#endif
