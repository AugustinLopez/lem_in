/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/12 15:57:30 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>
/*
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
}*/
/*
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
}*/
