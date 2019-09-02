/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_benjaug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/03 00:44:44 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						explore(t_lemin *lem, t_lnode *stack, t_link **link,
							int option)
{
	t_lnode	*tmp;

	if (option & CASE_EXPLO)
		get_target(*link)->exploration = lem->exploration;
	else
		get_target(*link)->origin_link->exploration = 0;
	get_target(*link)->origin_link = *link;
	if (option & CASE_MINUS)
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
	if ((option & CASE_END) && get_target(*link) == lem->end)
		return (1);
	if (!(tmp = ft_lnodnew(stack)))
		return (-1);
	tmp->node = get_target(*link);
	ft_lnodadd(&stack, tmp);
	return (0);
}

static inline int		explore_link_benjaug(t_lemin *lem, t_lnode *stack,
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

static inline size_t	stacksize(t_lnode *stack)
{
	t_lnode	*tmp;
	size_t	zu;

	zu = 0;
	tmp = stack;
	while (tmp)
	{
		++zu;
		tmp = tmp->next;
	}
	return (zu);
}

static inline void		correct_path(t_rb_node *node)
{
	t_rb_node	*tmp;
	t_link		*link;

	tmp = node;
	link = 0;
	while (tmp)
	{
		if (!(get_origin_node(tmp->origin_link)->solution == 1) || link)
			break ;
		tmp = get_origin_node(tmp->origin_link);
		link = tmp->link;
		while (link)
		{
			if (link->reverse->exploration == tmp->exploration
					&& tmp->origin_link == link->reverse)
				break ;
			link = link->next;
		}
	}
	if (tmp)
	{
		tmp->origin_link->exploration = 0;
		tmp->exploration = 0;
	}
}

/*
void				correct_path(t_rb_node *node)
{
	t_rb_node	*tmp;
	t_link		*link;

	tmp = node;
	while (tmp)
	{
		if (get_origin_node(tmp->origin_link)->solution == 1)
		{
			tmp = get_origin_node(tmp->origin_link);
			link = tmp->link;
			while (link)
			{
				if (link->reverse->exploration == tmp->exploration && tmp->origin_link == link->reverse)
				{
					tmp->origin_link->exploration = 0;
					tmp->exploration = 0;
					return ;
				}
				link = link->next;
			}
		}
		else
		{
			tmp->origin_link->exploration = 0;
			tmp->exploration = 0;
			break ;
		}
	}
}*/

int						benjaug(t_lemin *lem)
{
	t_lnode	*stack;
	t_link	*link;
	int		ret;
	size_t	correction;

	lem->exploration += 1;
	if (!(stack = ft_stackinit(lem)))
		return (-1);
	while (stack)
	{
		correction = (stack->node->solution == 1
				&& !(stack->node == lem->start)) ? stacksize(stack) : 0;
		link = stack->node->link;
		while ((ret = explore_link_benjaug(lem, stack, &link)) <= 0)
			if (ret == -1)
				return (-1);
		if (link && !(stack->node == lem->start && link->solution == 1))
			break ;
		if (lem->flags & F_EXPLO)
			print_stack(lem, stack);
		if (correction && stacksize(stack) - 1 < correction)
			correct_path(stack->node);
		ft_stackdelfirst(&stack);
	}
	return (conclude_exploration(lem, stack));
}
