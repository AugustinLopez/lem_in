/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:58:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/21 12:35:04 by bcarlier         ###   ########.fr       */
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

static inline int	parser_first_tube(t_lemin *lem)
{
	if (is_tube(lem, (char *)(lem->curline->pv)) == -1)
	{
		if (lem->fileline == lem->curline)
		{
			free(lem->fileline->pv);
			ft_memdel((void **)&(lem->fileline));
		}
		else
		{
			lem->curline = lem->fileline;
			while (lem->curline->next->next)
				lem->curline = lem->curline->next;
			free(lem->fileline->next->pv);
			ft_memdel((void **)&(lem->fileline->next));
		}
		return (-1);
	}
	++(lem->nbr_tube);
	return (0);
}

int					parser(t_lemin *lem)
{
	int		ret;

	ret = 0;
	if (parser_ant(lem) == -1 || lem->nbr_ant == 0)
		ret = 1;
	else if (parser_room(lem) == -1)
		ret = 2;
	else if (parser_first_tube(lem) == -1 || parser_tube(lem) == -1)
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
