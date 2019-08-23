/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/23 11:20:24 by aulopez          ###   ########.fr       */
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
			|| parser_tube(lem, &line) == -1)
	{
		ret = -1;
		ft_dprintf(STDERR_FILENO, "ERROR\n");
	}
	ft_gnl(-1, 0, 0);
	return (ret);
}
