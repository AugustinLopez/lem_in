/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_bad_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/12 16:17:41 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

static inline int	check_for_elimination(t_lemin *lem, t_list *road,
						t_list *km)
{
	t_list	*prev;
	char	first;
	t_list	*tmp;
	t_list	*ret;

	first = (road == lem->path);
	prev = lem->path;
	if (!first)
	{
		while (prev->next != road)
			prev = prev->next;
		tmp = prev->next->next;
	}
	else
		tmp = prev->next;
	while (tmp)
	{
		if ((ret = lstfind(tmp->pv, km)))
		{
			lstremove(&(lem->path), tmp, road);
			return (first);
		}
		tmp = tmp->next;
	}
	return (0);
}

int					remove_bad_paths(t_lemin *lem)
{
	t_list		*road;
	t_list		*km;
	int			ret;

	road = lem->path;
	if (ft_lstsize(road) == 1)
		return (0);
	while (road)
	{
		km = road->pv;
		while (km)
		{
			if (get_node(km)->nbr_link > 2)
				if ((ret = check_for_elimination(lem, road, km)))
					break ;
			km = km->next;
		}
		road = ret ? lem->path : road->next;
	}
	return (0);
}
