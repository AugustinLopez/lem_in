/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/10 10:22:01 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>

int					handle_single_path(t_list *road, size_t n, size_t tot)
{
	t_list	*km;
	int		check;

	check = 0;
	if (n >= tot && road->pv)
	{
		road->zu = 0;
		check = 1;
	}
	km = road->pv;
	while (km->next && !(km->next->zu))
		km = km->next;
	while (km->next)
	{
		km->zu = km->next->zu;
		km = km->next;
	}
	if (check)
		km->zu = 0;
	if (road->pv)
		km->zu = n;
	return (check);
}

void				print_thing(t_list *road)
{
	t_list	*km;

	km = road->pv;
	while (km->next && !(km->zu))
		km = km->next;
	while (km->next)
	{
		if (!(km->zu))
			break ;
		ft_printf("L%zu-%s ", km->zu, get_node(km)->name);
		km = km->next;
	}
}

int					only_zero(t_list *begin)
{
	t_list	*tmp;

	tmp = begin->next;
	while (tmp)
	{
		if (tmp->zu)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void				finish_path(t_lemin *lem, t_list *min, size_t iter)
{
	size_t	nbr;
	t_list	*road;
	t_list	dummy;
	int		a;

	dummy.zu = 0;
	nbr = ft_lstsize(lem->path);
	while (nbr)
	{
		road = lem->path;
		a = 0;
		while (road)
		{
			if (only_zero(road->pv))
			{
				lstremove(&(lem->path), &dummy, road);
				--nbr;
				break ;
			}
			a = 1;
			if (road == min && iter < lem->nbr_ant)
			{
				if (handle_single_path(road, ++iter, lem->nbr_ant))
					min = 0;
			}
			else
				handle_single_path(road, 0, 0);
			print_thing(road);
			road = road->next;
		}
		if (a)
			ft_printf("\n");
	}
}

void				handle_all_path(t_lemin *lem)
{
	size_t	nbr;
	size_t	max;
	t_list	*min;
	size_t	iter;
	int		ret;
	t_list	*tmp;

	nbr = ft_lstsize(lem->path);
	max = lstlongest(lem->path);
	min = lstshortest(lem->path);
	iter = 0;
	ret = 0;
	while (max)
	{
		tmp = lem->path;
		while (tmp)
		{
			if (tmp->zu)
				ret = handle_single_path(tmp, ++iter, nbr * lem->nbr_ant / tmp->zu);
			else
				ret = handle_single_path(tmp, 0, 0);
			if (ret)
			{
				--nbr;
				max = lstlongest(lem->path);
			}
			print_thing(tmp);
			tmp = tmp->next;
		}
		ft_printf("\n");
	}
//	finish_path(lem, min, iter);
}
/*
void				solve_paths(t_lemin *lem)
{
	t_list	*tmp;
	t_list	*begin;
	size_t	nbr;
	size_t	max;
	size_t	iter;

	nbr = ft_lstsize(lem->path);
	max = lstlongest(lem->path);
	ft_printf("%d %d\n", nbr, max);
	begin  = lem->path->pv;
	tmp = begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->zu = 1;
	iter = 0;
	while (begin->zu <= lem->nbr_ant)
	{
		tmp = begin;
		while (!(tmp->next->zu))
			tmp = tmp->next;
		while (tmp)
		{
			if (tmp->next)
			{
				tmp->zu = tmp->next->zu;
				if (tmp->next->zu > lem->nbr_ant)
					break ;
			}
			else if (tmp->zu <= lem->nbr_ant)
				tmp->zu += 1;
			tmp = tmp->next;
			if (lem->path->zu && iter >= lem->nbr_ant)
			{
				lem->path->zu = 0;
				tmp = begin;
				while (tmp->next)
					tmp = tmp->next;
				tmp->zu = lem->nbr_ant + 1;
				tmp = begin;
				while (!(tmp->next->zu))
					tmp = tmp->next;
			}
		}
		iter += 1;
		print_me(lem);
		if (tmp != begin)
			ft_printf("\n");
	}
}*/
