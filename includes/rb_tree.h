/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:56:35 by aulopez           #+#    #+#             */
/*   Updated: 2019/06/10 18:30:12 by aulopez          ###   ########.fr       */
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
	long long			x;
	long long			y;
	uint8_t				flag;
	t_list				*link;
	size_t				index;
	char				*name;
}						t_rb_node;

int						rb_insert(t_rb_node **root, t_rb_node *node);
void					lem_free_tree(t_rb_node **node);
size_t					lem_index_tree(t_rb_node *node);
t_rb_node				*lem_find_node(t_rb_node *root, const char *name);
#endif
