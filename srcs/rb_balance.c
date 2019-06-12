/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_balance.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:06:58 by aulopez           #+#    #+#             */
/*   Updated: 2019/06/12 10:16:33 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rb_tree.h>

static int		launch_recursive(t_rb_node **root, t_rb_node **node)
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

void			balance_black_uncle_right(t_rb_node **node, int am_i_left)
{
	t_rb_node	*tmp;

	if (am_i_left)
	{
		(*node)->right = (*node)->parent;
		(*node)->parent = (*node)->parent->parent;
		(*node)->parent->right = *node;
		(*node)->right->parent = *node;
		(*node)->right->left = 0;
		*node = (*node)->right;
	}
	*node = (*node)->parent;
	(*node)->flag &= ~RB_RED;
	(*node)->parent->flag |= RB_RED;
	if ((tmp = (*node)->left))
		tmp->parent = (*node)->parent;
	(*node)->left = (*node)->parent;
	(*node)->left->right = tmp;
	(*node)->parent = (*node)->left->parent;
	(*node)->left->parent = *node;
	if ((*node)->parent)
	{
		if ((*node)->parent->left == (*node)->left)
			(*node)->parent->left = *node;
		else
			(*node)->parent->right = *node;
	}
}

void			balance_black_uncle_left(t_rb_node **node, int am_i_left)
{
	t_rb_node *tmp;

	if (!am_i_left)
	{
		(*node)->left = (*node)->parent;
		(*node)->parent = (*node)->parent->parent;
		(*node)->parent->left = *node;
		(*node)->left->parent = *node;
		(*node)->left->right = 0;
		(*node) = (*node)->left;
	}
	*node = (*node)->parent;
	(*node)->flag &= ~RB_RED;
	(*node)->parent->flag |= RB_RED;
	if ((tmp = (*node)->right))
		tmp->parent = (*node)->parent;
	(*node)->right = (*node)->parent;
	(*node)->right->left = tmp;
	(*node)->parent = (*node)->right->parent;
	(*node)->right->parent = *node;
	if ((*node)->parent)
	{
		if ((*node)->parent->left == (*node)->right)
			(*node)->parent->left = *node;
		else
			(*node)->parent->right = *node;
	}
}

void			rb_balance(t_rb_node **node, int am_i_left)
{
	t_rb_node	*uncle;
	t_rb_node	*parent;
	int			is_parent_left;

	parent = (*node)->parent;
	if (!parent)
		(*node)->flag &= ~RB_RED;
	if (!parent || !(parent->flag & RB_RED))
		return ;
	is_parent_left = parent->parent && parent->parent->left == parent ? 1 : 0;
	uncle = is_parent_left ? parent->parent->right : parent->parent->left;
	if (uncle && uncle->flag & RB_RED)
	{
		parent->flag &= ~RB_RED;
		uncle->flag &= ~RB_RED;
		parent->parent->flag |= RB_RED;
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

int				rb_insert(t_rb_node **root, t_rb_node *node)
{
	if (!root || !node)
		return (-1);
	if (launch_recursive(root, &node) == -1)
		return (-1);
	rb_balance(&node, node->parent && node->parent->left == node ? 1 : 0);
	while (node->parent != NULL)
		node = node->parent;
	*root = node;
	(*root)->flag &= ~RB_RED;
	return (0);
}
