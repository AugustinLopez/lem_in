/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edmundkarp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/20 13:46:33 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

t_list				*init_pathlist(t_lemin *lem, t_solver *sol, t_fifo *fifo,
						t_list **memory)
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

/*
** fifo->max is equals to the maximum possible number of path in the solution +1
** Overflow are technically possible, but memory allocation should have failed
** at this point.
*/

int					init_edmundkarp(t_lemin *lem, t_fifo *fifo, t_solver *cur)
{
	size_t	a;
	size_t	b;

	ft_printf("%p %p\n", lem->start, lem->end);
	if (!lem->start->nbr_link)
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (free_fifo(fifo, -1));
	}
	else if (!lem->end->nbr_link)
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (free_fifo(fifo, -1));
	}

	ft_bzero(fifo, sizeof(*fifo));
	ft_bzero(lem->sol, sizeof(*(lem->sol)));
	ft_bzero(cur, sizeof(*cur));
	a = lem->start->nbr_link;
	b = lem->end->nbr_link;
	fifo->max = a < b ? b : a;
	fifo->max = fifo->max < lem->nbr_ant ? fifo->max + 1 : lem->nbr_ant + 1;
	lem->start->flag = 0;
	fifo->n = 0;
	return (0);
}
