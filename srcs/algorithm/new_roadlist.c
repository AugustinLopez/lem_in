/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_roadlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/26 17:09:38 by aulopez          ###   ########.fr       */
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
	ft_printf("%s", get_origin_node((t_link *)(tmp->pv))->name);
	while (tmp)
	{
		ft_printf("=>%s", get_target((t_link *)(tmp->pv))->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

int	feed_roadlist(t_link *first_link, t_roadlist *new)
{
	t_link	*link;
	t_rb_node	*node;

	if (ft_newroad(&(new->first)) == -1)
		return (-1);
	link = first_link->reverse;
	while (link)
	{
		if (ft_kmadd(new->first, link) == -1)
			return (-1);
		node = get_target(link);
		link = get_origin_node(link)->origin_link;
	}
	if (new->longest < new->first->length)
		new->longest = new->first->length;
	if (DEBUG)
	{
		ft_printf("%zu:", new->first->length);
		print_path(new->first->km);
	}
	return (0);
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
		road->ant_to_launch = roadlist->longest - road->length + 1;
		ant -= road->ant_to_launch;
		if (ant > lem->nbr_ant)
			return (-1);
		road = road->next;
	}
	step = roadlist->longest;
	step += ant / lem->exploration;
	road = roadlist->first;
	while (road)
	{
		road->ant_to_launch += step - roadlist->longest;
		road = road->next;
	}
	if (ant % lem->exploration)
		++step;
	/*road = roadlist->first; //TO DO AFTER SORTING !!!! TODO: STEP_COUNT_AFTER_SORT
	while (road)
	{
		if (ant % lem->exploration)
		{
			road->ant_to_launch += 1;
			ant -= 1;
		}
		else
			break ;
		road = road->next;
	}*/

	roadlist->step = step;
	return (0);
}

int	choose_roadlist(t_lemin *lem, t_roadlist **new)
{
	if (lem->roadlist == NULL)
		lem->roadlist = *new;
	else
	{
		if ((*new)->step > lem->roadlist->step)
		{
			free_roadlist(new);
			return (1);
		}
		else if ((*new)->step == lem->roadlist->step)
			free_roadlist(new);
		else
		{
			free_roadlist(&(lem->roadlist));
			lem->roadlist = *new;
		}
	}
	return (0);
}

int	create_roadlist(t_lemin *lem)
{
	t_roadlist	*new;
	t_link		*link;

	if (!(new = (t_roadlist *)malloc(sizeof(*new))))
		return (-1);
	ft_bzero(new, sizeof(*new));
	link = lem->end->link;
	new->exploration = lem->exploration;
	if (DEBUG)
		ft_printf("\n");
	while (link)
	{
		if (get_target(link)->solution == 1)
		{
			if (feed_roadlist(link, new) == -1)
			{
				free_roadlist(&new);
				return (-1);
			}
		}
		link = link->next;
	}
	if (step_count(lem, new) == -1)
	{
		free_roadlist(&new);
		return (1);
	}
	return (choose_roadlist(lem, &new));
}
