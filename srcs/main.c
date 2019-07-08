/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/08 12:16:31 by aulopez          ###   ########.fr       */
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

int					main(void)
{
	t_lemin	lem;
	int		ret;

	ft_bzero(&lem, sizeof(lem));
	if ((ret = reader_ant(&lem)) || lem.nbr_ant == 0)
		ft_dprintf(STDERR_FILENO, "ERROR_ANT\n");
	else if ((ret = reader_room(&lem)))
		ft_dprintf(STDERR_FILENO, "ERROR_ROOM\n");
	else if ((ret = reader_tube(&lem)))
		ft_dprintf(STDERR_FILENO, "ERROR_TUBE\n");
	if (!ret)
	{
		lem.curline = lem.fileline;
		while (lem.curline)
		{
			ft_printf("%s", (lem.curline)->pv);
			lem.curline = (lem.curline)->next;
		}
	}
	ft_gnl(-1, 0, 0);
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	return (ret * -1);
}
