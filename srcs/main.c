/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/09 17:36:11 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>

/*__attribute__((destructor)) void loop(void)
{
	for(;;);
}*/

void				debug(t_lemin *lem)
{
	ft_printf("\nStart is: %s %lld %lld\n",
		lem->start->name, lem->start->x, lem->start->y);
	ft_printf("With %zu links. First is %s\n",
		lem->start->nbr_link, get_node(lem->start->link)->name);
	ft_printf("End is: %s %lld %lld\n",
		lem->end->name, lem->end->x, lem->end->y);
}

void				print_path(t_lemin *lem)
{
	t_list		*road;
	t_list		*km;
	t_rb_node	*node;

	road = lem->path;
	ft_printf("\nNbr path:%d", ft_lstsize(lem->path));
	ft_printf("\n");
	while (road)
	{
		km = road->pv;
		while (km)
		{
			node = get_node(km);
			if (km->next)
				ft_printf("%s<-", node->name);
			else
				ft_printf("%s", node->name);
			km = km->next;
		}
		ft_printf("\n");
		road = road->next;
	}
	ft_printf("\n");
}

void				print_me(t_lemin *lem)
{
	t_list	*tmp;

	tmp = lem->path->pv;
	while (!(tmp->zu))
		tmp = tmp->next;
	if (tmp->next && tmp->zu <= lem->nbr_ant)
	{
		while (tmp->next)
		{
			if (tmp->zu > lem->nbr_ant)
				break ;
			ft_printf("L%zu-%s ", tmp->zu, get_node(tmp)->name);
			tmp = tmp->next;
		}
	}
}

void				solve_one_path(t_lemin *lem)
{
	t_list	*tmp;
	t_list	*begin;

	begin  = lem->path->pv;
	tmp = begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->zu = 1;
	ft_printf("\n");
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
		}
		print_me(lem);
		if (tmp != begin)
			ft_printf("\n");
	}
}








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




int					main(void)
{
	t_lemin	lem;
	int		ret;

	ft_bzero(&lem, sizeof(lem));
	ret = reader(&lem);
	if (!ret)
		ret = dijkstra(&lem);
	//Need to eliminate bad path here
	//Need to do one pass of dijkstra like, and one with priority given to path with less link
	if (!ret)
	{
		print_path(&lem);
		remove_bad_paths(&lem);
		print_path(&lem);
		handle_all_path(&lem);
	}
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	ft_lstdel(&(lem.path), *lstoflst);
	return (ret);
}
