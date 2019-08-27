/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_benjaug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/27 15:08:39 by aulopez          ###   ########.fr       */
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
		/*if (get_origin_node(*link)->solution == 1)
		{
			if ((*link)->reverse->solution == 1 && (*link)->target != lem->start)
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
		}*/
		if (get_target(*link)->solution == 0)
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
			km = get_target(*link)->link;
			while (km)
			{
				if (get_target(km)->solution == 1)
				{
					if (get_target(km) != lem->start
						&& get_target(km) != lem->end
						&& get_target(km)->exploration < lem->exploration)
					{
						get_target(*link)->exploration = lem->exploration;
						get_target(*link)->origin_link = *link;
						get_target(*link)->depth = get_origin_node(*link)->depth + 1;
						(*link)->depth = get_origin_node(*link)->depth + 1;
						(*link)->exploration = lem->exploration;
						get_target(km)->exploration = lem->exploration;
						get_target(km)->origin_link = km;
						get_target(km)->depth = get_origin_node(km)->depth - 1;
						(km)->depth = get_origin_node(km)->depth - 1;
						(km)->exploration = lem->exploration;
						if (!(tmp = create_node(stack)))
							return (-1);
						tmp->node = get_target(km);
						ft_nodadd(&stack, tmp);
					}

					break ;
				}
				km = km->next;
			}
		}
/*			if (km)
				ft_printf("%s:%s\n", get_target(*link)->name, get_target(km)->name);
			else
				ft_printf("%s\n", get_target(*link)->name);
*/
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
	lem->start->solution = 0;
	lem->end->solution = 0;
	ft_printf("%zu\n", lem->exploration);
	if (!(stack = stack_initialize(lem)))
		return (-1);
	while (stack)
	{
		link = stack->node->link;
		t_lnode *tmp = stack;
		while (tmp)
		{
			ft_printf("%s->-", tmp->node->name);
			tmp = tmp->next;
		}
		ft_printf("\n");
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
