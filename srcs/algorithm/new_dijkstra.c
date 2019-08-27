/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dijkstra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/27 17:29:43 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			explore_link(t_lemin *lem, t_lnode *stack, t_link **link)
{
	t_lnode	*tmp;

	if (get_target(*link)->exploration < lem->exploration
		&& get_target(*link)->solution == 0)
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
	*link = (*link)->next;
	if (*link == NULL)
		return (1);
	return (0);
}

int			dijkstra(t_lemin *lem)
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
		while ((ret = explore_link(lem, stack, &link)) <= 0)
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
	return (ret);
}
