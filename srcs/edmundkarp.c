/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmundkarp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/15 22:01:14 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

static inline int	free_fifo2(t_fifo *fifo, int ret)
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

int			already_visited_this_loop(t_fifo *fifo, t_rb_node *node)
{
	t_list	*start;

	start = fifo->first;
	while (start != fifo->cur)
	{
		if (get_node(start) == node)
			return (1);
		start = start->next;
	}
	return (0);
}

int			check_for_end(t_lemin *lem, t_fifo *fifo)
{
	t_rb_node	*node;
	t_list		*tmp;
	t_list		*link;


	tmp = get_node(fifo->cur)->link;
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

int			already_checked_this_loop(t_fifo *fifo, t_rb_node *node)
{
	t_list	*start;

	start = fifo->first;
	while (start != fifo->cur)
	{
		if (get_node(start) == node)
			return (1);
		start = start->next;
	}
	return (0);
}

int			link_loop2(t_lemin *lem, t_fifo *fifo)
{
	t_rb_node	*node;
	t_list		*link;
	t_list		*tmp;

	if (check_for_end(lem, fifo))
		return (1);
	link = get_node(fifo->cur)->link;
	while (link)
	{
		node = get_node(link);
		if (link->zu > fifo->n || node->visited == fifo->n)
		{
			link = link->next;
			continue ;
		}
		if (node->visited < fifo->n)
			node->visited = fifo->n;
		if (link->zu < fifo->n)
			link->zu = fifo->n;
		if (!(tmp = ft_lstnew(0, 0)))
			return (-1);
		tmp->pv = node;
		fifo->last->next = tmp;
		fifo->last = fifo->last->next;
		link = link->next;
	}
	return (0);
}

void		explore_n(t_lemin *lem, t_fifo *fifo)
{
	t_list		*tmp;
	t_list		*mem;
	t_list		*rev;
	t_rb_node	*node;
	t_rb_node	*end;
	size_t		x;
	size_t		i;
	size_t		j;

	j = 0;
	end = lem->end;
	mem = end->link;
	while (j < fifo->n + 1)
	{
		i = 0;
		if (j == 0)
			while (get_reverse_path(end, mem)->zu != fifo->n)
				mem = mem->next;
		else
			while (get_reverse_path(end, mem)->zu != fifo->max)
				mem = mem->next;
		x = get_reverse_path(end, mem)->zu;
		tmp = mem;
		mem = mem->next;
		node = end;
		ft_printf("%d: %s<-", j, node->name);
		while (node != lem->start)
		{
			tmp = node == end ? tmp : node->link;
			rev = get_reverse_path(node, tmp);
			while (rev->zu != x)
			{
				tmp = tmp->next;
				rev = get_reverse_path(node, tmp);
			}
			rev->zu = fifo->max;
			if (rev->zu == tmp->zu)
			{
				rev->zu = 0;
				tmp->zu = 0;
			}
			node = get_node(tmp);
			node->visited = fifo->max;
			i++;
			if (!(node == lem->start))
				ft_printf("%s<-", node->name);
		}
		ft_printf("%s : %d\n", lem->start->name, i);
		if (j == 0)
			mem = end->link;
		++j;
	}
	ft_printf("\n");
}

int			iteratif_edmundkarp(t_lemin *lem, t_fifo *fifo)
{
	int		ret;
	t_list	*tmp;

	while (fifo->cur)
	{
		if ((ret = link_loop2(lem, fifo)))
			break ;
		fifo->cur = fifo->cur->next;
	}
	if (ret == 1)
	{
		explore_n(lem, fifo);
		return (0);
	}
	ft_dprintf(STDERR_FILENO, "ERROR\n");
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
	while (++(fifo.n) < fifo.max)
	{
		if (!(fifo.first = ft_lstnew(0, 0)))
		{
			ft_dprintf(STDERR_FILENO, "ERROR\n");
			return (-1);
		}
		(fifo.first)->pv = lem->start;
		fifo.last = fifo.first;
		fifo.cur = fifo.first;
		ret = iteratif_edmundkarp(lem, &fifo);
		free_fifo2(&fifo, ret);
	}
	return (ret);
}
