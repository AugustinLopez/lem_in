/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/11 13:39:21 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>

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

static inline int	path_found(t_rb_node *node, t_lemin *lem)
{
	t_list	*tmp;
	t_list	*start;

	tmp = NULL;
	while (node)
	{
		if (!tmp)
		{
			if (!(start = ft_lstnew(0, 0)))
				return (-1);
			lem->dijkstra = start;
			tmp = start;
		}
		else
		{
			if (!(tmp->next = ft_lstnew(0, 0)))
				return (-1);
			tmp = tmp->next;
		}
		tmp->pv = node;
		node = node->prev;
		//if (node == lem->end)
		//	break ;
	}
	if (!(lem->path))
	{
		if (!(lem->path = ft_lstnew(0, 0)))
			return (-1);
		lem->path->pv = start;
		lem->path->zu = ft_lstsize(start);
	}
	else
	{
		if (!(tmp = ft_lstnew(0, 0)))
			return (-1);
		ft_lstadd(&(lem->path), tmp);
		lem->path->pv = start;
		lem->path->zu = ft_lstsize(start);
	}
	return (1);
}

static inline int	link_loop(t_list *lst, t_lemin *lem, t_fifo *fifo)
{
	t_rb_node	*node;
	t_list		*tmp;

	tmp = lst;
	while (tmp)
	{
		if ((node = get_node(tmp)) == lem->end)
		{
			lem->end->prev = get_node(fifo->first);
			if (path_found(node, lem) == -1)
				return (-1);
			lem->end->prev = 0;
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = fifo->first;
	while (lst)
	{
		node = get_node(lst);
		if (node->prev || node == lem->start)
		{
			lst = lst->next;
			continue ;
		}
		node->prev = get_node(tmp);
		if (!(fifo->tmp = ft_lstnew(0, 0)))
			return (-1);
		fifo->tmp->pv = node;
		fifo->last->next = fifo->tmp;
		fifo->last = fifo->tmp;
		lst = lst->next;
	}
	return (0);
}

static inline int	iteratif_dijkstra(t_lemin *lem, t_fifo *fifo)
{
	int		ret;

	while (fifo->first)
	{
		ft_printf("%s\n", get_node(fifo->first)->name);
		if ((ret = link_loop(get_node(fifo->first)->link, lem, fifo)))
			break ;
		fifo->tmp = fifo->first->next;
		free(fifo->first);
		fifo->first = fifo->tmp;
	}
	if (lem->path && !ret)
		return (free_fifo(fifo, 0));
	ft_dprintf(STDERR_FILENO, "ERROR\n");
	return (free_fifo(fifo, -1));
}

/*
** We use a FIFO stack for the modified Dijkstra algorithm.
** We keep track of the weight and the length: this is to avoid a situation
** where if two node A and B have the same length and can only pass through
** X carrefour, A monopolize the X carrefour simply because it is treated first
*/

int					dijkstra(t_lemin *lem)
{
	t_fifo		fifo;

	ft_bzero(&fifo, sizeof(fifo));
	if (!lem->start->nbr_link || !lem->end->nbr_link
			|| (!(fifo.first = ft_lstnew(0, 0))))
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (-1);
	}
	lem->start->weight = 1;
	(fifo.first)->pv = lem->start;
	fifo.last = fifo.first;
	return (iteratif_dijkstra(lem, &fifo));
}
