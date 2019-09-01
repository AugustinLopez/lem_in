/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_dijkstra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/01 22:35:17 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				print_stack(t_lemin *lem, t_lnode *stack)
{
	t_lnode *tmp = stack;

	while (tmp)
	{
		if (tmp->node != lem->start)
			ft_printf("%s%s%s-%zu > ", FT_BOLD, tmp->node->name, FT_EOC,
					tmp->node->depth);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

int					conclude_exploration(t_lemin *lem, t_lnode *stack)
{
	int	ret;

	ret = stack ? 0 : -1;
	ft_stackdel(stack);
	if (ret == 0)
	{
		pathsolver(lem);
		ret = create_roadlist(lem);
	}
	return (ret);
}

static inline int	explore_link_dijkstra(t_lemin *lem, t_lnode *stack,
						t_link **link)
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
		if (!(tmp = ft_lnodnew(stack)))
			return (-1);
		tmp->node = get_target(*link);
		ft_lnodadd(&stack, tmp);
	}
	*link = (*link)->next;
	if (*link == NULL)
		return (1);
	return (0);
}

int					dijkstra(t_lemin *lem)
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
		while ((ret = explore_link_dijkstra(lem, stack, &link)) <= 0)
			if (ret == -1)
				return (-1);
		if (link)
			break ;
		if (lem->flags & F_EXPLO)
			print_stack(lem, stack);
		ft_stackdelfirst(&stack);
	}
	return (conclude_exploration(lem, stack));
}
