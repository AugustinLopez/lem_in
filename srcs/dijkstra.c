/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/08 17:59:27 by aulopez          ###   ########.fr       */
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

static inline int	end_loop(t_rb_node *node, t_lemin *lem)
{
	t_list	*tmp;

	tmp = NULL;
	while (node)
	{
		if (!tmp)
		{
			if (!(lem->dijkstra = ft_lstnew(0, 0)))
				return (-1);
			tmp = lem->dijkstra;
		}
		else
		{
			if (!(tmp->next = ft_lstnew(0, 0)))
				return (-1);
			tmp = tmp->next;
		}
		tmp->pv = node;
		node = node->prev;
	}
	return (1);
}

static inline int	link_loop(t_list *lst, t_lemin *lem, t_fifo *fifo)
{
	t_rb_node	*node;

	while (lst)
	{
		node = get_node(lst);
		if (node->prev || node == lem->start)
		{
			lst = lst->next;
			continue ;
		}
		node->prev = get_node(fifo->first);
		if (!(fifo->tmp = ft_lstnew(0, 0)))
			return (free_fifo(fifo, -1));
		fifo->tmp->pv = node;
		fifo->last->next = fifo->tmp;
		fifo->last = fifo->tmp;
		if (node == lem->end)
			return (end_loop(node, lem));
		lst = lst->next;
	}
	return (0);
}

static inline int	iteratif_dijkstra(t_lemin *lem, t_fifo *fifo)
{
	int		ret;

	while (fifo->first)
	{
		if ((ret = link_loop(get_node(fifo->first)->link, lem, fifo)) == 1)
			return (free_fifo(fifo, 0));
		else if (ret == -1)
			break ;
		fifo->tmp = fifo->first->next;
		free(fifo->first);
		fifo->first = fifo->tmp;
	}
	ft_dprintf(STDERR_FILENO, "ERROR\n");
	return (free_fifo(fifo, -1));
}

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
	(fifo.first)->pv = lem->start;
	fifo.last = fifo.first;
	return (iteratif_dijkstra(lem, &fifo));
}
