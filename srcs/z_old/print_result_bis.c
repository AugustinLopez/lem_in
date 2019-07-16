/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/15 00:55:51 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

size_t				lstlongest_bis(t_list *begin, size_t *nbr, size_t max)
{
	size_t	n;
	t_list	*tmp;

	tmp = begin;
	n = 0;
	*nbr = 0;
	while (tmp)
	{
		if (tmp->zu && n < tmp->zu - 1 && tmp->zu - 1 < max)
		{
			n = tmp->zu - 1;
			*nbr = 1;
		}
		else if (tmp->zu && n == tmp->zu - 1 && tmp->zu - 1 < max)
			++(*nbr);
		tmp = tmp->next;
	}
	return (n);
}

size_t				lst2ndlongest(t_list *begin, size_t nbr)
{
	size_t	n;
	t_list	*tmp;

	tmp = begin;
	n = 0;
	while (tmp)
	{
		if (tmp->zu && n < tmp->zu - 1 && tmp->zu - 1 < nbr)
			n = tmp->zu - 1;
		tmp = tmp->next;
	}
	return (n);
}

int				solve_paths(t_lemin *lem, t_list *road, size_t ant_id)
{
	t_list	*tmp;
	t_list	*begin;
	int		a;

	a = 0;
	begin  = road->pv;
	tmp = begin;
	while (get_node(tmp) != lem->start)
		tmp = tmp->next;
	if (ant_id <= lem->nbr_ant)
		tmp->zu = ant_id;
	else
		tmp->zu = 0;
	while (begin->next && begin->next->zu == 0)
		begin = begin->next;
	tmp = begin;
	while (tmp->next)
	{
		tmp->zu = tmp->next->zu;
		if (tmp->zu)
		{
			a = 1;
			ft_printf("L%zu-%s ", tmp->zu, get_node(tmp)->name);
		}
		tmp = tmp->next;
	}
	return (a);
}

void	different_paths(t_lemin *lem, size_t *ant_id, size_t *length, size_t *nbr_path)
{
	size_t	second;
	size_t	max_bis;
	size_t	nbr_max;
	size_t	nbr_temp;
	float	p1;
	float	p2;
	size_t	s1;
	size_t	s2;
	size_t	tmp;
	t_list	*road;
	//select best "base case"
	//See if base case can be improved by using a single bigger path.
	//FOr instance, if base case give 35 with base case 29, and
	//there is a 32, 33 and 34 path, then 32 and 33 are improvements but not
	//34 because: 35 - 1 >= 32 --> 34 - 1 >= 33 --> 33 - 1 < 34
	*length = lstlongest_bis(lem->path, &nbr_max, -1);
	max_bis = nbr_max;
	second = *length;
	ft_printf("\n");
	while (*nbr_path > nbr_max)
	{
		while ((second = lstlongest_bis(lem->path, &nbr_temp, second)))
		{
			tmp = (lem->nbr_ant - *ant_id);
			p1 = (tmp + 0.0) / *nbr_path + *length - 1;
			p2 = (tmp + 0.0) / (*nbr_path - nbr_max) + second - 1;
			ft_printf("%f %f | %d %d | %d %d \n", p1, p2, *length, second, *nbr_path, nbr_max);
			if (p1 > p2)
				break ;
			nbr_max += nbr_temp;
		}
		if (!second)
		{
			road = lem->path;
			while (road)
			{
				road->zu - 1 <= *length
					? solve_paths(lem, road, ++(*ant_id))
					: solve_paths(lem, road, -1);
				road = road->next;
				if (*ant_id > lem->nbr_ant)
				{
					ft_printf("\n");
					return ;
				}
			}
			nbr_max = max_bis;
			second = *length;
			ft_printf("\n");
		}
		else
		{
			*nbr_path -= max_bis;
			*length = lstlongest_bis(lem->path, &nbr_max, *length);
			max_bis = nbr_max;
			second = *length;
		}
	}
}
void	similar_paths(t_lemin *lem, size_t *ant_id, size_t length)
{
	t_list	*road;

	while (lem->nbr_ant > *ant_id)
	{
		road = lem->path;
		while (road)
		{
			if (road->zu - 1 <= length)
				solve_paths(lem, road, ++(*ant_id));
			else
				solve_paths(lem, road, -1);
			road = road->next;
		}
		ft_printf("\n");
	}
}

