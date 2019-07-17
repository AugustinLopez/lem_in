/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmundkarp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/17 12:27:38 by aulopez          ###   ########.fr       */
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

int			link_loop2(t_lemin *lem, t_fifo *fifo)
{
	t_rb_node	*node;
	t_list		*link;
	t_list		*tmp;
	int			ret;

	//ft_printf("%s->", get_node(fifo->cur)->name);
	if (check_for_end(lem, fifo))
		return (1);
	link = get_node(fifo->first)->link;
	while (link)
	{
		ret = 0;
		node = get_node(link);
	//	ft_printf("|%s|", node->name);
		if (link->zu > fifo->n) //link already "solved"
		{
			link = link->next;
			continue ;
		}
		if (node->visited == fifo->n) //cannot visit same node twice UNLESS node has been "solved"
		{
			link = link->next;
			continue ;
		}
		if (get_node(link)->visited == fifo->max)
		{
			if (get_reverse_path(get_node(fifo->first), link)->zu != fifo->max) //Must reverse a solved path
				ret = 1;
			if (ret == 1) //we check if we already reversed a solved path on the target node.
			{
				tmp = get_node(link)->link;
				while (tmp)
				{
					if (tmp->zu == fifo->n)
						break;
					tmp = tmp->next;
				}
				if (tmp)
				{
					link = link->next;
					continue ;
				}
			}
		}
		if (fifo->first->zu == 1) //traffic jam case
		{
			//ft_printf("\\%d\\",get_reverse_path(get_node(fifo->cur), link)->zu );
			if (get_reverse_path(get_node(fifo->first), link)->zu != fifo->max)
			{
				link = link->next;
				continue ;
			}
		}
		else if (get_reverse_path(get_node(fifo->first), link)->zu == fifo->n) //can't go back to same path in the same loop.
		{
			link = link->next;
			continue ;
		}
		if (node->visited < fifo->n) //node not occupied by solution or previous pass by current loop
			node->visited = fifo->n;
		if (link->zu < fifo->n)
		{
			link->zu = fifo->n;
			if (!(tmp = ft_lstnew(0, 0)))
				return (-1);
			tmp->pv = node;
			tmp->zu = ret;
			fifo->last->next = tmp;
			fifo->last = fifo->last->next;
		}
		link = link->next;
	}
	//ft_printf("\n");
	return (0);
}

void		explore_n(t_lemin *lem, t_fifo *fifo)
{
	t_list		*tmp;
	t_list		*mem;
	t_list		*rev;
	t_list		*case1;
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
		//ft_printf("%d: %s<-", j, node->name);
		ft_printf("Num:%d: ", j);
		while (node != lem->start)
		{
			if (ft_strcmp(node->name, "Vit6") == 0)
			{
				case1 = node->link;
				ft_printf("\n");
				while (case1)
				{
					ft_printf("%s-%s |%d %d|\n", node->name, get_node(case1)->name, case1->zu, get_reverse_path(node, case1)->zu);
					case1 = case1->next;
				}
			}
			tmp = node == end ? tmp : node->link;
			rev = get_reverse_path(node, tmp);
			while (rev->zu != x)
			{
				tmp = tmp->next;
				rev = get_reverse_path(node, tmp);
			}
			if (tmp->zu == fifo->max)
			{
				case1 = tmp;
				while (tmp)
				{
					if (tmp->zu == fifo->max)
						if (get_reverse_path(node, tmp)->zu == fifo->n)
							case1 = tmp;
					tmp = tmp->next;
				}
				tmp = case1;
			}
			//ft_printf("|%s:%s| %d:%d ", get_node(tmp)->name, get_node(rev)->name, tmp->zu, rev->zu);
			rev->zu = fifo->max;
			if (rev->zu == tmp->zu)
			{
				rev->zu = 0;
				tmp->zu = 0;
			}
			node = get_node(tmp);
			node->visited = fifo->max;
			i++;
		//	if (!(node == lem->start))
		//		ft_printf("%s<-", node->name);
		}
		//ft_printf("%s : %d\n", lem->start->name, i);
		ft_printf("%d\n", i);
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

	while (fifo->first)
	{
		if ((ret = link_loop2(lem, fifo)))
			break ;
		tmp = fifo->first;
		fifo->first = fifo->first->next;
		free(tmp);
	}
	if (ret == 1)
	{
		explore_n(lem, fifo);
		return (0);
	}
	ft_dprintf(STDERR_FILENO, "No more found. Apparently\n");
	//ft_dprintf(STDERR_FILENO, "ERROR\n");
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
