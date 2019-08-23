/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/23 13:06:25 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			benjaug(t_lemin *lem)
{
	t_lnode	*stack;
	t_link	*link;

	if (!(stack = (t_lnode *)malloc(sizeof(*stack))))
		return (-1);
	ft_bzero(stack, sizeof(*stack));
//
	stack->node = lem->start;
	link = stack->node->link;
	while (link)
	{
		ft_printf("%p\n", ((t_rb_node *)(link->target))->name);
		link = link->next;
	}
//
	free(stack);
	return (0);
}
