/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:31:17 by aulopez           #+#    #+#             */
/*   Updated: 2019/05/31 15:31:17 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rb_tree.h>

/*
** We will create 2 RB tree: one for name check and one for coordinate check.
** When we have finished checking for duplicates, we can destroy the 2nd tree.
**
** We will create 2 nodes at each iteration with 2 memory allocation.
** If an allocations fails, we destroy both trees and end the program.
** Once a node is created, it in placed in our tree. Even in case of duplicata.
** If a duplicatas as been found, we destroy both trees and end the program.
** Tree one requires an additional malloc for the name. No need for 2nd tree.
*/

t_rb_node		*lem_rb_create(char *name, unsigned int x, unsigned int y,
					uint8_t flag)
{
	t_rb_node	*tmp;
	char		*str;

	if (!(tmp = (t_rb_node *)malloc(sizeof(*tmp))))
		return (NULL);
	if (!name)
		tmp->name = 0;
	else if (!(tmp->name = ft_strdup(name)))
	{
		free(tmp);
		return (NULL);
	}
	tmp->x = x;
	tmp->y = y;
	tmp->flag = flag | RB_RED;
	tmp->left = 0;
	tmp->right = 0;
	tmp->parent = 0;
	return (tmp);
}

void			lem_free_tree(t_rb_node **root)
{
	if (!root || !*root)
		return ;
	if ((*root)->left)
		lem_free_tree(&((*root)->left));
	if ((*root)->right)
		lem_free_tree(&((*root)->right));
	if ((*root)->name)
		free((*root)->name);
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

void			lem_index_tree(t_rb_node *root)
{
	size_t	index;

	if (!root)
		return ;
	index = 0;
	if (root->left)
		lem_index(root->left, index);
	root->index = index;
	index += 1;
	if (root->right)
		lem_index(root->right, index);
}
