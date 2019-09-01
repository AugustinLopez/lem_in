/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnk_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 11:43:19 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/01 23:11:46 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

static inline void	ft_lnkappend(t_rb_node *origin, t_link *new)
{
	if (origin->link == NULL)
		origin->link = new;
	else
	{
		new->next = origin->link;
		origin->link = new;
	}
	origin->nbr_link += 1;
}

int					ft_lnknew(t_rb_node *origin, t_rb_node *target)
{
	t_link	*normal;
	t_link	*reverse;

	if (!(normal = (t_link*)malloc(sizeof(*normal))))
		return (-1);
	if (!(reverse = (t_link*)malloc(sizeof(*reverse))))
	{
		free(normal);
		return (-1);
	}
	ft_bzero(normal, sizeof(*normal));
	ft_bzero(reverse, sizeof(*reverse));
	normal->origin = origin;
	normal->target = target;
	normal->reverse = reverse;
	reverse->origin = target;
	reverse->target = origin;
	reverse->reverse = normal;
	ft_lnkappend(origin, normal);
	ft_lnkappend(target, reverse);
	return (0);
}

void				ft_lnkdel(t_rb_node *node)
{
	t_link *tmp;

	if (!(node->link))
		return ;
	tmp = node->link->next;
	free(node->link);
	while (tmp)
	{
		node->link = tmp;
		tmp = node->link->next;
		free(node->link);
	}
}
