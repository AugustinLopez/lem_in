/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_benjaug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/01 22:48:51 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int	explore_link_benjaug(t_lemin *lem, t_lnode *stack,
						t_link **link)
{
	int		ret;

	lem->end->exploration = 0;
	ret = 0;
	if (get_target(*link)->exploration == lem->exploration
			&& get_target(*link) != lem->start)
		ret = case_reexplore(lem, stack, link);
	else if (get_target(*link)->exploration < lem->exploration)
	{
		if (get_origin_node(*link)->solution == 1)
			ret = case_upstream(lem, stack, link);
		else if (get_target(*link)->solution == 0 || (*link)->solution == 0)
			ret = case_basic(lem, stack, link);
	}
	if (ret)
		return (ret);
	*link = (*link)->next;
	return (*link == NULL ? 1 : 0);
}

int					benjaug(t_lemin *lem)
{
	t_lnode	*stack;
	t_link	*link;
	int		ret;

	lem->exploration += 1;
	if (!(stack = ft_stackinit(lem)))
		return (-1);
	while (stack)
	{
		link = stack->node->link;
		while ((ret = explore_link_benjaug(lem, stack, &link)) <= 0)
			if (ret == -1)
				return (-1);
		if (link && !(stack->node == lem->start && link->solution == 1))
			break ;
		if (lem->flags & F_EXPLO)
			print_stack(lem, stack);
		ft_stackdelfirst(&stack);
	}
	return (conclude_exploration(lem, stack));
}
