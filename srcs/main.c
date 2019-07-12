/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/12 12:45:38 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>

/*__attribute__((destructor)) void loop(void)
{
	for(;;);
}*/

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

void				solve_paths(t_lemin *lem, t_list *road, size_t ant_id)
{
	t_list	*tmp;
	t_list	*begin;

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
			ft_printf("L%zu-%s ", tmp->zu, get_node(tmp)->name);
		tmp = tmp->next;
	}
}

int					solve(t_lemin *lem)
{
	size_t	nbr_path;
	size_t	max_length;
	size_t	nbr_max;
	size_t	second;
	size_t	ant;
	size_t	i;
	t_list	*road;

	i = 0;
	ant = lem->nbr_ant;
	nbr_path = ft_lstsize(lem->path);
	max_length = lstlongest_bis(lem->path, &nbr_max, -1);
	second = lst2ndlongest(lem->path, max_length);
	ft_printf("N:%d A:%d Max:%d Nbr:%d\n", nbr_path, ant, max_length, nbr_path);
	while (nbr_path > nbr_max)
	{
		if (max_length <= ant / (nbr_path - nbr_max) + second)
		{
			road = lem->path;
			while (road)
			{
				if (road->zu <= max_length)
					solve_paths(lem, road, ++i);
				else
					solve_paths(lem, road, -1);
				road = road->next;
			}
			ft_printf("\n");
			ant -= nbr_path;
			ft_printf("N:%d A:%d Max:%d Nbr:%d\n", nbr_path, ant, max_length, nbr_path);
		}
		else
		{
			nbr_path -= nbr_max;
			max_length = lstlongest_bis(lem->path, &nbr_max, max_length);
			second = lst2ndlongest(lem->path, max_length);
		}
	}
	while (ant)
	{
			road = lem->path;
			while (road)
			{
				solve_paths(lem, road, ++i);
				road = road->next;
			}
			ft_printf("\n");

		ant -= ant > nbr_path ? nbr_path : ant;
		ft_printf("N:%d A:%d Max:%d Nbr:%d\n", nbr_path, ant, max_length, nbr_max);
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
	//Need to do one pass of dijkstra like, and one with priority given to path with less link
	if (!ret)
	{
		print_path(&lem);
		remove_bad_paths(&lem);
		print_path(&lem);
		solve(&lem);
		solve_one_path(&lem);
	}
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	ft_lstdel(&(lem.path), *lstoflst);
	return (ret);
}
