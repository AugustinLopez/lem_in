/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:45:54 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/22 14:53:40 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"
#include "lem_in.h"

void	print_path(t_lemin *lem)
{
	t_list	*road;
	t_list	*km;

	if (DEBUG)
		return ;
	road = lem->sol->path;
	while (road)
	{
		km = road->pv;
		while (km)
		{
			ft_printf("%s->", get_node(km)->name);
			km = km->next;
		}
		road = road->next;
		ft_printf("\n");
	}
}

void	print_new_explo(int c, t_solver *new, t_solver *old, t_lemin *lem)
{
	if (DEBUG)
		return ;
	if (c)
		ft_printf("New Explo\n");
	else
		ft_printf("%zu %zu %zu %zu\n", new->max, old->max, step_count(lem->nbr_ant, new), step_count(lem->nbr_ant, old));
}

void	print_stack(t_fifo *fifo)
{
	t_list	*tmp;

	if (DEBUG)
		return ;
	tmp = fifo->first;
	while (tmp)
	{
		ft_printf("%s|%zu->", get_node(tmp)->name, get_node(tmp)->flag);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	print_explo(char c, t_list *rev, t_list *path, t_rb_node *node)
{
	if (DEBUG)
		return ;
	if (c == '\n')
		ft_printf("\n");
	else
		ft_printf("(%zu|%zu|%zu)==>", rev->zu, path->zu, node->visited);
}

