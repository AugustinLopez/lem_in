/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmundkarp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/20 11:53:12 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

int					loop_pathlist(t_lemin *lem, t_fifo *fifo, t_list **road,
						t_list **km)
{
	t_list		*tmp;
	size_t		i;
	t_rb_node	*node;

	i = 0;
	node = lem->end;
	while (1)
	{
		++i;
		*road = node == lem->end ? *road : node->link;
		while (get_reverse_path(node, *road)->zu != fifo->max)
			*road = (*road)->next;
		if ((node = get_node(*road)) == lem->start)
			break ;
		if (!(tmp = ft_lstnew(0, 0)))
			return (-1);
		tmp->pv = node;
		ft_lstadd(km, tmp);
	}
	(*road)->zu = i;
	return (0);
}

int					feed_pathlist(t_solver *sol, t_lemin *lem, t_fifo *fifo)
{
	t_list		*path;
	t_list		*mem;
	t_list		*tmp;
	size_t		j;
	size_t		i;

	j = 0;
	mem = lem->end->link;
	while (++j < fifo->n + 1)
	{
		if (!(tmp = init_pathlist(lem, sol, fifo, &mem)))
			return (-1);
		path = mem;
		mem = mem->next;
		if (loop_pathlist(lem, fifo, &path, &tmp) == -1)
			return (-1);
		i = path->zu;
		sol->path->zu = i;
		sol->path->pv = tmp;
		if (sol->max < sol->path->zu)
			sol->max = sol->path->zu;
	}
	sol->num = fifo->n;
	return (0);
}

int					bfs_algorithm(t_lemin *lem, t_fifo *fifo, t_solver *sol)
{
	int			ret;
	t_list		*tmp;

	while (fifo->first)
	{
		if ((ret = pathfinder(lem, fifo)))
			break ;
		tmp = fifo->first;
		fifo->first = fifo->first->next;
		free(tmp);
	}
	if (ret == 1)
	{
		pathsolver(lem, fifo);
		ret = feed_pathlist(sol, lem, fifo);
		return (ret);
	}
	if (fifo->n == 1)
		return (-1);
	return (1);
}

int					exploration(t_lemin *lem, t_fifo *fifo, t_solver *old,
						t_solver *new)
{
	int	ret;

	fifo->first->pv = lem->start;
	fifo->last = fifo->first;
	ret = 0;
	if (old->max == 0)
		ret = bfs_algorithm(lem, fifo, old);
	else
	{
		if ((ret = bfs_algorithm(lem, fifo, new)))
			return (free_fifo(fifo, ret));
		ret = 1;
		if (step_count(lem->nbr_ant, new) > step_count(lem->nbr_ant, old))
			ft_lstdel(&(new->path), *lstoflst);
		else
		{
			ft_lstdel(&(old->path), *lstoflst);
			ft_memcpy(old, new, sizeof(*new));
			ret = 0;
		}
		ft_bzero(new, sizeof(*new));
	}
	return (free_fifo(fifo, ret));
}

int					edmundkarp(t_lemin *lem)
{
	t_fifo		fifo;
	int			ret;
	t_solver	new;

	if ((ret = init_edmundkarp(lem, &fifo, lem->sol, &new)))
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (free_fifo(&fifo, ret));
	}
	while (++(fifo.n) < fifo.max)
	{
		if (ret == 1)
			break ;
		else if (ret == -1 || !(fifo.first = ft_lstnew(0, 0)))
		{
			ft_dprintf(STDERR_FILENO, "ERROR\n");
			return (free_fifo(&fifo, ret));
		}
		ret = exploration(lem, &fifo, lem->sol, &new);
	}
	return (free_fifo(&fifo, ret));
}
