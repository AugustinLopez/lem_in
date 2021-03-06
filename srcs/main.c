/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/20 11:39:23 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

void	basic_sort(t_list **array, t_list *origin, size_t size)
{
	t_list	*tmp;
	size_t	i;

	i = 0;
	tmp = origin;
	while (tmp)
	{
		array[i++] = tmp;
		tmp = tmp->next;
	}
	i = 0;
	while (i < size - 1)
	{
		if (array[i]->zu > array[i + 1]->zu)
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

int		sort_road(t_lemin *lem)
{
	t_list	**array;
	size_t	i;

	if (!(array = ft_memalloc(sizeof(*array) * lem->sol->num)))
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (-1);
	}
	basic_sort(array, lem->sol->path, lem->sol->num);
	lem->sol->path = array[0];
	i = 0;
	while (i < lem->sol->num - 1)
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
	t_solver	path;
	int			ret;
	size_t		res;

	(void)av;
	ft_bzero(&lem, sizeof(lem));
	ft_bzero(&path, sizeof(path));
	lem.sol = &path;
	res = 0;
	if (!(ret = parser(&lem)))
		if ((ret = edmundkarp(&lem) >= 0))
			if (!(ret = sort_road(&lem)))
				res = printer(&lem, ac);
	ft_lstdel(&((lem.sol)->path), *lstoflst);
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	if (ac > 1)
	{
		ft_printf("Step's number: %zu\n", res);
		ft_printf("Ant's number : %zu\n", lem.nbr_ant);
		ft_printf("Room's number: %zu\n", lem.nbr_room);
		ft_printf("Tube's number: %zu\n", lem.nbr_tube);
	}
	return (ret);
}
