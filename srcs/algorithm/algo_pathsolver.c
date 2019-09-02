/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_pathsolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:52:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/02 11:03:59 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	print_solving_path(t_lemin *lem, t_rb_node *node)
{
	if (lem->flags & F_SOLVER)
	{
		if (node == lem->end)
			ft_printf("%zu: %s%s%s%s%s<==%s", lem->exploration, FT_YELLOW,
				FT_REV, node->name, FT_EOC, FT_LGREEN, FT_EOC);
		else if (node == lem->start && !(lem->flags & F_PATH))
			ft_printf("%s%s%s%s: New edge(s) = %zu\n\n", FT_LYELLOW, FT_REV,
				node->name, FT_EOC, lem->end->origin_link->depth);
		else if (node == lem->start)
			ft_printf("%s%s%s%s: New edge(s) = %zu\n", FT_LYELLOW, FT_REV,
				node->name, FT_EOC, lem->end->origin_link->depth);
		else if (node->solution == 1)
		{
			if (node->origin_link == node->origin_solution)
				ft_printf("%s%s%s<==%s", FT_LRED, FT_REV, node->name, FT_EOC);
			else if (node->origin_link->reverse->solution == 1)
				ft_printf("%s%s<==%s", FT_LRED, node->name, FT_EOC);
			else
				ft_printf("%s%s%s<==%s", FT_LRED, node->name, FT_LGREEN,
						FT_EOC);
		}
		else
			ft_printf("%s%s<==%s", FT_LGREEN, node->name, FT_EOC);
	}
}

static inline int	solver_case(t_lemin *lem, t_rb_node *node, int upstream)
{
	if (node->origin_link->reverse->solution == 1)
	{
		node->origin_link->solution = 0;
		if (upstream && get_origin_node(node->origin_solution) != lem->start)
			node->solution = 0;
		node->origin_link->reverse->solution = 0;
		return (1);
	}
	node->origin_link->solution = 1;
	node->solution = 1;
	node->origin_solution = node->origin_link;
	return (0);
}

void				pathsolver(t_lemin *lem)
{
	t_rb_node	*node;
	int			upstream;

	upstream = 0;
	node = lem->end;
	while (node->origin_link)
	{
		if (lem->flags & F_SOLVER)
			print_solving_path(lem, node);
		upstream = solver_case(lem, node, upstream);
		node = get_origin_node(node->origin_link);
	}
	print_solving_path(lem, lem->start);
	lem->end->solution = 0;
	lem->start->solution = 0;
}
