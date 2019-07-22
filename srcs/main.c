/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/22 14:17:56 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"


void	basic_sort(t_list **array, size_t size)
{
	t_list	*tmp;
	size_t	i;

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
	t_list	*tmp;
	size_t	i;

	if (!(array = ft_memalloc(sizeof(*array) * lem->sol->num)))
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (-1);
	}
	tmp = lem->sol->path;
	i = 0;
	while (tmp)
	{
		array[i++] = tmp;
		tmp = tmp->next;
	}
	basic_sort(array, lem->sol->num);
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

void	print_length(t_lemin *lem)
{
	t_list	*tmp;
	t_list	*tmp2;

	ft_printf("%zu %zu %zu\n", step_count(lem->nbr_ant, lem->sol), lem->sol->num, lem->sol->max);
	tmp = lem->sol->path;
	while (tmp)
	{
		ft_printf("%zu ", tmp->zu);
		tmp2 = (t_list *)(tmp->pv);
		while (tmp2)
		{
			ft_printf("%s->", get_node(tmp2)->name);
			tmp2 = tmp2->next;
		}

	ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("\n");
}
/*
void	feed_ant(t_list *start, size_t ant)
{
	t_list	*km;
	size_t	prev;
	size_t	tmp;

	if (ant == 0)
		start->zu = 0;
	km = start->pv;
	if (ant && km->zu == 0)
	{
		km->zu = ant;
		return ;
	}
	prev = km->zu;
	km = km->next;
	while (km)
	{
		tmp = km->zu;
		km->zu = prev;
		prev = tmp;
		km = km->next;
	}
	km = start->pv;
	km->zu = ant;
}

void	print_ant(t_list *start)
{
	t_list	*km;
	t_list	*road;

	road = start;
	while (road)
	{
		km = road->pv;
		while (km)
		{
			if (km->zu)
				ft_printf("L%zu-%s ", km->zu, get_node(km)->name);
			km = km->next;
		}
		road = road->next;
	}
	ft_printf("\n");
}
*/

int		feed_ant(t_list *road, t_fifo *ant, size_t step)
{
	t_list	*tmp;

	if (!(road->zu && road->zu <= step && ant->n <= ant->max))
	{
		road->zu = 0;
		return (0);
	}
	++road->zu;
	if (!(tmp = ft_lstnew(0, 0)))
		return (-1);
	if (!(ant->first))
	{
		ant->first = tmp;
		ant->last = tmp;
	}
	else
	{
		ant->last->next = tmp;
		ant->last = ant->last->next;
	}
	tmp->zu = (ant->n)++;
	tmp->pv = road->pv;
	return (0);
}

int		print_fifo(t_fifo *ant, int ac)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*tmp;
	int		ret;
	int		first;

	ret = 0;
	prev = 0;
	first = 1;
	cur = ant->first;
	while (cur)
	{
		if (ac < 2 && first && first--)
			ft_printf("L%zu-%s", cur->zu, get_node(cur->pv)->name);
		else if (ac < 2)
			ft_printf(" L%zu-%s", cur->zu, get_node(cur->pv)->name);
		tmp = ((t_list *)(cur->pv))->next;
		if (!(tmp))
		{
			if (prev)
			{
				prev->next = cur->next;
				free(cur);
				cur = prev->next;
			}
			else
			{
				ant->first = ant->first->next;
				free(cur);
				cur = ant->first;
			}
		}
		else
		{
			ret = 1;
			cur->pv = tmp;
			prev = cur;
			cur = cur->next;
		}
	}
	if (ac < 2)
		ft_printf("\n");
	return (ret);
}

size_t	printer(t_lemin *lem, int ac)
{
	t_fifo	ant;
	size_t	step;
	t_list	*tmp;
	int		ret;
	size_t	res;

	ant.n = 1;
	ant.max = lem->nbr_ant;
	ant.first = 0;
	res = 0;
	step = step_count(lem->nbr_ant, lem->sol);
	ft_printf("\n");
	while (ant.n <= ant.max)
	{
		tmp = lem->sol->path;
		while (tmp)
		{
			feed_ant(tmp, &ant, step);
			tmp = tmp->next;
		}
		ret = print_fifo(&ant, ac);
		++res;
	}
	while (print_fifo(&ant, ac))
		++res;
	return (res + 1);
}

int		main(int ac, char **av)
{
	t_lemin		lem;
	t_solver	path;
	int			ret;
	size_t		res;

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