void	finish_path(t_lemin *lem)
{
	char	a;
	t_list	*road;

	a = 1;
	while (a)
	{
		a = 0;
		road = lem->path;
		while (road)
		{
			if (solve_paths(lem, road, -1))
				a = 1;
			road = road->next;
		}
		if (a)
			ft_printf("\n");
	}
}

void				populate_path_array(t_lemin *lem, t_pathprint *print)
{
	size_t	min;
	t_list	*tmp;

	min = 0;
	while (print->index < print->path)
	{
		tmp = lem->path;
		(print->number)[print->index] = 0;
		(print->length)[print->index] = -1;
		while (tmp)
		{
			if (tmp->zu && tmp->zu - 1 < (print->length)[print->index]
					&& tmp->zu - 1 > min)
			{
				(print->length)[print->index] = tmp->zu - 1;
				(print->number)[print->index] = 1;
			}
			else if (tmp->zu && tmp->zu - 1 == (print->length)[print->index]
					&& tmp->zu - 1 > min)
				++((print->number)[print->index]);
			tmp = tmp->next;
		}
		ft_printf("%d %d %d\n", print->index, (print->length)[print->index], (print->number)[print->index]); //print
		min = (print->length)[print->index];
		if ((print->number)[print->index] == 0)
			break ;
		print->max_index = print->index;
		++(print->index);
	}
}




void	different_paths_bis(t_lemin *lem, t_pathprint *print, size_t *length)
{
	float	p1;
	float	p2;
	float	tmp;
	t_list	*road;
	//select best "base case"
	//See if base case can be improved by using a single bigger path.
	//FOr instance, if base case give 35 with base case 29, and
	//there is a 32, 33 and 34 path, then 32 and 33 are improvements but not
	//34 because: 35 - 1 >= 32 --> 34 - 1 >= 33 --> 33 - 1 < 34
	*length = (print->length)[print->max_index];
	print->sum_number = (print->number)[print->max_index];
	print->index = print->max_index;
	ft_printf("\n");
	while (print->path > print->sum_number)
	{
		while ((print->index)--)
		{
			tmp = (lem->nbr_ant - print->ant + 0.0);
			p1 = tmp / print->path + (print->length)[print->max_index] - 1;
			p2 = tmp / (print->path - print->sum_number)
					+ (print->length)[print->index] - 1;
			ft_printf("%d %d | %d %d | %f %f\n", (print->length)[print->max_index],  (print->length)[print->index], print->path, print->index, p1, p2);
			if (p1 > p2)
				break ;
			print->sum_number += (print->number)[print->index];
		}
		if (p1 <= p2)
		{
			//need to find if i can use bigger path at this point
			road = lem->path;
			while (road)
			{
				road->zu - 1 <= (print->length)[print->max_index]
					? solve_paths(lem, road, ++(print->ant))
					: solve_paths(lem, road, -1);
				road = road->next;
				if (print->ant > lem->nbr_ant)
				{
					ft_printf("\n");
					*length = (print->length)[print->index];
					return ;
				}
			}
			print->sum_number = (print->number)[print->max_index];
			print->index = print->max_index;
			ft_printf("\n");
		}
		else
		{
			print->path -= (print->number)[print->max_index];
			print->max_index -= 1;
			print->index = print->max_index;
			print->sum_number = (print->number)[print->max_index];
		}
	}
	*length = (print->length)[0];
}


int					solve(t_lemin *lem)
{
	size_t	nbr_path;
	size_t	max_length;
	size_t	index;
	t_pathprint	print;

	ft_bzero(&print, sizeof(print));
	print.path = ft_lstsize(lem->path);
	print.index = 0;
	print.length = ft_memalloc(sizeof(size_t) * print.path);
	print.number = ft_memalloc(sizeof(size_t) * print.path);
	if (!(print.length) || !(print.number))
	{
		ft_memdel((void **)&(print.length));
		ft_memdel((void **)&(print.number));
		return (-1);
	}
	populate_path_array(lem, &print);
	max_length = print.path;
	different_paths_bis(lem, &print, &max_length);
	similar_paths(lem, &(print.ant), max_length);
	finish_path(lem);
	ft_memdel((void **)&(print.length));
	ft_memdel((void **)&(print.number));
	return (0);
}
