/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/01 23:07:58 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

static inline void	basic_sort(t_road **array, t_road *first, size_t size)
{
	t_road	*tmp;
	size_t	i;

	i = 0;
	tmp = first;
	while (tmp)
	{
		array[i++] = tmp;
		tmp = tmp->next;
	}
	i = 0;
	while (i < size - 1)
	{
		if (array[i]->length > array[i + 1]->length)
		{
			tmp = array[i];
			array[i] = array[i + 1];
			array[i + 1] = tmp;
			if (i)
				--i;
		}
		else
			++i;
	}
}

int					sort_roadlist(t_roadlist *roadlist)
{
	t_road	**array;
	size_t	i;

	if (roadlist->nbr_road <= 1)
		return (0);
	if (!(array = ft_memalloc(sizeof(*array) * roadlist->nbr_road)))
	{
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (-1);
	}
	basic_sort(array, roadlist->first, roadlist->nbr_road);
	roadlist->first = array[0];
	i = 0;
	while (i < roadlist->nbr_road - 1)
	{
		array[i]->next = array[i + 1];
		++i;
	}
	array[i]->next = NULL;
	free(array);
	return (0);
}
