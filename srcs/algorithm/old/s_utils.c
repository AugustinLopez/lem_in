/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/22 15:55:35 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

int		free_fifo(t_fifo *fifo, int ret)
{
	t_link	*tmp;

	while (fifo->first)
	{
		tmp = fifo->first->next;
		free(fifo->first);
		fifo->first = tmp;
	}
	return (ret);
}

t_link	*get_reverse_path(t_rb_node *node, t_link *path)
{
	t_link		*tmp;
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

size_t	step_count(size_t ant, t_solver *sol)
{
	t_link	*tmp;
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
	sol->step += a / sol->num;
	if (a % sol->num)
		++(sol->step);
/*	while (a)
	{
		a -= (sol->num > a) ? a : sol->num;
		++(sol->step);
	}*/
	return (sol->step);
}
