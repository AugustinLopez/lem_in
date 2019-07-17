/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmundkarp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/17 14:46:03 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

static inline int	free_fifo(t_fifo *fifo, int ret)
{
	t_list	*tmp;

	while (fifo->first)
	{
		tmp = fifo->first->next;
		free(fifo->first);
		fifo->first = tmp;
	}
	return (ret);
}

t_list		*get_reverse_path(t_rb_node *node, t_list *path)
{
	t_list		*tmp;
	t_rb_node	*rev;

	rev = get_node(path);
	tmp = rev->link;
	while (tmp)
	{
		if (get_node(tmp) == node)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

int			check_for_end(t_lemin *lem, t_fifo *fifo)
{
	t_rb_node	*node;
	t_list		*tmp;
	t_list		*link;


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
** 4th: going to a solved node but without reversing a path.
** - we launch a loop to verify if the need has already been visited during
** this iteration.
** - If not already visited, special case: the next iteration through from this
** solved node will have to reverse a solved path (ret == 1)
** 5th: Special case from 4th.
*/

int			check_node_validity(t_fifo *fifo, t_rb_node *node, t_list *link, t_list *rev)
{
	t_list	*tmp;

	if (link->zu >= fifo->n)
		return (-1);
	if (node->visited == fifo->n)
		return (-1);
	if (rev->zu == fifo->n)
		return (-1);
	if (fifo->first->zu == 1 && rev->zu != fifo->max)
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
		return (1);
	}
	if (fifo->first->zu == 1 && rev->zu != fifo->max)
		return (-1);
	return (0);
}

int			add_valid_node(t_fifo *fifo, t_rb_node *node, t_list *link, int ret)
{
	t_list	*tmp;

	if (node->visited < fifo->n)
		node->visited = fifo->n;
	link->zu = fifo->n;
	if (!(tmp = ft_lstnew(0, 0)))
		return (-1);
	tmp->pv = node;
	tmp->zu = ret;
	fifo->last->next = tmp;
	fifo->last = fifo->last->next;
	return (0);
}

int			link_loop(t_lemin *lem, t_fifo *fifo)
{
	t_rb_node	*node;
	t_list		*link;
	t_list		*rev;
	int			ret;

	if (check_for_end(lem, fifo))
		return (1);
	link = get_node(fifo->first)->link;
	while (link)
	{
		node = get_node(link);
		rev = get_reverse_path(get_node(fifo->first), link);
		if ((ret = check_node_validity(fifo, node, link, rev)) != -1)
			if (add_valid_node(fifo, node, link, ret) == -1)
				return (-1);
		link = link->next;
	}
	return (0);
}

void		solve_new_path(t_lemin *lem, t_fifo *fifo)
{
	t_list		*path;
	t_rb_node	*node;
	t_list		*rev;

	node = lem->end;
	path = node->link;
	while (get_reverse_path(node, path)->zu != fifo->n)
		path = path->next;
	while (node != lem->start)
	{
		path = node == lem->end ? path : node->link;
		rev = get_reverse_path(node, path);
		while (rev->zu != fifo->n)
		{
			path = path->next;
			rev = get_reverse_path(node, path);
		}
		rev->zu = fifo->max;
		if (rev->zu == path->zu)
		{
			rev->zu = 0;
			path->zu = 0;
		}
		node = get_node(path);
		node->visited = fifo->max;
	}
}

void		find_new_paths(t_lemin *lem, t_fifo *fifo)
{
	t_list		*path;
	t_list		*mem;
	t_rb_node	*node;
	t_list		*rev;
	size_t		j;
	size_t		i;

	j = 0;
	mem = lem->end->link;
	while (++j < fifo->n + 1)
	{
		i = 0;
		node = lem->end;
		ft_printf("%d: %s<-", j, node->name);
		while (get_reverse_path(node, mem)->zu != fifo->max)
			mem = mem->next;
		path = mem;
		mem = mem->next;
		while (node != lem->start)
		{
			path = node == lem->end ? path : node->link;
			rev = get_reverse_path(node, path);
			while (rev->zu != fifo->max)
			{
				path = path->next;
				rev = get_reverse_path(node, path);
			}
			node = get_node(path);
			if (!(node == lem->start))
				ft_printf("%s<-", node->name);
			i++;
		}
		ft_printf("%s : %d\n", lem->start->name, i);
	}
	ft_printf("\n");
}

int			iteratif_edmundkarp(t_lemin *lem, t_fifo *fifo)
{
	int		ret;
	t_list	*tmp;

	while (fifo->first)
	{
		if ((ret = link_loop(lem, fifo)))
			break ;
		tmp = fifo->first;
		fifo->first = fifo->first->next;
		free(tmp);
	}
	if (ret == 1)
	{
		solve_new_path(lem, fifo);
		find_new_paths(lem, fifo);
		return (0);
	}
	ft_dprintf(STDERR_FILENO, "No more found. Apparently\n");
	return (-1);
	
}

int			edmundkarp(t_lemin *lem)
{
	t_fifo	fifo;
	int		ret;

	if (!lem->start->nbr_link || !lem->end->nbr_link)
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (-1);
	}
	ft_bzero(&fifo, sizeof(fifo));
	fifo.max = lem->start->nbr_link < lem->end->nbr_link
		? lem->start->nbr_link + 1 : lem->end->nbr_link + 1;
	fifo.n = 0;
	while (++(fifo.n) < fifo.max)
	{
		if (!(fifo.first = ft_lstnew(0, 0)))
		{
			ft_dprintf(STDERR_FILENO, "ERROR\n");
			return (-1);
		}
		(fifo.first)->pv = lem->start;
		fifo.last = fifo.first;
		ret = iteratif_edmundkarp(lem, &fifo);
		free_fifo(&fifo, ret);
	}
	return (ret);
}
