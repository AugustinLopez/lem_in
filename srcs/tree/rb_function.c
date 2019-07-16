/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:31:17 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/16 14:22:13 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void					lem_free_tree(t_rb_node **root)
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

t_rb_node				*lem_find_node(t_rb_node *root, const char *name)
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

static inline t_rb_node	*lem_rb_create(t_lemin *lem, t_tree_data *data)
{
	t_rb_node	*tmp;

	if (!(tmp = (t_rb_node *)malloc(sizeof(*tmp))))
		return (NULL);
	ft_bzero(tmp, sizeof(*tmp));
	if (!(tmp->name = ft_strsub(data->line, 0, data->fin)))
	{
		free(tmp);
		return (NULL);
	}
	tmp->x = data->x;
	tmp->y = data->y;
	tmp->flag = RB_RED;
	if (!lem->end && (data->command & LEM_END))
		lem->end = tmp;
	else if (!lem->start && (data->command & LEM_START))
		lem->start = tmp;
	return (tmp);
}

int						lem_feed_tree(t_lemin *lem, t_tree_data *room)
{
	t_rb_node	*tmp;
	t_rb_node	*same;

	if (!(tmp = lem_rb_create(lem, room)))
		return (-1);
	if (rb_insert(&(lem->tree), tmp) == -1)
	{
		same = lem_find_node(lem->tree, tmp->name);
		free(tmp->name);
		free(tmp);
		if (same && room->x == same->x && room->y == same->y)
			return (0);
		else
			return (-1);
	}
	return (0);
}

t_rb_node				*get_node(t_list *ptr)
{
	return ((t_rb_node *)(ptr->pv));
}
