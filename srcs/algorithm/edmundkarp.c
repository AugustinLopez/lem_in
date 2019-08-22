/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmundkarp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/22 15:21:25 by bcarlier         ###   ########.fr       */
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

void				remove_doublon(t_fifo *fifo)
{
	t_link	*origin;
	t_link	*tmp;
	t_link	*prev;

	origin = fifo->first;
	while (origin)
	{
		tmp = origin->next;
		prev = origin;
		while (tmp)
		{
			if (!ft_strcmp(get_node(tmp)->name, get_node(origin)->name))
			{
				prev->next = tmp->next;
				free(tmp);
				tmp = prev->next;
				if (tmp == NULL)
					fifo->last = prev;
			}
			else
			{
				tmp = tmp->next;
				prev = prev->next;
			}
		}
		origin = origin->next;
	}
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

static inline int	new_exploration(t_lemin *lem, t_fifo *stack, t_solver *new)
{
	int			ret;
	t_solver	*old;

	old = lem->sol;
	stack->first->pv = lem->start;
	stack->last = stack->first;
	ret = 0;
	if (old->max == 0)
		ret = explore_node(lem, stack, old);
	else
	{
		if ((ret = explore_node(lem, stack, new)))
			return (free_fifo(stack, ret));
		ret = 1;
		print_new_explo(1, new, old, lem);
		if (step_count(lem->nbr_ant, new) > step_count(lem->nbr_ant, old))
			ft_lnkdel(&(new->path), *lnkoflnk);
		else
		{
			ft_lnkdel(&(old->path), *lnkoflnk);
			ft_memcpy(old, new, sizeof(*new));
			ret = 0;
		}
		ft_bzero(new, sizeof(*new));
	}
	return (free_fifo(stack, ret));
}

int					edmundkarp(t_lemin *lem)
{
	t_fifo		stack;
	t_solver	new;
	int			ret;

	if ((ret = init_edmundkarp(lem, &stack, &new)))
		return (-1);
	while (++(stack.n) < stack.max)
	{
		print_new_explo(0, 0, 0, 0);
		if (ret == 1)
			break ;
		else if (ret == -1 || !(stack.first = ft_lnknew(0, 0)))
		{
			ret = -1;
			break ;
		}
		ret = new_exploration(lem, &stack, &new);
	}
	if (ret == -1)
		ft_dprintf(STDERR_FILENO, "ERROR\n");
	return (free_fifo(&stack, ret));
}
