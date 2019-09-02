/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 11:42:58 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/02 11:01:04 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lnode	*ft_stackinit(t_lemin *lem)
{
	t_lnode *tmp;

	if (!(tmp = ft_lnodnew(0)))
		return (NULL);
	tmp->node = lem->start;
	tmp->node->exploration = lem->exploration;
	return (tmp);
}

void	ft_stackdelfirst(t_lnode **stack)
{
	t_lnode *tmp;

	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	if (*stack)
		(*stack)->prev = 0;
}

void	ft_stackdel(t_lnode *stack)
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
