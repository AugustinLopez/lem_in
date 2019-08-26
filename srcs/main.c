/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/26 16:15:55 by aulopez          ###   ########.fr       */
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
					continue ;
				ret = create_roadlist(&lem);
			}
			if (ac > 1)
			{
				ft_printf("Step's number: %zu\n", lem.roadlist->step);
				ft_printf("Ant's number : %zu\n", lem.nbr_ant);
				ft_printf("Room's number: %zu\n", lem.nbr_room);
				ft_printf("Tube's number: %zu\n", lem.nbr_tube);
			}
			sort_roadlist(lem.roadlist);
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
