/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnodadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 11:10:25 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/01 23:05:23 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

t_lnode*	ft_lnodnew(t_lnode *stack)
{
	t_lnode	*tmp;
	t_lnode	*iter;

	tmp = (t_lnode *)malloc(sizeof(*tmp));
	if (!tmp)
	{
		if (stack != NULL)
		{
			iter = stack;
			while (iter)
			{
				tmp = iter;
				iter = iter->next;
				free(tmp);
			}
			tmp = NULL;
		}
	}
	else
		ft_bzero(tmp, sizeof(*tmp));
	return (tmp);
}

void	ft_lnodadd(t_lnode **lnode, t_lnode *new)
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
