/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/09 12:43:43 by aulopez          ###   ########.fr       */
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
		ft_printf("\n");
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

t_list				*lstfind(t_list *begin, t_list *elem)
{
	t_list	*tmp;

	tmp = begin->next;
	while (tmp->next)
	{
		if (get_node(tmp) == get_node(elem))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void				eliminate(t_list **begin, t_list *one, t_list *two)
{
	t_list	*elim;
	t_list	*tmp;

	elim = two->zu < one->zu ? one : two;
	if (elim == *begin)
		*begin = (*begin)->next;
	else
	{
		tmp = *begin;
		while (tmp->next != elim)
			tmp = tmp->next;
		tmp->next = tmp->next->next;
	}
	elim->next = 0;
	ft_lstdelone(&elim, *lstoflst);
}

int					check_for_elimination(t_list *road, t_list *km, t_lemin *lem)
{
	t_list	*prev;
	char	first;
	t_list	*tmp;
	t_list	*ret;

	first = (road == lem->path);
	prev = lem->path;
	if (!first)
		while (prev->next != road)
			prev = prev->next;
	if (first)
		tmp = prev->next;
	else
		tmp = prev->next->next;
	while (tmp)
	{
		if ((ret = lstfind(tmp->pv, km)))
		{
			if (!first)
				eliminate(&(lem->path), tmp, prev->next);
			else
				eliminate(&(lem->path), tmp, lem->path);
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
	ret = 0;
	while (road)
	{
		km = road->pv;
		while (km)
		{
			if (get_node(km)->nbr_link > 2)
				if ((ret = check_for_elimination(road, km, lem)))
					break ;
			km = km->next;
		}
		if (ret)
		{
			ret = 0;
			road = lem->path;
		}
		else
			road = road->next;
	}
	return (0);
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
		remove_bad_paths(&lem);
		print_path(&lem);
		solve_one_path(&lem);
	}
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	ft_lstdel(&(lem.path), *lstoflst);
	return (ret);
}
