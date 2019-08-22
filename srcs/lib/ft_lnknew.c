/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnknew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 11:10:25 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/22 16:42:08 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

static inline void	ft_lnkadd(t_rb_node *origin, t_link *new)
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
	ft_lnkadd(origin, normal);
	ft_lnkadd(target, reverse);
	return (0);
}
