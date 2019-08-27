/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 11:10:25 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/27 17:04:24 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

void	ft_nodadd(t_lnode **lnode, t_lnode *new)
{
	t_lnode	*tmp;

	tmp = *lnode;
	while (tmp->next)
	{
		if (tmp->next->node->depth > new->node->depth)
		{
			new->next = tmp->next;
			tmp->next->prev = new;
			new->prev = tmp;
			tmp->next = new;
			return ;
		}
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
}
