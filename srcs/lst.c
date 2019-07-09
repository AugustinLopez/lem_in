/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/09 16:32:21 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				lstoflst(void *pv, size_t zu)
{
	t_list	*cur;
	t_list	*tmp;

	cur = (t_list *)pv;
	tmp = cur;
	while (cur)
	{
		tmp = tmp->next;
		free(cur);
		cur = tmp;
	}
	pv = 0;
	(void)zu;
}

t_list				*lstfind(t_list *begin, t_list *elem)
{
	t_list	*tmp;

	tmp = begin->next;
	while (tmp->next)
	{
		if (get_node(tmp) == get_node(elem))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void				lstremove(t_list **begin, t_list *one, t_list *two)
{
	t_list	*elim;
	t_list	*tmp;

	elim = two->zu < one->zu ? one : two;
	if (elim == *begin)
		*begin = (*begin)->next;
	else
	{
		tmp = *begin;
		while (tmp->next != elim)
			tmp = tmp->next;
		tmp->next = tmp->next->next;
	}
	elim->next = 0;
	ft_lstdelone(&elim, *lstoflst);
}

size_t				lstlongest(t_list *begin)
{
	size_t	n;
	t_list	*tmp;

	tmp = begin;
	n = 0;
	while (tmp)
	{
		if (tmp->zu && n < tmp->zu)
			n = tmp->zu;
		tmp = tmp->next;
	}
	return (n);
}

t_list				*lstshortest(t_list *begin)
{
	t_list	*ret;
	t_list	*tmp;

	tmp = begin;
	ret = begin;
	while (tmp)
	{
		if (ret->zu > tmp->zu)
			ret = tmp;
		tmp = tmp->next;
	}
	return (ret);
}
