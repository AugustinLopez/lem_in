/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ek_pathfinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/21 11:41:48 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

static inline int	check_for_end(t_lemin *lem, t_fifo *fifo)
{
	t_rb_node	*node;
	t_list		*tmp;

	tmp = get_node(fifo->first)->link;
	while (tmp)
	{
		if ((node = get_node(tmp)) == lem->end)
		{
			if (tmp->zu < fifo->n)
			{
				tmp->zu = fifo->n;
				return (1);
			}
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
** 1st: link solved or already visited
** 2nd: node already visited (not solved)
** 3rd: cannot reverse a link already visited (not solved)
** 4th: Special case from 5th.
** 5th: going to a solved node but without reversing a path.
** - we launch a loop to verify if the need has already been visited during
** this iteration.
** - If not already visited, special case: the next iteration through from this
** solved node will have to reverse a solved path (ret == 1)
*/

static inline int	check_node_validity(t_lemin *lem, t_fifo *fifo,
						t_list *link, t_list *rev)
{
	t_list	*tmp;
	t_rb_node *node;

	(void)lem;
	node = get_node(link);
	if (link->zu >= fifo->n
		|| node->visited == fifo->n
		|| rev->zu == fifo->n
		|| (fifo->first->zu == 1 && rev->zu != fifo->max))
		return (-1);
	if (node->visited == fifo->max && rev->zu != fifo->max)
	{
		tmp = node->link;
		while (tmp)
		{
			if (tmp->zu == fifo->n)
				return (-1);
			tmp = tmp->next;
		}
	//	node->visited = fifo->n;
		return (1);
	}
	if (rev->zu == fifo->max)
	{
		if (get_node(fifo->first)->flag == 0)
			return (-1);
	//	node->visited = fifo->n;
	//	get_node(rev)->visited = fifo->n;
		return (2);
	}
	return (0);
}

static inline int	add_node(t_fifo *fifo, t_rb_node *node, t_list *link,
						int ret)
{
	t_list	*tmp;
	t_list	*iter;

	if (node->visited < fifo->n)
		node->visited = fifo->n;
	node->flag = get_node(fifo->first)->flag;
	node->flag += (ret != 2) ? 1 : -1;
	link->zu = fifo->n;
	if (!(tmp = ft_lstnew(0, 0)))
		return (-1);
	tmp->pv = node;
	tmp->zu = (ret == 1) ? 1 : 0;
	iter = fifo->first;
	while (iter->next && get_node(iter->next)->flag <= node->flag)
		iter = iter->next;
	if (iter->next)
	{
		tmp->next = iter->next;
		iter->next = tmp;
		return (0);
	}
	fifo->last->next = tmp;
	fifo->last = fifo->last->next;
	return (0);
}

/*
** PATHFINDER:
** Return 1 if a new path is found
** Return 0 if no new path.
** Return -1 if not enough memory
*/

int					pathfinder(t_lemin *lem, t_fifo *fifo)
{
	t_rb_node	*node;
	t_list		*link;
	t_list		*rev;
	int			ret;

	if (check_for_end(lem, fifo))
		return (1);
	link = get_node(fifo->first)->link;

	//*1
	t_list	*tmp;
	/*tmp = fifo->first;
	while (tmp)
	{
		ft_printf("%s->", get_node(tmp)->name);
		tmp = tmp->next;
	}
	ft_printf("\n");*/
	//*1
	while (link)
	{
		node = get_node(link);
		rev = get_reverse_path(get_node(fifo->first), link);
		if ((ret = check_node_validity(lem, fifo, link, rev)) != -1)
		{
			if (add_node(fifo, node, link, ret) == -1)
				return (-1);
		}
		else if (node->visited == fifo->n && get_node(rev)->flag + 1 < node->flag)
		{
		//3
			tmp = node->link;
			while (tmp)
			{
				if (get_reverse_path(node, tmp)->zu == fifo->n)
				{
					get_reverse_path(node, tmp)->zu = 0;
					link->zu = fifo->n;
					node->flag = get_node(rev)->flag + 1;
					break ;
				}
				tmp = tmp->next;
			}
			if (add_node(fifo, node, link, ret) == -1)
				return (-1);
		//3
		}
		link = link->next;
	}
	return (0);
}

/*
** PATHSOLVER:
** Pathfinder is the exploration part. Once a valid path is found, some
** additional step are taken so we can identify the new path and modify
** the graph accordingly.
*/

void				pathsolver(t_lemin *lem, t_fifo *fifo)
{
	t_list		*path;
	t_list		*rev;
	t_rb_node	*node;

	node = lem->end;
	path = node->link;
	while (get_reverse_path(node, path)->zu != fifo->n)
		path = path->next;
	while (node != lem->start)
	{
	//	ft_printf("%s", node->name);
		path = node == lem->end ? path : node->link;
		rev = get_reverse_path(node, path);
		while (rev->zu != fifo->n)
		{
			path = path->next;
			rev = get_reverse_path(node, path);
		}
	//	ft_printf("(%zu|%zu|%zu)==>", rev->zu, path->zu, node->visited);
		rev->zu = (path->zu == fifo->max) ? 0 : fifo->max;
		path->zu = (path->zu == fifo->max) ? 0 : path->zu;
		node = get_node(path);
		node->visited = fifo->max;
	}
//	ft_printf("\n");
}
