/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/11 13:46:12 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int					is_comment(char *line)
{
	size_t	i;

	i = 0;
	if (line[i] == '#' && (line[i + 1] != '#'))
		return (1);
	else if ((line[i] == '#' && line[i + 1] == '#')
			&& (!ft_strcmp(line + i + 2, "start\n")
				&& !ft_strcmp(line + i + 2, "end\n")))
		return (1);
	return (0);
}

int					save_line(t_lemin *lem, char *line)
{
	if (!lem->fileline)
	{
		if (!(lem->fileline = ft_lstnew(0, 0)))
			return (-1);
		lem->curline = lem->fileline;
		if (!(lem->fileline->pv = ft_strdup(line)))
			return (-1);
	}
	else
	{
		if (!(lem->curline->next = ft_lstnew(0, 0)))
			return (-1);
		lem->curline = lem->curline->next;
		if (!(lem->curline->pv = ft_strdup(line)))
			return (-1);
	}
	return (0);
}

int					reader(t_lemin *lem)
{
	int		ret;

	if ((ret = reader_ant(lem)) || lem->nbr_ant == 0)
		ret = 1;
	else if ((ret = reader_room(lem)))
		ret = 2;
	else if ((ret = reader_tube(lem)))
		ret = 3;
	lem->curline = lem->fileline;
	while (lem->curline)
	{
		ft_printf("%s", lem->curline->pv);
		lem->curline = lem->curline->next;
	}
	if (ret)
		ft_dprintf(STDERR_FILENO, "ERROR\n");
	ft_gnl(-1, 0, 0);
	return (ret);
}
