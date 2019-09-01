/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/01 18:17:45 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int					is_comment(char *line)
{
	if (line[0] == '#')
	{
		if (!ft_strcmp(line + 1, "#start\n") || !ft_strcmp(line + 1, "#end\n"))
			return (0);
		return (1);
	}
	return (0);
}

int					parser(t_lemin *lem)
{
	int		ret;
	char	*line;

	line = 0;
	ret = 0;
	if (parser_ant(lem) == -1
			|| lem->nbr_ant == 0
			|| parser_room(lem, &line) == -1
			|| parser_tube(lem, &line) == -1
			|| lem->nbr_tube == 0
			|| lem->nbr_room == 0
			|| lem->start->nbr_link == 0
			|| lem->end->nbr_link == 0)
		ret = -1;
	ft_gnl(-1, 0, 0);
	if (!ret && !(lem->flags & F_NOFILE))
		ft_printf("\n");
	return (ret);
}
