/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/08 21:58:52 by aulopez          ###   ########.fr       */
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

	tmp = lem->dijkstra;
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
		ft_printf("\n");
	}
}

void				solve_one_path(t_lemin *lem)
{
	t_list	*tmp;

	tmp  = lem->dijkstra;
	while (tmp->next)
		tmp = tmp->next;
	tmp->zu = 1;
	ft_printf("\n");
	while (lem->dijkstra->zu <= lem->nbr_ant)
	{
		tmp = lem->dijkstra;
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
	}
}

void				lstoflst(void *pv, size_t zu)
{
	t_list	*cur;
	t_list	*tmp;

	cur = (t_list *)pv;
	tmp = cur;
	while (cur)
	{
		tmp = tmp->next;
		free(cur);
		cur = tmp;
	}
	pv = 0;
	(void)zu;
}

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
		solve_one_path(&lem);
	}
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	ft_lstdel(&(lem.path), *lstoflst);
	return (ret);
}
