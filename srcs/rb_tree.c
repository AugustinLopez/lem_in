/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:31:17 by aulopez           #+#    #+#             */
/*   Updated: 2019/06/12 10:07:15 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rb_tree.h>

void			lem_free_tree(t_rb_node **root)
{
	t_list	*tmp;

	if (!root || !*root)
		return ;
	if ((*root)->left)
		lem_free_tree(&((*root)->left));
	if ((*root)->right)
		lem_free_tree(&((*root)->right));
	if ((*root)->name)
		free((*root)->name);
	if ((tmp = (*root)->link))
	{
		while (tmp)
		{
			(*root)->link = (*root)->link->next;
			free(tmp);
			tmp = (*root)->link;
		}
	}
	free(*root);
	*root = 0;
}

static void		lem_index(t_rb_node *root, size_t *index)
{
	if (root->left)
		lem_index(root->left, index);
	root->index = *index;
	*index += 1;
	if (root->right)
		lem_index(root->right, index);
}

size_t			lem_index_tree(t_rb_node *root)
{
	size_t	index;

	if (!root)
		return (0);
	index = 0;
	if (root->left)
		lem_index(root->left, &index);
	root->index = index;
	index += 1;
	if (root->right)
		lem_index(root->right, &index);
	return (index);
}

t_rb_node		*lem_find_node(t_rb_node *root, const char *name)
{
	int			val;
	t_rb_node	*node;

	node = root;
	while (1)
	{
		if (!node)
			return (NULL);
		val = ft_strcmp(node->name, name);
		if (val == 0)
			return (node);
		node = val > 0 ? node->left : node->right;
	}
	return (NULL);
}
