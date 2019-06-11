/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:35:56 by aulopez           #+#    #+#             */
/*   Updated: 2019/06/11 15:35:56 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int	is_tube(t_lemin *lem, char *line)
{
	size_t	i;
	size_t	j;
	t_rb_node	*tmp;
	t_rb_node	*tmp2;
	t_list		*node;

	(void)lem;
	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	j = i;
	if (line[j++] != '-' || !line[j] || line[j] == '\n')
		return (0);
	while (line[j] && line[j] != '\n')
		j++;
	if (line[j] != '\n')
		return (0);
	line[i] = 0;
	tmp = lem_find_node(lem->tree, line);
	line[i] = '-';
	line[j] = 0;
	tmp2 = lem_find_node(lem->tree, line + i + 1);
	line[j] = '\n';
	if (tmp && tmp2)
	{
		//I need to check existing link to avoid adding the same link 2 time
		if (!(node = ft_lstnew(0, 0)))
			return (-1);
		node->pv = tmp2;
		if (!tmp->link)
			tmp->link = node;
		else
			ft_lstadd(&(tmp->link), node);
		if (!(node = ft_lstnew(0, 0)))
			return (-1);
		node->pv = tmp;
		if (!tmp2->link)
			tmp2->link = node;
		else
			ft_lstadd(&(tmp2->link), node);

	}
	else
		return (0);
	tmp2 = tmp2->link->pv;
	tmp = tmp->link->pv;
	if (tmp2->link->next || tmp->link->next)
		ft_printf("Y:");
	else
		ft_printf("N:");
	ft_printf("%s-%s\n", tmp2->name, tmp->name);
	return (1);
}

/*
** READER_TUBE:
** This function come after Reader_room. At this point we did an additional
** reading which is neither a room or a comment: hence the check before the
** read loop.
** The tube are the last information. They come after the room.
** We save input in a list if not a comment. We return malloc failure.
** Model:
** - No whitespace accepted.
*/

int				reader_tube(t_lemin *lem)
{
	int		ret;
	char	*line;

	if (is_tube(lem, (char *)(lem->tmp->pv)) == 0)
		return (-1);
	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		if (!is_comment(line))
		{
			if (!is_tube(lem, line))
			{
				free(line);
				return (-1);
			}
			if (push_in_file(lem, line) == -1)
			{
				free(line);
				return (-2);
			}
		}
		free(line);
	}
	return (0);
}
