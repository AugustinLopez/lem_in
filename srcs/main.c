/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/27 13:08:01 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

void	basic_sort(t_road **array, t_road *first, size_t size)
{
	t_road	*tmp;
	size_t	i;

	i = 0;
	tmp = first;
	while (tmp)
	{
		array[i++] = tmp;
		tmp = tmp->next;
	}
	i = 0;
	while (i < size - 1)
	{
		if (array[i]->length > array[i + 1]->length)
		{
			tmp = array[i];
			array[i] = array[i + 1];
			array[i + 1] = tmp;
			if (i)
				--i;
		}
		else
			++i;
	}
}

int		sort_roadlist(t_roadlist *roadlist)
{
	t_road	**array;
	size_t	i;

	if (!(array = ft_memalloc(sizeof(*array) * roadlist->exploration)))
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (-1);
	}
	basic_sort(array, roadlist->first, roadlist->exploration);
	roadlist->first = array[0];
	i = 0;
	while (i < roadlist->exploration - 1)
	{
		array[i]->next = array[i + 1];
		++i;
	}
	array[i]->next = NULL;
	free(array);
	return (0);
}

int	calculate_ant_to_launch(t_lemin *lem, t_roadlist *roadlist)
{
	size_t	ant;
	t_road	*road;
	size_t	step;

	ant = lem->nbr_ant;
	road = roadlist->first;
	step = 0;
	while (road)
	{
		road->ant_to_launch = roadlist->longest - road->length + 1;
		ant -= roadlist->longest - road->length + 1;
		road = road->next;
	}
	road = roadlist->first;
	step = roadlist->longest + ant / roadlist->exploration;
	while (road)
	{
		road->ant_to_launch += step - roadlist->longest;
		if (ant % lem->exploration)
		{
			road->ant_to_launch += 1;
			ant -= 1;
		}
		road = road->next;
	}
	return (0);
}

int		printer(t_lemin *lem)
{
	t_road	*road;
	t_list	*iter;
	size_t	ant;
	size_t	step;
	size_t	x1;
	size_t	x2;

	ant = 1;
	step = 0;
	while (step <= lem->roadlist->step)
	{
		road = lem->roadlist->first;
		while (road)
		{
			iter = road->km;
			x1 = iter->zu;
			while (iter->next)
			{
				x2 = iter->next->zu;
				iter->next->zu = x1;
				x1 = x2;
				iter = iter->next;
			}
			if (road->ant_to_launch)
			{
				road->km->zu = ant;
				ant += 1;
				road->ant_to_launch -= 1;
			}
			else
				road->km->zu = 0;
			iter = road->km;
			while (iter)
			{
				if (iter->zu != 0)
					ft_printf("L%zu-%s ", iter->zu, get_target((t_link *)(iter->pv))->name);
				iter = iter->next;
			}
			road = road->next;
		}
		ft_printf("\n");
		step += 1;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_lemin		lem;
//	t_solver	path;
	int			ret;

	(void)av;
	ft_bzero(&lem, sizeof(lem));
	ret = parser(&lem);
	if (!ret)
	{
		if ((ret = dijkstra(&lem)) == -1 || create_roadlist(&lem) != 0)
			ft_dprintf(STDERR_FILENO, "ERROR\n");
		else
		{
			while (ret == 0)
			{
				ret = dijkstra(&lem);
				if (ret == -1)
					break ;
				ret = create_roadlist(&lem);
			}
			ret = 0;
			sort_roadlist(lem.roadlist);
			calculate_ant_to_launch(&lem, lem.roadlist);
			if (ac > 1)
			{
				ft_printf("Step's number: %zu\n", lem.roadlist->step);
				ft_printf("Ant's number : %zu\n", lem.nbr_ant);
				ft_printf("Room's number: %zu\n", lem.nbr_room);
				ft_printf("Tube's number: %zu\n", lem.nbr_tube);
			}
			else
				printer(&lem);
			free_roadlist(&(lem.roadlist));
		}
	}
	lem_free_tree(&(lem.tree));
	return (ret);
//	ft_bzero(&path, sizeof(path));
	//lem.sol = &path;
/*	if (!(ret = parser(&lem)))
		if ((ret = edmundkarp(&lem) >= 0))
			if (!(ret = sort_road(&lem)))
				res = printer(&lem, ac);*/
	//ft_lnkdel(&((lem.sol)->path), *lnkoflnk);
}
