/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/27 17:21:42 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lnode*	create_node(t_lnode *stack)
{
	t_lnode	*tmp;
	t_lnode	*iter;

	tmp = (t_lnode *)malloc(sizeof(*tmp));
	if (!tmp)
	{
		if (stack != NULL)
		{
			iter = stack;
			while (iter)
			{
				tmp = iter;
				iter = iter->next;
				free(tmp);
			}
			tmp = NULL;
		}
	}
	else
		ft_bzero(tmp, sizeof(*tmp));
	return (tmp);
}

void		ft_stackdel(t_lnode *stack)
{
	t_lnode	*iter;

	if (stack)
	{
		iter = stack;
		while (iter)
		{
			stack = iter;
			iter = iter->next;
			free(stack);
		}
	}
}

void		ft_stackdelfirst(t_lnode **stack)
{
	t_lnode *tmp;

	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	if (*stack)
		(*stack)->prev = 0;
}

void		pathsolver(t_lemin *lem)
{
	t_rb_node	*node;

	node = lem->end;
	while (node->origin_link)
	{
		if (DEBUG)
			ft_printf("%s<<<", node->name);
		if (node->origin_link->reverse->solution == 1)
		{
			node->origin_link->solution = 0;
			if (node && node->origin_link->reverse->solution == 1
				&& get_origin_node(node->origin_solution) != lem->start)
				node->solution = 0;
			node->origin_link->reverse->solution = 0;
			node = get_origin_node(node->origin_link);
		}
		else
		{
			node->origin_link->solution = 1;
			node->solution = 1;
			node->origin_solution = node->origin_link;
			node = get_origin_node(node->origin_link);
		}
	}
	if (DEBUG)
		ft_printf("%s\n", lem->start->name);
	lem->end->solution = 0;
	lem->start->solution = 0;
}

t_lnode			*stack_initialize(t_lemin *lem)
{
	t_lnode *tmp;

	if (!(tmp = create_node(0)))
		return (NULL);
	tmp->node = lem->start;
	tmp->node->exploration = lem->exploration;
	if (DEBUG)
		ft_printf("\n");
	return (tmp);
}
