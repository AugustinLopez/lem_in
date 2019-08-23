/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnkdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 11:43:19 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/23 12:23:40 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

void	ft_lnkdel(t_rb_node *node)
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

void	ft_roadlistdel(t_roadlist *roads)
{
	t_link	*tmp;

	if (!(roads->first))
		return ;
	roads->current = road->first;
	while (roads->current)
	{
		tmp = roads->current->km;
		while (tmp)
		{
			roads->current->km = tmp;
			tmp = roads->current->km->next;
			free(roads->current->km);
		}
		roads->first = roads->current;
		roads->current = roads->first->next;
		free(roads->first);
	}
}
