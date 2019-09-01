/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_roadlist_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/01 22:52:32 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

int	ft_newroad(t_road **road)
{
	t_road	*new;

	if (!(new = (t_road *)malloc(sizeof(*new))))
		return (-1);
	ft_bzero(new, sizeof(*new));
	if (*road == NULL)
		*road = new;
	else
	{
		new->next = *road;
		*road = new;
	}
	return (0);
}

int	ft_kmadd(t_road *road, t_link *km)
{
	t_list	*tmp;

	if (!(tmp = (t_list *)malloc(sizeof(*tmp))))
		return (-1);
	ft_bzero(tmp, sizeof(*tmp));
	tmp->pv = (void *)km;
	if (road->km == 0)
		road->km = tmp;
	else
		ft_lstadd(&(road->km), tmp);
	road->length += 1;
	return (0);
}

void	free_roadlist(t_roadlist **roadlist)
{
	t_road	*road;
	t_list	*iter;

	if (!*roadlist)
		return ;
	road = (*roadlist)->first;
	while (road)
	{
		iter = road->km;
		while (iter)
		{
			road->km = iter;
			iter = iter->next;
			free(road->km);
		}
		(*roadlist)->first = road;
		road = road->next;
		free((*roadlist)->first);
	}
	free(*roadlist);
	*roadlist = 0;
}

void	print_path(t_list *km)
{
	t_list	*tmp;

	tmp = km;
	while (tmp)
	{
		ft_printf("=>%s", get_target((t_link *)(tmp->pv))->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

int	step_count(t_lemin *lem, t_roadlist *roadlist)
{
	size_t	ant;
	t_road	*road;
	size_t	step;

	ant = lem->nbr_ant;
	road = roadlist->first;
	step = 0;
	while (road)
	{
		ant -= roadlist->longest - road->length + 1;
		if (ant > lem->nbr_ant)
			return (-1);
		road = road->next;
	}
	step = roadlist->longest;
	step += ant / roadlist->nbr_road;
	if (ant % roadlist->nbr_road)
		++step;
	roadlist->step = step;
	return (0);
}
