/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnodnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 11:46:01 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/29 11:46:10 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
