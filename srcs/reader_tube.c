/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:35:56 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/08 21:24:55 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static inline int	create_link(t_rb_node *left, t_rb_node *right)
{
	t_list	*node;

	if (!(node = ft_lstnew(0, 0)))
		return (-1);
	node->pv = right;
	if (!(left->link))
	{
		left->link = node;
		left->flag = 0;
	}
	else
		ft_lstadd(&(left->link), node);
	if (!(node = ft_lstnew(0, 0)))
		return (-1);
	node->pv = left;
	if (!(right->link))
	{
		right->link = node;
		right->flag = 0;
	}
	else
		ft_lstadd(&(right->link), node);
	left->nbr_link += 1;
	right->nbr_link += 1;
	return (0);
}

static inline int	check_duplicate(t_rb_node *left, void *right)
{
	t_list	*tmp;

	if (!(tmp = left->link))
		return (0);
	if (left == right)
		return (1);
	while (tmp)
	{
		if (tmp->pv == right)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static inline int	proceed_with_tube(t_lemin *lem, char *line, size_t i,
						size_t j)
{
	t_rb_node	*left;
	t_rb_node	*right;

	line[i] = 0;
	line[j] = 0;
	left = lem_find_node(lem->tree, line);
	right = lem_find_node(lem->tree, line + i + 1);
	line[i] = '-';
	line[j] = '\n';
	if (!(left && right))
		return (-1);
	else if (check_duplicate(left, right) == 0)
		return (create_link(left, right));
	else
		return (0);
}

static inline int	is_tube(t_lemin *lem, char *line)
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

int					reader_tube(t_lemin *lem)
{
	int		ret;
	char	*line;

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
