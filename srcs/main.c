/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/10 11:19:09 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>

/*__attribute__((destructor)) void loop(void)
{
	for(;;);
}*/

size_t				lstlongest(t_list *begin, size_t *nbr)
{
	size_t	n;
	t_list	*tmp;

	tmp = begin;
	n = 0;
	*nbr = 0;
	while (tmp)
	{
		if (n < tmp->zu)
		{
			n = tmp->zu;
			*nbr = 0;
		}
		else if (n == tmp->zu)
			++(*nbr);
		tmp = tmp->next;
	}
	return (n);
}

int					solve(t_lemin *lem)
{
	size_t	iter;
	size_t	nbr_path;
	size_t	max_length;
	size_t	nbr_max;

	iter = 0;
	nbr_path = ft_lstsize(lem->path);
	max_length = lstlongest(lem->path);
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
	//	print_path(&lem);
		remove_bad_paths(&lem);
		print_path(&lem);
		solve_one_path(&lem);
	}
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	ft_lstdel(&(lem.path), *lstoflst);
	return (ret);
}
