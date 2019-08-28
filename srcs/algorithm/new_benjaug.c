/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_benjaug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/28 17:47:22 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define CASE_EXPLO 1
#define CASE_END 2
#define CASE_MINUS 4

int			incr_stack(t_lemin *lem, t_lnode *stack, t_link **link, int opt)
{
	t_lnode	*tmp;

	if (opt & CASE_EXPLO)
		get_target(*link)->exploration = lem->exploration;
	else
		get_target(*link)->origin_link->exploration = 0;
	get_target(*link)->origin_link = *link;
	if (opt & CASE_MINUS)
	{
		get_target(*link)->depth = get_origin_node(*link)->depth - 1;
		(*link)->depth = get_origin_node(*link)->depth - 1;
	}
	else
	{
		get_target(*link)->depth = get_origin_node(*link)->depth + 1;
		(*link)->depth = get_origin_node(*link)->depth + 1;
	}
	(*link)->exploration = lem->exploration;
	if ((opt & CASE_END) && get_target(*link) == lem->end)
		return (1);
	if (!(tmp = create_node(stack)))
		return (-1);
	tmp->node = get_target(*link);
	ft_nodadd(&stack, tmp);
	return (0);
}

int			special_incr(t_lemin *lem, t_lnode *stack, t_link **link, int opt)
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
	if (opt)
		get_origin_node(km)->origin_link->exploration = 0;
	get_origin_node(km)->origin_link = km->reverse;
	get_origin_node(km)->depth = get_origin_node(*link)->depth;
	km->reverse->depth = get_origin_node(*link)->depth;
	km->reverse->exploration = lem->exploration;
	if (!(tmp = create_node(stack)))
		return (-1);
	tmp->node = get_origin_node(km);
	ft_nodadd(&stack, tmp);
	return (0);
}

int			first_case(t_lemin *lem, t_lnode *stack, t_link **link)
{
	if (get_origin_node(*link)->solution == 1
			&& get_target(*link)->solution == 1
			&& get_origin_node(*link)->origin_solution == (*link)->reverse
			&& get_origin_node(*link)->depth <= get_target(*link)->depth)
	{
		if (incr_stack(lem, stack, link, CASE_MINUS))
			return (-1);
	}
	else if (get_origin_node(*link)->depth < get_target(*link)->depth - 1)
	{
		if (incr_stack(lem, stack, link, 0))
			return (-1);
	}
	return (0);
}

int			second_case(t_lemin *lem, t_lnode *stack, t_link **link)
{
	t_link *km;
	int		ret;

	if ((get_target(*link)->solution == 1 && (*link)->reverse->solution == 0))
	{
		km = get_target(*link)->origin_solution;
		if (get_target(*link)->origin_solution->solution == 1)
		{
			if (get_origin_node(km) != lem->start
				&& get_origin_node(km)->exploration < lem->exploration) //vicious case
			{
				if (special_incr(lem, stack, link, 0))
					return (-1);
			}
		}
	}
	else if (get_target(*link)->solution == 1
		&& (*link)->reverse->solution == 1
		&& (*link)->target != lem->start)
	{
		if (incr_stack(lem, stack, link, CASE_EXPLO | CASE_MINUS))
			return (-1);
	}
	else if (get_target(*link)->solution == 0)
	{
		if ((ret = incr_stack(lem, stack, link, CASE_EXPLO | CASE_END)))
			return (ret);
	}
	return (0);
}

int			third_case(t_lemin *lem, t_lnode *stack, t_link **link)
{
	t_link *km;
	int		ret;

	if (get_target(*link)->solution == 0)
	{
		if ((ret = incr_stack(lem, stack, link, CASE_EXPLO | CASE_END)))
			return (ret);
	}
	else if ((*link)->solution == 0)
	{
		km = get_target(*link)->origin_solution;
		if (get_target(*link)->origin_solution->solution == 1)
		{
			if (get_origin_node(km) != lem->start
				&& get_origin_node(km)->exploration < lem->exploration) //vicious case
			{
				if (special_incr(lem, stack, link, 0))
					return (-1);
			}
			else if (get_origin_node(km) != lem->start
				&& get_origin_node(km)->exploration == lem->exploration
				&& get_origin_node(*link)->depth < get_origin_node(km)->depth)
			{
				if (special_incr(lem, stack, link, 1))
					return (-1);
			}
		}
	}
	return (0);
}

int			explore_link_base(t_lemin *lem, t_lnode *stack, t_link **link)
{
	int		ret;

	/*if (get_target(*link)->exploration == lem->exploration
		&& get_target(*link) != lem->start)
	{
		if (first_case(lem, stack, link))
			return (-1);
	}
	else */if (get_target(*link)->exploration < lem->exploration)
	{
		if (get_origin_node(*link)->solution == 1)
		{
			if ((ret = second_case(lem, stack, link)))
				return (ret);
		}
		else if (get_target(*link)->solution == 0 || (*link)->solution == 0)
		{
			if ((ret = third_case(lem, stack, link)))
				return (ret);
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
		if (0)
		{
			t_lnode *tmp = stack;
			while (tmp)
			{
				ft_printf("%s:%zu->-", tmp->node->name, tmp->node->depth);
				tmp = tmp->next;
			}
		}
		while ((ret = explore_link_base(lem, stack, &link)) <= 0)
			if (ret == -1)
				return (-1);
		if (link && !(stack->node == lem->start && link->solution == 1))
			break ;
		ft_stackdelfirst(&stack);
	}
	ret = stack ? 0 : -1;
	ft_stackdel(stack);
	if (ret == 0)
		pathsolver(lem);
	return (ret);
}
