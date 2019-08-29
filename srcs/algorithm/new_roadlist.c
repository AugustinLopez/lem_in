/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_roadlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/29 17:43:16 by aulopez          ###   ########.fr       */
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
	//ft_printf("=>%s", get_target((t_link *)(tmp->pv))->name);
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
		link = get_origin_node(link)->origin_solution;
	}
	if (new->longest < new->first->length)
		new->longest = new->first->length;
	if (1)
	{
		ft_printf("%zu:   ", new->first->length);
		print_path(new->first->km);
	}
	new->nbr_road += 1;
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

t_road	*longest_road(t_roadlist *roadlist)
{
	t_road	*road;
	t_road	*prev;

	prev = 0;
	road = roadlist->first;
	while (road)
	{
		if (road->length == roadlist->longest)
		{
			if (prev)
				prev->next = road->next;
			else
				roadlist->first = roadlist->first->next;
			break ;
		}
		prev = road;
		road = road->next;
	}
	return (road);
}

int		step_count_bis(t_lemin *lem, t_roadlist *roadlist)
{
	t_road	*analysis;
	t_road	*road;
	int		ret;
	size_t	step;
	t_list	*km;
	t_link	*link;

	if (roadlist->nbr_road <= 2)
		return (0);
	analysis = longest_road(roadlist);
	roadlist->longest = 0;
	road = roadlist->first;
	while (road)
	{
		if (road->length > roadlist->longest)
			roadlist->longest = road->length;
		road = road->next;
	}
	step = roadlist->step;
	roadlist->nbr_road -= 1;
	ret = step_count(lem, roadlist);
	if (ret == -1 || roadlist->step >= step)
	{
		roadlist->longest = analysis->length;
		analysis->next = roadlist->first;
		roadlist->first = analysis;
		roadlist->step = step;
		roadlist->nbr_road += 1;
	}
	else
	{
		km = analysis->km;
		while (km)
		{
			link = (t_link *)(km->pv);
			if (link)
			{
				link->solution = 0;
				get_target(link)->solution = 0;
				get_target(link)->origin_solution = 0;
			}
			km = km->next;
		}
		km = analysis->km;
		while (km)
		{
			analysis->km = km;
			km = km->next;
			free(analysis->km);
		}
		free(analysis);
	}
	return (ret);
}

int	choose_roadlist(t_lemin *lem, t_roadlist **new)
{
	int	tmp;

	tmp = 0;
	if (lem->roadlist == NULL)
		lem->roadlist = *new;
	else
	{
			
		if ((*new)->step > lem->roadlist->step)
		{
			free_roadlist(new);
			return (1);
		}
		else
		{
			if ((*new)->nbr_road == lem->roadlist->nbr_road
				&& (*new)->step == lem->roadlist->step)
				tmp = 1;
			free_roadlist(&(lem->roadlist));
			lem->roadlist = *new;
			return (tmp);
		}
	}
	return (0);
}

int	create_roadlist(t_lemin *lem)
{
	t_roadlist	*new;
	t_link		*link;
	int			ret;

	if (!(new = (t_roadlist *)malloc(sizeof(*new))))
		return (-1);
	ft_bzero(new, sizeof(*new));
	link = lem->end->link;
	new->exploration = lem->exploration;
	lem->start->solution = 1;
	while (link)
	{
		if (get_target(link)->solution == 1)
		{
			if (feed_roadlist(link, new) == -1)
			{
				lem->start->solution = 0;
				free_roadlist(&new);
				return (-1);
			}
		}
		link = link->next;
	}
	lem->start->solution = 0;
	ret = step_count(lem, new);
	if (ret == -1)
		new->step = -1;
	if (step_count_bis(lem, new) == -1 && ret == -1)
	{
		free_roadlist(&new);
		return (1);
	}
	return (choose_roadlist(lem, &new));
}
