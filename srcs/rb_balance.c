/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_balance.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:06:58 by aulopez           #+#    #+#             */
/*   Updated: 2019/05/31 16:06:58 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rb_tree.h>

static int		rb_symmetrical(t_rb_node *root, int uncle, int brother)
{
	t_rb_node *tmp;

	if (brother == LEM_LEFT)
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

static int		rb_blackaunt(t_rb_node *root, int uncle, int brother)
{
	t_rb_node *tmp;

	if (uncle == LEM_LEFT)
		return (rb_symmetrical(root, uncle, brother));
	if (brother == LEM_RIGHT)
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
	root->right = root->parentl
	root->parent = root->parent->parentl
	if (root->parent)
		root->parent->left = root;
	root->right->parent = root;
	root->right->left = tmp;
	root->flag &= ~RB_RED;
	root->right->flag |= RB_RED;
	return (0);
}

static void		rb_balance(t_rb_node *root, int brother)
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
		(void)rb_blackaunt(root, uncle, brother);
}

static int		launch_recursive(t_rb_node **root, t_rb_node *node)
{
	int	val;

	if (node->name)
		val = ft_strcmp((*root)->name, node->name);
	else
		val = (*root)->x == node->x
			? (*root)->y - node->y : (*root)->x - node->x;
	if (!val)
		return (LEM_FALSE);
	if (val < 0 && (*root)->left)
		return (launch_recursive(&((*root)->left), node));
	else if (val > 0 && (*root)->right)
		return (launch_recursive(&((*root)->right), node));
	else if (val < 0)
	{
		(*root)->right = node;
		rb_balance(*root, LEM_RIGHT);
		return (LEM_TRUE);
	}
	(*root)->left = node;
	rb_balance(*root, LEM_LEFT);
	return (LEM_TRUE);
}

int				rb_insert(t_rb_node **root, t_rb_node *node)
{
	if (!root || !node)
		return (LEM_FALSE);
	if (!*root)
	{
		*root = node;
		node->flag &= ~RB_RED;
	}
	else
	{
		if (launch_recursive(root, node) == LEM_FALSE)
			return (LEM_FALSE);
		while ((*root)->parent)
			*root = (*root)->parent;
		(*root)->flag &= ~RB_RED;
	}
	return (LEM_TRUE);
}
