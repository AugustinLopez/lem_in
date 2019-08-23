/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/23 14:44:34 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			benjaug(t_lemin *lem)
{
	t_lnode	*stack;
	t_lnode	*tmp;
	t_link	*link;

	if (!(stack = (t_lnode *)malloc(sizeof(*stack))))
		return (-1);
	ft_bzero(stack, sizeof(*stack));
//
	stack->node = lem->start;
	stack->node->exploration = 1;
	ft_printf("\n");
	while (stack)
	{
		link = stack->node->link;
		while (link)
		{
			if (get_target(link)->exploration == 0)
			{
				ft_printf("%s->%s\n", get_origin(link)->name, get_target(link)->name);
				get_target(link)->exploration = 1;
				get_target(link)->origin = link;
				link->exploration = 1;
				if (get_target(link) == lem->end)
					break ;
				if (!(tmp = (t_lnode *)malloc(sizeof(*tmp))))
					return (-1); //protect better
				ft_bzero(tmp, sizeof(*tmp));
				tmp->node = get_target(link);
				ft_nodadd(&stack, tmp);
			}
			link = link->next;
		}
		if (link)
			break ; //free rest of stack
		tmp = stack;
		stack = stack->next;
		free(tmp);
		if (stack)
			stack->prev = 0;
	}
	if (stack)
	{
		tmp = stack;
		while (tmp)
		{
			stack = tmp;
			tmp = tmp->next;
			free(stack);
		}
	}
	stack->node = lem->end;
	while (stack->node->origin)
	{
		ft_printf("%s<=", stack->node->name);
		stack->node->origin->solution = 1;
		get_origin(stack->node->origin)->solution = 1;
		stack->node = get_origin(stack->node->origin);
	}
	lem->end->solution = 0;
	lem->start->solution = 0;
	ft_printf("%s\n", lem->start->name);
	return (0);
}
