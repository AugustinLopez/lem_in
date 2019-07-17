/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/17 13:32:41 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

int					main(int ac, char **av)
{
	t_lemin	lem;
	int		ret;

	ft_bzero(&lem, sizeof(lem));
	ret = parser(&lem);
	if (!ret)
		ret = edmundkarp(&lem);
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	if (ac == 2)
	{
		ft_printf("Ant's number:  %zu\n", lem.nbr_ant);
		ft_printf("Room's number: %zu\n", lem.nbr_room);
		ft_printf("Tube's number: %zu\n", lem.nbr_tube);
	}
	return (ret);
}
