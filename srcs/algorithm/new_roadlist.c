/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_roadlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/26 11:58:14 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

int					loop_pathlink(t_lemin *lem, t_fifo *stack, t_link **road,
						t_link **km)
{
	t_link		*tmp;
	size_t		i;
	t_rb_node	*node;

	i = 0;
	node = lem->end;
	while (1)
	{
		++i;
		*road = node == lem->end ? *road : node->link;
		while (get_reverse_path(node, *road)->zu != stack->max)
			*road = (*road)->next;
		if ((node = get_node(*road)) == lem->start)
			break ;
		if (!(tmp = ft_lnknew(0, 0)))
			return (-1);
		tmp->pv = node;
		ft_lnkadd(km, tmp);
	}
	(*road)->zu = i;
	return (0);
}

int					feed_pathlink(t_solver *sol, t_lemin *lem, t_fifo *stack)
{
	t_link		*path;
	t_link		*mem;
	t_link		*tmp;
	size_t		j;
	size_t		i;

	j = 0;
	mem = lem->end->link;
	while (++j < stack->n + 1)
	{
		if (!(tmp = init_pathlink(lem, sol, stack, &mem)))
			return (-1);
		path = mem;
		mem = mem->next;
		if (loop_pathlink(lem, stack, &path, &tmp) == -1)
			return (-1);
		i = path->zu;
		sol->path->zu = i;
		sol->path->pv = tmp;
		if (sol->max < sol->path->zu)
			sol->max = sol->path->zu;
	}
	sol->num = stack->n;
	return (0);
}

int					explore_node(t_lemin *lem, t_fifo *stack, t_solver *sol)
{
	int			ret;
	t_link		*tmp;

	while (stack->first)
	{
		remove_doublon(stack);
		if ((ret = pathfinder(lem, stack)))
			break ;
		tmp = stack->first;
		stack->first = stack->first->next;
		free(tmp);
	}
	if (ret == 1)
	{
		pathsolver(lem, stack);
		ret = feed_pathlink(sol, lem, stack);
		return (ret);
	}
	if (stack->n == 1)
		return (-1);
	return (1); //ret 0 ?
}
