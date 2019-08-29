/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 11:42:58 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/29 11:43:00 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_stackdel(t_lnode *stack)
{
	t_lnode	*iter;

	if (stack)
	{
		iter = stack;
		while (iter)
		{
			stack = iter;
			iter = iter->next;
			free(stack);
		}
	}
}
