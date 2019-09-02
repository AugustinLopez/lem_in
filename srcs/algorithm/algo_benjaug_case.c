/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_benjaug_case.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/02 15:29:03 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int	start_upstream(t_lemin *lem, t_lnode *stack, t_link **link,
				int option)
{
	t_lnode	*tmp;
	t_link	*km;

	km = get_target(*link)->origin_solution;
	get_target(km)->exploration = lem->exploration;
	get_target(km)->origin_link = *link;
	get_target(km)->depth = get_origin_node(*link)->depth + 1;
	(*link)->depth = get_origin_node(*link)->depth + 1;
	(*link)->exploration = lem->exploration;
	get_origin_node(km)->exploration = lem->exploration;
	if (option)
		get_origin_node(km)->origin_link->exploration = 0;
	get_origin_node(km)->origin_link = km->reverse;
	get_origin_node(km)->depth = get_origin_node(*link)->depth;
	km->reverse->depth = get_origin_node(*link)->depth;
	km->reverse->exploration = lem->exploration;
	if (!(tmp = ft_lnodnew(stack)))
		return (-1);
	tmp->node = get_origin_node(km);
	ft_lnodadd(&stack, tmp);
	return (0);
}

static inline int	case_reexplore_upstream(t_lemin *lem, t_lnode *stack,
						t_link **link)
{
	t_rb_node	*nd;
	t_lnode		*lnode;

	get_target(*link)->origin_link = *link;
	(*link)->exploration = lem->exploration;
	(*link)->depth = get_origin_node(*link)->depth + 1;
	get_target(*link)->depth = get_origin_node(*link)->depth + 1;
	nd = get_target(*link);
	nd->origin_solution->depth = get_origin_node(*link)->depth;
	get_origin_node(nd->origin_solution)->depth = get_origin_node(*link)->depth;
	if (!(lnode = ft_lnodnew(stack)))
		return (-1);
	lnode->node = get_origin_node(nd->origin_solution);
	ft_lnodadd(&stack, lnode);
	return (0);
}

int					case_reexplore(t_lemin *lem, t_lnode *stack, t_link **link)
{
	int	ret;

	ret = 0;
	if (get_origin_node(*link)->solution == 1
			&& get_target(*link)->solution == 1
			&& (*link)->reverse->solution == 1
			&& get_origin_node(*link)->origin_solution == (*link)->reverse
			&& get_origin_node(*link)->depth <= get_target(*link)->depth)
		ret = explore(lem, stack, link, CASE_MINUS);
	else if (get_origin_node(*link)->solution == 0
			&& get_target(*link)->solution == 0
			&& get_origin_node(*link)->depth < get_target(*link)->depth - 1)
		ret = explore(lem, stack, link, 0);
	else if (get_origin_node(*link)->solution == 1
			&& get_target(*link)->solution == 0
			&& get_origin_node(*link)->origin_solution
			&& get_origin_node(*link)->depth < get_target(*link)->depth - 1)
		ret = explore(lem, stack, link, 0);
	else if (get_origin_node(*link)->solution == 0
			&& get_target(*link)->origin_link->reverse->solution != 1
			&& get_origin_node(*link)->depth < get_target(*link)->depth - 1)
		ret = case_reexplore_upstream(lem, stack, link);
	return (ret);
}

int					case_upstream(t_lemin *lem, t_lnode *stack, t_link **link)
{
	t_link	*km;
	int		ret;

	ret = 0;
	if ((get_target(*link)->solution == 1 && (*link)->reverse->solution == 0))
	{
		km = get_target(*link)->origin_solution;
		if (km->solution == 1 && get_origin_node(km) != lem->start
				&& get_origin_node(km)->exploration < lem->exploration)
			ret = start_upstream(lem, stack, link, 0);
	}
	else if (get_target(*link)->solution == 1
			&& (*link)->reverse->solution == 1
			&& (*link)->target != lem->start)
		ret = explore(lem, stack, link, CASE_EXPLO | CASE_MINUS);
	else if (get_target(*link)->solution == 0
			&& get_origin_node(*link)->origin_link->reverse->solution == 1)
		ret = explore(lem, stack, link, CASE_EXPLO | CASE_END);
	return (ret);
}

int					case_basic(t_lemin *lem, t_lnode *stack, t_link **link)
{
	t_link	*km;
	int		ret;

	ret = 0;
	if (get_target(*link)->solution == 0)
		ret = explore(lem, stack, link, CASE_EXPLO | CASE_END);
	else if ((*link)->solution == 0)
	{
		km = get_target(*link)->origin_solution;
		if (km->solution == 1 && get_origin_node(km) != lem->start)
		{
			if (get_origin_node(km)->exploration < lem->exploration)
				ret = start_upstream(lem, stack, link, 0);
			else if (get_origin_node(*link)->depth < get_origin_node(km)->depth
					&& get_origin_node(km)->exploration == lem->exploration)
				ret = start_upstream(lem, stack, link, 1);
		}
	}
	return (ret);
}
