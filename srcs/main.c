/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:35:43 by bcarlier          #+#    #+#             */
/*   Updated: 2019/05/16 11:57:48 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <lem_in.h>

int	parser_master(t_lemin *lem)
{
	ssize_t	ret;
	char	*line;

	ret = 0;
	(void)lem;
	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		ft_printf("%s", line);
		free(line);
	}
	return (0);
}

int	main(void)
{
	t_lemin	lem;
	int		ret;

	ft_bzero(&lem, sizeof(lem));
	ret = parser_master(&lem);
	return (ret);
}
