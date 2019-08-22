/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnkdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 11:43:19 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/22 16:52:50 by bcarlier         ###   ########.fr       */
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
