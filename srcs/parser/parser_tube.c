/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:35:56 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/22 16:43:44 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*static inline int	create_link(t_rb_node *origin, t_rb_node *target)
{
	t_link	*node;

	if (!(node = ft_lnknew(0, 0)))
		return (-1);
	node->pv = target;
	if (!(origin->link))
	{
		origin->link = node;
		origin->flag = 0;
	}
	else
		ft_lnkadd(&(origin->link), node);
	if (!(node = ft_lnknew(0, 0)))
		return (-1);
	node->pv = origin;
	if (!(target->link))
	{
		target->link = node;
		target->flag = 0;
	}
	else
		ft_lnkadd(&(target->link), node);
	origin->nbr_link += 1;
	target->nbr_link += 1;
	return (0)
}*/

static inline int	check_duplicate(t_rb_node *origin, t_rb_node *target)
{
	t_link	*tmp;

	if (!(tmp = origin->link))
		return (0);
	if (origin == target)
		return (1);
	while (tmp)
	{
		if (tmp->target == target)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static inline int	proceed_with_tube(t_lemin *lem, char *line, size_t i,
						size_t j)
{
	t_rb_node	*origin;
	t_rb_node	*target;
	int			ret;

	line[i] = 0;
	line[j] = 0;
	origin = lem_find_node(lem->tree, line);
	target = lem_find_node(lem->tree, line + i + 1);
	line[i] = '-';
	line[j] = '\n';
	if (!(origin && target))
		return (-1);
	else if (check_duplicate(origin, target) == 0)
	{
		if ((ret = ft_lnknew(origin, target)) != -1)
			++(lem->nbr_tube);
		return (ret);
	}
	else
		return (0);
}

int					is_tube(t_lemin *lem, char *line)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	j = i;
	if (line[j++] != '-' || !line[j] || line[j] == '\n')
		return (-1);
	while (line[j] && line[j] != '\n')
		j++;
	if (line[j] != '\n')
		return (-1);
	return (proceed_with_tube(lem, line, i, j));
}

int					parser_tube(t_lemin *lem)
{
	int		ret;
	char	*line;

	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		if (!(ret = is_comment(line)))
			ret = is_tube(lem, line);
		if (ret < 0 || save_line(lem, line) == -1)
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (0);
}
