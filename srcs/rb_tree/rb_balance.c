/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_balance.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:06:58 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/23 11:44:59 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rb_tree.h"

static inline void	simplify_to_right(t_rb_node **node)
{
	t_rb_node	*tmp;

	tmp = (*node)->right;
	if (tmp)
		tmp->parent = (*node)->parent;
	(*node)->right = (*node)->parent;
	(*node)->parent = (*node)->parent->parent;
	(*node)->parent->right = *node;
	(*node)->right->parent = *node;
	(*node)->right->left = tmp;
}

static inline void	balance_black_uncle_right(t_rb_node **node, int am_i_left)
{
	t_rb_node	*tmp;

	if (am_i_left)
		simplify_to_right(node);
	*node = am_i_left ? *node : (*node)->parent;
	(*node)->color &= ~RB_RED;
	(*node)->parent->color |= RB_RED;
	if ((tmp = (*node)->left))
		tmp->parent = (*node)->parent;
	(*node)->left = (*node)->parent;
	(*node)->left->right = tmp;
	(*node)->parent = (*node)->left->parent;
	(*node)->left->parent = *node;
	if (!((*node)->parent))
		return ;
	if ((*node)->parent->left == (*node)->left)
		(*node)->parent->left = *node;
	else
		(*node)->parent->right = *node;
}

static inline void	simplify_to_left(t_rb_node **node)
{
	t_rb_node	*tmp;

	tmp = (*node)->left;
	if (tmp)
		tmp->parent = (*node)->parent;
	(*node)->left = (*node)->parent;
	(*node)->parent = (*node)->parent->parent;
	(*node)->parent->left = *node;
	(*node)->left->parent = *node;
	(*node)->left->right = tmp;
}

static inline void	balance_black_uncle_left(t_rb_node **node, int am_i_left)
{
	t_rb_node	*tmp;

	if (!am_i_left)
		simplify_to_left(node);
	*node = !am_i_left ? *node : (*node)->parent;
	(*node)->color &= ~RB_RED;
	(*node)->parent->color |= RB_RED;
	if ((tmp = (*node)->right))
		tmp->parent = (*node)->parent;
	(*node)->right = (*node)->parent;
	(*node)->right->left = tmp;
	(*node)->parent = (*node)->right->parent;
	(*node)->right->parent = *node;
	if (!((*node)->parent))
		return ;
	if ((*node)->parent->left == (*node)->right)
		(*node)->parent->left = *node;
	else
		(*node)->parent->right = *node;
}

void				rb_balance(t_rb_node **node, int am_i_left)
{
	t_rb_node	*uncle;
	t_rb_node	*parent;
	int			is_parent_left;

	parent = (*node)->parent;
	if (!parent)
		(*node)->color &= ~RB_RED;
	if (!parent || !(parent->color & RB_RED))
		return ;
	is_parent_left = parent->parent && parent->parent->left == parent ? 1 : 0;
	uncle = is_parent_left ? parent->parent->right : parent->parent->left;
	if (uncle && uncle->color & RB_RED)
	{
		parent->color &= ~RB_RED;
		uncle->color &= ~RB_RED;
		parent->parent->color |= RB_RED;
		parent = parent->parent;
		is_parent_left = (parent->parent && parent->parent->left == parent)
			? 1 : 0;
		rb_balance(&parent, is_parent_left);
	}
	else if (is_parent_left)
		balance_black_uncle_left(node, am_i_left);
	else
		balance_black_uncle_right(node, am_i_left);
}
