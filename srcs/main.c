/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/16 15:14:48 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

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

int					main(void)
{
	t_lemin	lem;
	int		ret;

	ft_bzero(&lem, sizeof(lem));
	ret = parser(&lem);
	if (!ret)
		ret = edmundkarp(&lem);
	// This part is the algorithm
	/*if (!ret)
		ret = dijkstra(&lem);
	if (!ret)
		remove_bad_paths(&lem);
	// end of the algorithm part
	if (!ret)
		solve(&lem);*/
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	ft_lstdel(&(lem.path), *lstoflst);
	return (ret);
}
