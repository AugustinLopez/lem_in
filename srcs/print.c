/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/22 14:53:26 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int		print_fifo_loop(t_fifo *ant, t_list *tmp, t_list **prev, t_list **cur)
{
	if (!(tmp))
	{
		if (*prev)
		{
			(*prev)->next = (*cur)->next;
			free(*cur);
			*cur = (*prev)->next;
		}
		else
		{
			ant->first = ant->first->next;
			free(*cur);
			*cur = ant->first;
		}
		return (0);
	}
	(*cur)->pv = tmp;
	*prev = *cur;
	*cur = (*cur)->next;
	return (1);
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
		ret = print_fifo_loop(ant, tmp, &prev, &cur) ? 1 : ret;
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
	size_t	res;

	print_path(lem);
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
		(void)print_fifo(&ant, ac);
		++res;
	}
	while (print_fifo(&ant, ac))
		++res;
	return (res + 1);
}
