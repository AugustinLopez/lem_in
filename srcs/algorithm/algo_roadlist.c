/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_roadlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:17:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/01 22:56:13 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

static inline int	choose_roadlist(t_lemin *lem, t_roadlist **new)
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

static inline int	feed_roadlist(t_lemin *lem, t_link *first_link,
						t_roadlist *new)
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
	if (lem->flags & F_PATH)
	{
		ft_printf("%zu:   ", new->first->length);
		print_path(new->first->km);
	}
	new->nbr_road += 1;
	return (0);
}

static inline int	find_all_road(t_lemin *lem, t_roadlist *new)
{
	t_link	*link;

	link = lem->end->link;
	lem->start->solution = 1;
	while (link)
	{
		if (get_target(link)->solution == 1)
		{
			if (feed_roadlist(lem, link, new) == -1)
			{
				lem->start->solution = 0;
				free_roadlist(&new);
				return (-1);
			}
		}
		link = link->next;
	}
	lem->start->solution = 0;
	return (0);
}

int					create_roadlist(t_lemin *lem)
{
	t_roadlist	*new;
	int			ret;

	if (!(new = (t_roadlist *)malloc(sizeof(*new))))
		return (-1);
	ft_bzero(new, sizeof(*new));
	new->exploration = lem->exploration;
	if (find_all_road(lem, new) == -1)
		return (-1);
	if (lem->flags & F_PATH)
		ft_printf("\n");
	if ((ret = step_count(lem, new)) == -1)
		new->step = -1;
	if (try_without_longest_path(lem, new) == -1 && ret == -1)
	{
		free_roadlist(&new);
		return (1);
	}
	return (choose_roadlist(lem, &new));
}
