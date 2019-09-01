/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/02 00:34:21 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "rb_tree.h"

void	print_help(void)
{
	ft_printf("%susage%s: %s./lem-in%s [%s-%s%s] < [%sinput%s]\n\n",
			FT_UNDER, FT_EOC, FT_BOLD, FT_EOC, FT_BOLD, F_FLAG, FT_EOC,
			FT_UNDER, FT_EOC);
	ft_printf("\t%s-h%s\tShow this help\n", FT_BOLD, FT_EOC);
	ft_printf("\t%s-F%s\tDo not print file\n", FT_BOLD, FT_EOC);
	ft_printf("\t%s-A%s\tDo not print any ants' path\n", FT_BOLD, FT_EOC);
	ft_printf("\t%s-i%s\tShow summary information\n", FT_BOLD, FT_EOC);
	ft_printf("\t%s-s%s\tPrint any new solving path\n", FT_BOLD, FT_EOC);
	ft_printf("\t%s-p%s\tPrint any new list of path\n", FT_BOLD, FT_EOC);
	ft_printf("\t%s-n%s\tPrint the index of the step\n", FT_BOLD, FT_EOC);
	ft_printf("\t%s-c%s\tAdd color to ants' path\n", FT_BOLD, FT_EOC);
	ft_printf("\t%s-e%s\tPrint state of the exploration stack\n",
			FT_BOLD, FT_EOC);
	ft_printf("\t%s-l%s\tSet max ant number to INT_MAX\n", FT_BOLD, FT_EOC);
	ft_printf("\t%s-x%s\tError if duplicated coordinates\n", FT_BOLD, FT_EOC);
}

int		main(int ac, char **av)
{
	t_lemin	lem;

	ft_bzero(&lem, sizeof(lem));
	(void)ft_flagarg(ac, av, &(lem.flags), F_FLAG);
	if (lem.flags & F_HELP)
	{
		print_help();
		return (0);
	}
	if (parser(&lem) == -1 || dijkstra(&lem) == -1)
	{
		lem_free_tree(&(lem.coordinate));
		lem_free_tree(&(lem.tree));
		ft_dprintf(STDERR_FILENO, "ERROR\n");
		return (-1);
	}
	lem_free_tree(&(lem.coordinate));
	while (benjaug(&lem) == 0)
		continue ;
	printer(&lem);
	lem_free_tree(&(lem.tree));
	return (0);
}
