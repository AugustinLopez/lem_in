/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edmundkarp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/22 15:21:11 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

t_link				*init_pathlink(t_lemin *lem, t_solver *sol, t_fifo *fifo,
						t_link **memory)
{
	t_link		*tmp;

	if (!(tmp = ft_lnknew(0, 0)))
		return (0);
	if (!(sol->path))
		sol->path = tmp;
	else
		ft_lnkadd(&(sol->path), tmp);
	if (!(tmp->pv = ft_lnknew(0, 0)))
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

	ft_bzero(fifo, sizeof(*fifo));
	ft_bzero(lem->sol, sizeof(*(lem->sol)));
	ft_bzero(cur, sizeof(*cur));
	if (!lem->start || !lem->end
		|| !lem->start->nbr_link || !lem->end->nbr_link)
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (free_fifo(fifo, -1));
	}
	a = lem->start->nbr_link;
	b = lem->end->nbr_link;
	fifo->max = a < b ? b : a;
	fifo->max = fifo->max < lem->nbr_ant ? fifo->max + 1 : lem->nbr_ant + 1;
	lem->start->flag = 0;
	lem->end->flag = 1;
	fifo->n = 0;
	return (0);
}
