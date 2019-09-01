/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_roadlist_longest.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/01 22:46:24 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

static inline t_road	*longest_road(t_roadlist *roadlist)
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

static inline int		longest_road_is_good(t_lemin *lem, t_roadlist *roadlist,
							size_t *step)
{
	t_road	*road;
	int		ret;

	ret = 0;
	roadlist->longest = 0;
	road = roadlist->first;
	while (road)
	{
		if (road->length > roadlist->longest)
			roadlist->longest = road->length;
		road = road->next;
	}
	*step = roadlist->step;
	roadlist->nbr_road -= 1;
	ret = step_count(lem, roadlist);
	if (ret == -1)
		return (-1);
	if (roadlist->step >= *step)
		return (1);
	return (0);
}

static inline void		free_longest_road(t_road *road)
{
	t_list	*km;
	t_link	*link;

	km = road->km;
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
	km = road->km;
	while (km)
	{
		road->km = km;
		km = km->next;
		free(road->km);
	}
	free(road);
}

int						try_without_longest_path(t_lemin *lem,
							t_roadlist *roadlist)
{
	t_road	*lroad;
	int		ret;
	size_t	step;

	if (roadlist->nbr_road <= 2)
		return (0);
	lroad = longest_road(roadlist);
	if ((ret = longest_road_is_good(lem, roadlist, &step)))
	{
		roadlist->longest = lroad->length;
		lroad->next = roadlist->first;
		roadlist->first = lroad;
		roadlist->step = step;
		roadlist->nbr_road += 1;
	}
	else
		free_longest_road(lroad);
	return (ret);
}
