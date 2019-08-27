/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_benjaug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/27 18:29:46 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			explore_link_base(t_lemin *lem, t_lnode *stack, t_link **link)
{
	t_lnode	*tmp;
	t_link	*km;

	km = 0;
	if (get_target(*link)->exploration < lem->exploration)
	{
		if (get_origin_node(*link)->solution == 1)
		{
			
			ft_printf("%s-", get_origin_node(*link)->name);
			if ((get_target(*link)->solution == 1 && (*link)->solution == 0))
			{
				km = get_target(*link)->origin_solution;
				if (get_origin_node(*link)->origin_link->reverse->solution == 0)
				{
					if (get_origin_node(km) != lem->start
						&& get_origin_node(km)->exploration < lem->exploration)
					{
						get_target(km)->exploration = lem->exploration;
						get_target(km)->origin_link = *link;
						get_target(km)->depth = get_origin_node(*link)->depth + 1;
						(*link)->depth = get_origin_node(*link)->depth + 1;
						(*link)->exploration = lem->exploration;
							get_origin_node(km)->exploration = lem->exploration;
						get_origin_node(km)->origin_link = km->reverse;
						get_origin_node(km)->depth = get_origin_node(*link)->depth;
						km->reverse->depth = get_origin_node(*link)->depth;
						km->reverse->exploration = lem->exploration;
						if (!(tmp = create_node(stack)))
							return (-1);
						tmp->node = get_origin_node(km);
						ft_nodadd(&stack, tmp);
					}
				}
			}
			else if ((*link)->reverse->solution == 1 && (*link)->target != lem->start)
			{
				get_target(*link)->exploration = lem->exploration;
				get_target(*link)->origin_link = *link;
				get_target(*link)->depth = get_origin_node(*link)->depth - 1;
				(*link)->depth = get_origin_node(*link)->depth - 1;
				(*link)->exploration = lem->exploration;
				if (!(tmp = create_node(stack)))
					return (-1);
				tmp->node = get_target(*link);
				ft_nodadd(&stack, tmp);
			}
			else if ((*link)->reverse->solution == 0)
			{
				get_target(*link)->exploration = lem->exploration;
				get_target(*link)->origin_link = *link;
				get_target(*link)->depth = get_origin_node(*link)->depth + 1;
				(*link)->depth = get_origin_node(*link)->depth + 1;
				(*link)->exploration = lem->exploration;
				if (!(tmp = create_node(stack)))
					return (-1);
				tmp->node = get_target(*link);
				ft_nodadd(&stack, tmp);
			}
		}
		else if (get_target(*link)->solution == 0)
		{
			get_target(*link)->exploration = lem->exploration;
			get_target(*link)->origin_link = *link;
			get_target(*link)->depth = get_origin_node(*link)->depth + 1;
			(*link)->depth = get_origin_node(*link)->depth + 1;
			(*link)->exploration = lem->exploration;
			if (get_target(*link) == lem->end)
				return (1);
			if (!(tmp = create_node(stack)))
				return (-1);
			tmp->node = get_target(*link);
			ft_nodadd(&stack, tmp);
		}
		else if ((*link)->solution == 0)
		{
			km = get_target(*link)->origin_solution;
			if (get_origin_node(*link)->origin_link->reverse->solution == 0)
			{
				if (get_origin_node(km) != lem->start
					&& get_origin_node(km)->exploration < lem->exploration)
				{
					get_target(km)->exploration = lem->exploration;
					get_target(km)->origin_link = *link;
					get_target(km)->depth = get_origin_node(*link)->depth + 1;
					(*link)->depth = get_origin_node(*link)->depth + 1;
					(*link)->exploration = lem->exploration;
					get_origin_node(km)->exploration = lem->exploration;
					get_origin_node(km)->origin_link = km->reverse;
					get_origin_node(km)->depth = get_origin_node(*link)->depth;
					km->reverse->depth = get_origin_node(*link)->depth;
					km->reverse->exploration = lem->exploration;
					if (!(tmp = create_node(stack)))
						return (-1);
					tmp->node = get_origin_node(km);
					ft_nodadd(&stack, tmp);
				}
			}
		}
	}
	*link = (*link)->next;
	if (*link == NULL)
		return (1);
	return (0);
}

int			benjaug(t_lemin *lem)
{
	t_lnode	*stack;
	t_link	*link;
	int		ret;

	lem->exploration += 1;
	if (!(stack = stack_initialize(lem)))
		return (-1);
	while (stack)
	{
		link = stack->node->link;
		t_lnode *tmp = stack;
		if (0)
		{
			while (tmp)
			{
				ft_printf("%s:%zu->-", tmp->node->name, tmp->node->depth);
				tmp = tmp->next;
			}
			ft_printf("\n");
		}
		while ((ret = explore_link_base(lem, stack, &link)) <= 0)
			if (ret == -1)
				return (-1);
		if (link)
			break ;
		ft_stackdelfirst(&stack);
	}
	ret = stack ? 0 : -1;
	ft_stackdel(stack);
	if (ret == 0)
		pathsolver(lem);
	//lem->start->exploration = 0;
	return (ret);
}
