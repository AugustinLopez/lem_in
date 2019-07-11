/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/11 14:39:08 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>

/*__attribute__((destructor)) void loop(void)
{
	for(;;);
}*/

size_t				lstlongest_bis(t_list *begin, size_t *nbr)
{
	size_t	n;
	t_list	*tmp;

	tmp = begin;
	n = 0;
	*nbr = 0;
	while (tmp)
	{
		if (tmp->zu && n < tmp->zu - 1)
		{
			n = tmp->zu - 1;
			*nbr = 1;
		}
		else if (tmp->zu && n == tmp->zu - 1)
			++(*nbr);
		tmp = tmp->next;
	}
	tmp = begin;
	while (tmp)
	{
		if (n == tmp->zu - 1)
			tmp->zu = 0;
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



int					solve(t_lemin *lem)
{
	size_t	nbr_path;
	size_t	max_length;
	size_t	nbr_max;
	size_t	second;
	size_t	ant;

	ant = lem->nbr_ant;
	nbr_path = ft_lstsize(lem->path);
	max_length = lstlongest_bis(lem->path, &nbr_max);
	second = lst2ndlongest(lem->path, max_length);
	ft_printf("N:%d A:%d Max:%d Nbr:%d\n", nbr_path, ant, max_length, nbr_max);
	ft_printf("Max:%d VS %d Left\n", max_length, ant / (nbr_path - nbr_max) + second);
	ant -= nbr_path;
	ft_printf("N:%d A:%d Max:%d Nbr:%d\n", nbr_path, ant, max_length, nbr_max);
	ft_printf("Max:%d VS %d Left\n", max_length, ant / (nbr_path - nbr_max) + second);
	return (0);
}

int					main(void)
{
	t_lemin	lem;
	int		ret;

	ft_bzero(&lem, sizeof(lem));
	ret = reader(&lem);
	if (!ret)
		ret = dijkstra(&lem);
	//Need to do one pass of dijkstra like, and one with priority given to path with less link
	if (!ret)
	{
		print_path(&lem);
		remove_bad_paths(&lem);
		print_path(&lem);
		solve(&lem);
		solve_one_path(&lem);
	}
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	ft_lstdel(&(lem.path), *lstoflst);
	return (ret);
}
