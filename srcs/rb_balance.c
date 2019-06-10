/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_balance.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:06:58 by aulopez           #+#    #+#             */
/*   Updated: 2019/06/10 18:04:29 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rb_tree.h>

/*static int		rb_symmetrical(t_rb_node *root, int am_i_left)
{
	t_rb_node *tmp;

	if (am_i_left == LEM_LEFT)
	{
		if ((tmp = root->left->right))
			tmp->parent = root;
		root->left->right = root;
		root->left->parent = root->parent;
		root->parent = root->left;
		root->left = tmp;
		root = root->parent;
	}
	if ((tmp = root->left))
		tmp->parent = root->parent;
	root->left = root->parent;
	root->parent = root->parent->parent;
	if (root->parent)
		root->parent->right = root;
	root->left->parent = root;
	root->left->right = tmp;
	root->flag &= ~RB_RED;
	root->left->flag |= RB_RED;
	return (0);
}

static int		rb_blackaunt(t_rb_node *root, int uncle, int am_i_left)
{
	t_rb_node *tmp;

	if (uncle == LEM_LEFT)
		return (rb_symmetrical(root, am_i_left));
	if (am_i_left == LEM_RIGHT)
	{
		if ((tmp = root->right->left))
			tmp->parent = root;
		root->right->left = root;
		root->right->parent = root->parent;
		root->parent = root->right;
		root->right = tmp;
		root = root->parent;
	}
	if ((tmp = root->right))
		tmp->parent = root->parent;
	root->right = root->parent;
	root->parent = root->parent->parent;
	if (root->parent)
		root->parent->left = root;
	root->right->parent = root;
	root->right->left = tmp;
	root->flag &= ~RB_RED;
	root->right->flag |= RB_RED;
	return (0);
}*/

/*static void		rb_balance(t_rb_node **node, int am_i_left)
{
	t_rb_node	*aunt;
	int			uncle;

	if (!root->parent || !(root->flag & RB_RED))
	{
		root->flag &= ~RB_RED;
		return ;
	}
	uncle = (root->parent->left == root) ? LEM_LEFT : LEM_RIGHT;
	aunt = uncle == LEM_LEFT ? root->parent->right : root->parent->left;
	if (aunt && (aunt->flag & RB_RED))
	{
		aunt->flag &= ~RB_RED;
		root->flag &= ~RB_RED;
		root->parent->flag |= RB_RED;
		if (root->parent->parent)
			rb_balance(root->parent->parent,
					(root->parent->parent->left == root->parent));
	}
	else
		(void)rb_blackaunt(root, uncle, am_i_left);
}*/

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

void			balance_black_uncle(t_rb_node **node, int am_i_left, int is_parent_left)
{
	t_rb_node *tmp;

	if (is_parent_left && !am_i_left)
	{
		(*node)->left = (*node)->parent;
		(*node)->parent = (*node)->parent->parent;
		(*node)->parent->left = *node;
		(*node)->left->parent = *node;
		(*node)->left->right = 0;
		(*node) = (*node)->left;
	}
	else if (!is_parent_left && am_i_left)
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
	if (is_parent_left)
	{
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
	else
	{
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
	else
		balance_black_uncle(node, am_i_left, is_parent_left);
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
