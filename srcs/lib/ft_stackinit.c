/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 11:58:31 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/29 12:02:53 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lnode			*ft_stackinit(t_lemin *lem)
{
	t_lnode *tmp;

	if (!(tmp = ft_lnodnew(0)))
		return (NULL);
	tmp->node = lem->start;
	tmp->node->exploration = lem->exploration;
	return (tmp);
}
