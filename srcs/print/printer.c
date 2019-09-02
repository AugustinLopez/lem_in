/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/02 10:58:20 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

static inline int	calculate_ant_to_launch(t_lemin *lem, t_roadlist *roadlist)
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
	step = roadlist->longest + ant / roadlist->nbr_road;
	ant %= roadlist->nbr_road;
	road = roadlist->first;
	while (road)
	{
		road->ant_to_launch += step - roadlist->longest;
		if (ant && ant--)
			road->ant_to_launch += 1;
		road = road->next;
	}
	return (0);
}

static inline void	print_info(t_lemin *lem, t_road *road)
{
	t_list	*iter;

	iter = road->km;
	while (iter)
	{
		if (iter->zu != 0)
		{
			if ((lem->flags & F_COLOR)
					&& get_target((t_link *)(iter->pv)) == lem->end)
				ft_printf("%sL%zu-%s%s ", FT_LYELLOW, iter->zu,
						get_target((t_link *)(iter->pv))->name, FT_EOC);
			else if ((lem->flags & F_COLOR)
					&& get_origin_node((t_link *)(iter->pv)) == lem->start)
				ft_printf("%sL%zu-%s%s ", FT_GREEN, iter->zu,
						get_target((t_link *)(iter->pv))->name, FT_EOC);
			else
				ft_printf("L%zu-%s ", iter->zu,
						get_target((t_link *)(iter->pv))->name);
		}
		iter = iter->next;
	}
}

static inline void	print_loop(t_lemin *lem, size_t *ant, t_road *road)
{
	t_list	*iter;
	size_t	prev_value;
	size_t	next_value;

	iter = road->km;
	prev_value = iter->zu;
	while (iter->next)
	{
		next_value = iter->next->zu;
		iter->next->zu = prev_value;
		prev_value = next_value;
		iter = iter->next;
	}
	if (road->ant_to_launch)
	{
		road->km->zu = *ant;
		*ant += 1;
		road->ant_to_launch -= 1;
	}
	else
		road->km->zu = 0;
	print_info(lem, road);
}

static inline int	print_ant_path(t_lemin *lem)
{
	t_road	*road;
	size_t	step;
	size_t	ant;

	step = 0;
	ant = 1;
	while (step++ < lem->roadlist->step)
	{
		if (lem->flags & F_NUMBER)
			ft_printf("%s%d:%s ", FT_BOLD, step, FT_EOC);
		road = lem->roadlist->first;
		while (road)
		{
			print_loop(lem, &ant, road);
			road = road->next;
		}
		ft_printf("\n");
	}
	return (0);
}

void				printer(t_lemin *lem)
{
	sort_roadlist(lem->roadlist);
	calculate_ant_to_launch(lem, lem->roadlist);
	if (!(lem->flags & F_NOANT))
		print_ant_path(lem);
	if (lem->flags & F_INFO)
	{
		if (!(lem->flags & F_NOFILE && lem->flags & F_NOANT))
			ft_printf("\n");
		ft_printf("Step's number: %zu\n", lem->roadlist->step);
		ft_printf("Ant's number : %zu\n", lem->nbr_ant);
		ft_printf("Room's number: %zu\n", lem->nbr_room);
		ft_printf("Tube's number: %zu\n", lem->nbr_tube);
	}
	free_roadlist(&(lem->roadlist));
}
