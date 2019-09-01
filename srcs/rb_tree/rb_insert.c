/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:06:58 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/02 00:30:54 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rb_tree.h"

static inline int	launch_coordinate(t_rb_node **root, t_rb_node **node)
{
	int	val;

	if (!*root)
	{
		(*root) = *node;
		return (0);
	}
	else if ((*root)->x == (*node)->x && (*root)->y == (*node)->y)
		return (-1);
	else if ((*root)->x < (*node)->x
			|| ((*root)->x == (*node)->x && (*root)->y < (*node)->y))
		val = 1;
	else
		val = -1;
	if (val == 1 && (*root)->left)
		return (launch_coordinate(&((*root)->left), node));
	else if (val == 1)
		(*root)->left = *node;
	else if ( val == -1 && (*root)->right)
		return (launch_coordinate(&((*root)->right), node));
	else
		(*root)->right = *node;
	(*node)->parent = (*root);
	return (0);
}

int					rb_coordinate(t_rb_node **root, t_rb_node *node)
{
	if (!root || !node)
		return (-1);
	if (launch_coordinate(root, &node) == -1)
		return (-1);
	rb_balance(&node, node->parent && node->parent->left == node ? 1 : 0);
	while (node->parent != NULL)
		node = node->parent;
	*root = node;
	(*root)->color &= ~RB_RED;
	return (0);
}

static inline int	launch_recursive(t_rb_node **root, t_rb_node **node)
{
	int	val;

	if (!*root)
	{
		(*root) = *node;
		return (0);
	}
	else if (!(val = ft_strcmp((*root)->name, (*node)->name)))
		return (-1);
	else if (val > 0 && (*root)->left)
		return (launch_recursive(&((*root)->left), node));
	else if (val < 0 && (*root)->right)
		return (launch_recursive(&((*root)->right), node));
	else if (val > 0)
		(*root)->left = *node;
	else
		(*root)->right = *node;
	(*node)->parent = (*root);
	return (0);
}

int					rb_insert(t_rb_node **root, t_rb_node *node)
{
	if (!root || !node)
		return (-1);
	if (launch_recursive(root, &node) == -1)
		return (-1);
	rb_balance(&node, node->parent && node->parent->left == node ? 1 : 0);
	while (node->parent != NULL)
		node = node->parent;
	*root = node;
	(*root)->color &= ~RB_RED;
	return (0);
}
