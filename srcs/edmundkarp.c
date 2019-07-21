/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmundkarp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/19 22:08:29 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

static inline int	free_fifo(t_fifo *fifo, int ret)
{
	t_list	*tmp;

	while (fifo->first)
	{
		tmp = fifo->first->next;
		free(fifo->first);
		fifo->first = tmp;
	}
	return (ret);
}

t_list		*get_reverse_path(t_rb_node *node, t_list *path)
{
	t_list		*tmp;
	t_rb_node	*rev;

	rev = get_node(path);
	tmp = rev->link;
	while (tmp)
	{
		if (get_node(tmp) == node)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void				lstoflst(void *pv, size_t zu)
{
	t_list	*cur;
	t_list	*tmp;

	cur = (t_list *)pv;
	tmp = cur;
	while (cur)
	{
		tmp = tmp->next;
		free(cur);
		cur = tmp;
	}
	pv = 0;
	(void)zu;
}

t_list	*init_pathlist(t_lemin *lem, t_solver *sol, t_fifo *fifo, t_list **memory)
{
	t_list		*tmp;

	if (!(tmp = ft_lstnew(0, 0)))
		return (0);
	if (!(sol->path))
		sol->path = tmp;
	else
		ft_lstadd(&(sol->path), tmp);
	if (!(tmp->pv = ft_lstnew(0, 0)))
		return (0);
	while (get_reverse_path(lem->end, *memory)->zu != fifo->max)
		*memory = (*memory)->next;
	tmp = tmp->pv;
	tmp->pv = lem->end;
	return (tmp);
}

int			loop_pathlist(t_lemin *lem, t_fifo *fifo, t_list **road, t_list **km)
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

void		print_list(t_solver *sol)
{
	t_list	*road;
	t_list	*km;
	size_t	i;

	road = sol->path;
/*	while (tmp)
	{*/
		km = road->pv;
		ft_printf("%zu: ", road->zu);
		while (km)
		{
			ft_printf("%s-", get_node(km)->name);
			km = km->next;
		}
		ft_printf("\n");
	/*	tmp = tmp->next;
	}*/
}

int			feed_pathlist(t_solver *sol, t_lemin *lem, t_fifo *fifo)
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
		//print_list(sol);
	}
	sol->num = fifo->n;
	return (0);
}


size_t		step_count(size_t ant, t_solver *sol)
{
	t_list	*tmp;
	size_t	a;

	a = ant;
	tmp = sol->path;
	sol->step = 0;
	while (tmp)
	{
		a -= (sol->max - tmp->zu + 1);
		if (a > ant)
		{
			sol->step = -1;
			return (-1);
		}
		tmp = tmp->next;
	}
	sol->step = sol->max;
	while (a)
	{
		a -= (sol->num > a) ? a : sol->num;
		++(sol->step);
	}
	return (sol->step);
}

int			bfs_algorithm(t_lemin *lem, t_fifo *fifo, t_solver *sol)
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

int			exploration(t_lemin *lem, t_fifo *fifo, t_solver *old, t_solver *new)
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
		t_list	*tmp;

		ft_printf("%zu %zu\n", step_count(lem->nbr_ant, old), old->num);
		tmp = old->path;
		while (tmp)
		{
			ft_printf("%zu ", tmp->zu);
			tmp = tmp->next;
		}
		ft_printf("\n");
		ft_bzero(new, sizeof(*new));
	}
	return (free_fifo(fifo, ret));
}

int			initialize_edmundkarp(t_lemin *lem, t_fifo *fifo, t_solver *old, t_solver *new)
{
	size_t	a;
	size_t	b;

	if (!lem->start->nbr_link || !lem->end->nbr_link)
		return (-1);
	ft_bzero(fifo, sizeof(*fifo));
	ft_bzero(old, sizeof(*old));
	ft_bzero(new, sizeof(*new));
	a = lem->start->nbr_link;
	b = lem->end->nbr_link;
	fifo->max = a < b ? b : a;
	fifo->max = fifo->max < lem->nbr_ant ? fifo->max + 1 : lem->nbr_ant + 1;
	fifo->n = 0;
	return (0);
}

int			edmundkarp(t_lemin *lem)
{
	t_fifo		fifo;
	int			ret;
	t_solver	old;
	t_solver	new;

	if ((ret = initialize_edmundkarp(lem, &fifo, &old, &new)))
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
		ret = exploration(lem, &fifo, &old, &new);
	}
	ft_lstdel(&(old.path), *lstoflst);
	return (free_fifo(&fifo, ret));
}
