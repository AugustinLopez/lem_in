/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/08 16:26:15 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>


int				free_fifo(t_fifo *fifo, int ret)
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

int				dijloop(t_lemin *lem, t_fifo *fifo)
{
	t_rb_node	*node;
	t_list		*lst;

	while (fifo->first)
	{
		lst = get_node(fifo->first)->link;
		while (lst)
		{
			node = get_node(lst);
			if (node->prev || node == lem->start)
			{
				if (!lst)
					continue ;
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
			{
				while (node)
				{
					ft_printf("%s-", node->name);
					node = node->prev;
				}
				ft_printf("\n");
				return (0);
			}
			lst = lst->next;
		}
		fifo->tmp = fifo->first->next;
		free(fifo->first);
		fifo->first = fifo->tmp;
	}
	ft_dprintf(STDERR_FILENO, "ERROR\n");
	return (-1);
}

int				dijkstra(t_lemin *lem)
{
	t_fifo		fifo;

	if (!lem->start->nbr_link || !lem->end->nbr_link)
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (-1);
	}
	ft_bzero(&fifo, sizeof(fifo));
	if (!(fifo.first = ft_lstnew(0, 0)))
		return (-1);
	(fifo.first)->pv = lem->start;
	fifo.last = fifo.first;
	dijloop(lem, &fifo);
	return (free_fifo(&fifo, 0));
}

void				debug(t_lemin *lem)
{
	ft_printf("\nStart is: %s %lld %lld\n",
		lem->start->name, lem->start->x, lem->start->y);
	ft_printf("With %zu links. First is %s\n",
		lem->start->nbr_link, get_node(lem->start->link)->name);
	ft_printf("End is: %s %lld %lld\n",
		lem->end->name, lem->end->x, lem->end->y);
}

int					main(void)
{
	t_lemin	lem;
	int		ret;

	ft_bzero(&lem, sizeof(lem));
	ret = reader(&lem);
	if (!ret)
		dijkstra(&lem);
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	return (ret);
}
