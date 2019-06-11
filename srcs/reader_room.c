/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:29:12 by aulopez           #+#    #+#             */
/*   Updated: 2019/06/11 15:28:09 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>

static inline t_rb_node	*lem_rb_create(t_lemin *lem, t_tree_data *data)
{
	t_rb_node	*tmp;

	if (!(tmp = (t_rb_node *)malloc(sizeof(*tmp))))
		return (NULL);
	ft_bzero(tmp, sizeof(*tmp));
	if (!(tmp->name = ft_strsub(data->line, 0, data->fin)))
	{
		free(tmp);
		return (NULL);
	}
	tmp->x = data->x;
	tmp->y = data->y;
	tmp->flag = RB_RED;
	if (!lem->end && (data->command & LEM_END))
		lem->end = tmp;
	else if (!lem->start && (data->command & LEM_START))
		lem->start = tmp;
	return (tmp);
}

static inline int		feed_tree(t_lemin *lem, t_tree_data *room)
{
	t_rb_node	*tmp;

	if (!(tmp = lem_rb_create(lem, room)))
		return (-2);
	if (rb_insert(&(lem->tree), tmp) == -1)
	{
		free(tmp->name);
		free(tmp);
		return (-2);
	}
	ft_printf("%s %lld %lld\n", tmp->name, tmp->x, tmp->y);
	return (1);
}

/*
** IS_ROOM:
** NAME ANALYSIS:
** 1. Leading whitespace are treated as normal character. Name cannot be empty.
** 2. The name must not start with #, L or ' '.
** 3. At the first ' ', we stop the name analysis.
** 4.' ', '-', '\0' or '\n' in the name -> undefined behavior.
**
** Reasoning:
** 1. Whitespace are technically valid character.
** An absence of character is not a valid character.
** 2. Written in subject. Leading space are refused because of 1. and 4.
** 4. The subject does not indicates how to deal with those special characters.
** The special meaning will be prioritized before potential naming purpose.
**
** COORDINATE ANALYSIS:
** 1. A single ' ' is expected before a coordinate.
** 2. Numbers must be containable in a long long.
** 3. The first character of a number must be a digit greater than 0 or a '-'
** 4. The first character following a '-' must be a digit greater than 0.
** 5. Following characters must be digits between 0 and 9.
** 6. Last character must be a line feed.
**
** Reasoning:
** 1. Subject.
** 2. Best compromise for potential negative number.
** 4-5. Leading '+' and '0' are a nonstandard decimal notation. Thousands
** separator are nonstandard either.
*/

static inline int	is_room(t_lemin *lem, char *line, int *command)
{
	size_t		i;
	t_tree_data	room;

	room.fin = 0;
	room.line = line;
	room.command = *command;
	while (line[room.fin] && line[room.fin] != ' ')
		room.fin++;
	if (ft_strchr("#L ", line[0]) || room.fin == 0 || line[room.fin] != ' ')
		return (0);
	i = room.fin + 1;
	if (!line[i] || line[i] == '\n' || lem_atoll(line, &room.x, &i)
			|| line[i] != ' ')
		return (0);
	i = i + 1;
	if (!line[i] || line[i] == '\n' || lem_atoll(line, &room.y, &i)
			|| line[i] != '\n')
		return (0);
	*command &= ~LEM_COMMAND;
	return (feed_tree(lem, &room));
}

/*
** IS_COMMAND:
** A command is either "##start" or "##end" followed by a line feed. No
** exception, whitespace, uppercase, etc...
** A command cannot be immediately followed by another command.
** A command cannot be repeated at any point.
** An invalid command should have been interpreted as a
** comment and ignored prior to this point.
*/

static inline int	is_command(char *line, int *command)
{
	if (line[0] == '#' && (!ft_strlcmp(line + 1, "#end\n")))
	{
		if (*command & (LEM_END | LEM_COMMAND))
			return (-1);
		*command |= (LEM_END | LEM_COMMAND);
		return (1);
	}
	if (line[0] == '#' && (!ft_strlcmp(line + 1, "#start\n")))
	{
		if (*command & (LEM_START | LEM_COMMAND))
			return (-1);
		*command |= (LEM_START | LEM_COMMAND);
		return (1);
	}
	return (0);
}

/*
** READER_ROOM:
** Commands/rooms are always the 2nd type of info (besides possible comments).
** It cannot be the last information.
** We save input in a list if not a comment. We return malloc failure.
** If the last valid line is command or if we don't have a start or an end,
** we return an error.
*/

int					reader_room(t_lemin *lem)
{
	int		ret;
	char	*line;
	int		command;

	command = 0;
	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		if (is_comment(line) == 0)
		{
			if (!(ret = is_command(line, &command)))
				ret = is_room(lem, line, &command);
			if (ret == 0 && command != (LEM_START + LEM_END))
				ret = -1;
			else if (push_in_file(lem, line) == -1)
				ret = -2;
		}
		free(line);
		if (ret <= 0)
			return (ret);
	}
	return (-1);
}
