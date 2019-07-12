/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/12 16:44:45 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

size_t				lstlongest_bis(t_list *begin, size_t *nbr, size_t max)
{
	size_t	n;
	t_list	*tmp;

	tmp = begin;
	n = 0;
	*nbr = 0;
	while (tmp)
	{
		if (tmp->zu && n < tmp->zu - 1 && tmp->zu - 1 < max)
		{
			n = tmp->zu - 1;
			*nbr = 1;
		}
		else if (tmp->zu && n == tmp->zu - 1 && tmp->zu - 1 < max)
			++(*nbr);
		tmp = tmp->next;
	}
	return (n);
}

size_t				lst2ndlongest(t_list *begin, size_t nbr)
{
	size_t	n;
	t_list	*tmp;

	tmp = begin;
	n = 0;
	while (tmp)
	{
		if (tmp->zu && n < tmp->zu - 1 && tmp->zu - 1 < nbr)
			n = tmp->zu - 1;
		tmp = tmp->next;
	}
	return (n);
}

int				solve_paths(t_lemin *lem, t_list *road, size_t ant_id)
{
	t_list	*tmp;
	t_list	*begin;
	int		a;

	a = 0;
	begin  = road->pv;
	tmp = begin;
	while (get_node(tmp) != lem->start)
		tmp = tmp->next;
	if (ant_id <= lem->nbr_ant)
		tmp->zu = ant_id;
	else
		tmp->zu = 0;
	while (begin->next && begin->next->zu == 0)
		begin = begin->next;
	tmp = begin;
	while (tmp->next)
	{
		tmp->zu = tmp->next->zu;
		if (tmp->zu)
		{
			a = 1;
			ft_printf("L%zu-%s ", tmp->zu, get_node(tmp)->name);
		}
		tmp = tmp->next;
	}
	return (a);
}

void	different_paths(t_lemin *lem, size_t *ant_id, size_t *length, size_t *nbr_path)
{
	size_t	second;
	size_t	nbr_max;
	t_list	*road;

	*length = lstlongest_bis(lem->path, &nbr_max, -1);
	second = lst2ndlongest(lem->path, *length);
	ft_printf("\n");
	while (*nbr_path > nbr_max)
	{
		if (*length <= (lem->nbr_ant - *ant_id) / (*nbr_path - nbr_max) + second)
		{
			road = lem->path;
			while (road)
			{
				road->zu - 1 <= *length
					? solve_paths(lem, road, ++(*ant_id))
					: solve_paths(lem, road, -1);
				road = road->next;
			}
			ft_printf("\n");
		}
		else
		{
			*nbr_path -= nbr_max;
			*length = lstlongest_bis(lem->path, &nbr_max, *length);
			second = lst2ndlongest(lem->path, *length);
		}
	}
}

void	similar_paths(t_lemin *lem, size_t *ant_id, size_t length)
{
	t_list	*road;

	while (lem->nbr_ant > *ant_id)
	{
			road = lem->path;
			while (road)
			{
				if (road->zu - 1 <= length)
					solve_paths(lem, road, ++(*ant_id));
				else
					solve_paths(lem, road, -1);
				road = road->next;
			}
			ft_printf("\n");
	}
}

void	finish_path(t_lemin *lem)
{
	char	a;
	t_list	*road;

	a = 1;
	while (a)
	{
		a = 0;
		road = lem->path;
		while (road)
		{
			if (solve_paths(lem, road, -1))
				a = 1;
			road = road->next;
		}
		if (a)
			ft_printf("\n");
	}
}

int					solve(t_lemin *lem)
{
	size_t	nbr_path;
	size_t	max_length;
	size_t	index;

	index = 0;
	nbr_path = ft_lstsize(lem->path);
	different_paths(lem, &index, &max_length, &nbr_path);
	similar_paths(lem, &index, max_length);
	finish_path(lem);
	return (0);
}
