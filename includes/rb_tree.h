/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 14:56:35 by aulopez           #+#    #+#             */
/*   Updated: 2019/05/31 14:56:35 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Should be merged with the other header: here to avoid conflict
*/

#ifndef RB_TREE_H
# define RB_TREE_H

# include <stdint.h>
# include <libft.h>

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
# define RB_START 2
# define RB_END 4

typedef struct			s_rb_node
{
	struct s_rbtree		*left;
	struct s_rbtree		*right;
	struct s_rbtree		*parent;
	unsigned int		x;
	unsigned int		y;
	uint8_t				flag;
	size_t				index;
	char				*name;
}						t_rb_node;

t_rb_node				*lem_rb_create(char *name, unsigned int x,
							unsigned int y, uint8_t flag);
int						rb_insert(t_rb_node **root, t_rb_node *node);
void					lem_free_tree(t_rb_node **node);
void					lem_index_tree(t_rb_node *node);
#endif
