/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:29:12 by aulopez           #+#    #+#             */
/*   Updated: 2019/06/10 18:27:24 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>
/*
** LEM_ATOLL:
** We use limits to get the max value of a signed long long.
** We built a limit akin to 10 (LOG(LLONG_MAX) - 1). (No problem as long as
** LOG(LLONG_MAX) == LOG(ABS(LLONG_MIN)) is true for the integer part).
** Thus we know when an over/underflow might happens.
** return -1 in case of over/underflow.
** return 0 at the 1st character that is not a digit, including '\0'. Exception
** for the minus sign: must be the 1st character.
** return 0 if the 1st character (or 2nd after minus) is '0': no leading '0'.
**
** Each characters is treated one by one, starting from the beginning.
** *result contains the final calculated value. *index is increased by one
** for each valid character treated: use it for additional error check.
*/

static inline int	lem_atoll_minus(const char *src, long long *result,
						size_t *index)
{
	long long	limit;
	long long	tmp;

	limit = LLONG_MAX;
	tmp = LLONG_MAX;
	*result = 1;
	while ((limit /= 10))
		*result *= 10;
	limit = -(*result / 10);
	*index = *index + 1;
	*result = 0;
	if (src[*index] == '0')
	{
		*index = *index + 1;
		return (0);
	}
	while ('0' <= src[*index] && src[*index] <= '9' && *result > limit)
		*result = *result * 10 - src[(*index)++] + '0';
	if ('0' <= src[*index] && src[*index] <= '9')
	{
		*result = *result * 10 - (src[(*index)++] - '0');
		if ((*result > -10) || ('0' <= src[*index] && src[*index] <= '9'))
			return (-1);
	}
	return (0);
}

int					lem_atoll(const char *src, long long *result, size_t *index)
{
	long long	limit;
	long long	tmp;

	if (src[*index] == '-')
		return (lem_atoll_minus(src, result, index));
	limit = LLONG_MAX;
	tmp = LLONG_MAX;
	*result = 1;
	while ((limit /= 10))
		*result *= 10;
	limit = *result / 10;
	*result = 0;
	if (src[*index] == '0')
	{
		*index = *index + 1;
		return (0);
	}
	while ('0' <= src[*index] && src[*index] <= '9' && *result < limit)
		*result = *result * 10 + src[(*index)++] - '0';
	if ('0' <= src[*index] && src[*index] <= '9')
	{
		*result = *result * 10 + (src[(*index)++] - '0');
		if ((*result < 10) || ('0' <= src[*index] && src[*index] <= '9'))
			return (-1);
	}
	return (0);
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

int	is_command(char *line, int *command)
{
	size_t	i;

	i = lem_whitespace(line, 0);
	if (line[i] == '#' && (!ft_strlcmp(line + i + 1, "#end\n")))
	{
		if (*command & (LEM_END | LEM_COMMAND))
			return (-1);
		*command |= LEM_END | LEM_COMMAND;
		return (1);
	}
	if (line[i] == '#' && (!ft_strlcmp(line + i + 1, "#start\n")))
	{
		if (*command & (LEM_START | LEM_COMMAND))
			return (-1);
		*command |= LEM_START | LEM_COMMAND;
		return (1);
	}
	return (0);
}

/*
** IS_ROOM:
** NAME ANALYSIS:
** 1. Leading whitespace are treated as normal character.
** 2. The name must not start with # or L.
** 3. At the first ' ', we stop the name analysis.
** 4.' ', '-' or '\n' in the name -> undefined behavior.
**
** Reasoning:
** 1. Whitespace are technically normal ascii character.
** 2. Written in subject.
** 4. The subject does not indicates how to deal with those special character.
** If a special meaning is possible, it will be used as such.
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

t_rb_node	*lem_rb_create(t_lemin *lem, t_tree_data *data)
{
	t_rb_node	*tmp;

	if (!(tmp = (t_rb_node *)malloc(sizeof(*tmp))))
		return (NULL);
	if (!(tmp->name = ft_strsub(data->line, 0, data->fin)))
	{
		free(tmp);
		return (NULL);
	}
	tmp->x = data->x;
	tmp->y = data->y;
	tmp->right = 0;
	tmp->left = 0;
	tmp->parent = 0;
	tmp->flag = RB_RED;
	if (!lem->end && (data->command & LEM_END))
		lem->end = tmp;
	else if (!lem->start && (data->command & LEM_START))
		lem->start = tmp;
	return (tmp);
}

int	is_room(t_lemin *lem, char *line, int command)
{
	size_t		i;
	t_tree_data	room;
	t_rb_node	*tmp;

	ft_bzero(&room, sizeof(room));
	room.line = line;
	room.command = command;
	while (line[room.fin] && line[room.fin] != ' ')
		room.fin++;
	if (ft_strchr("#L", line[0]) || room.fin == 0 || line[room.fin] != ' ')
		return (0);
	i = room.fin + 1;
	if (!line[i] || line[i] == '\n' || lem_atoll(line, &room.x, &i)
		|| line[i] != ' ')
		return (0);
	i = i + 1;
	if (!line[i] || line[i] == '\n' || lem_atoll(line, &room.y, &i)
		|| (line[i] && line[i] != '\n'))
		return (0);
	if (!(tmp = lem_rb_create(lem, &room)))
		return (-1);
	if (rb_insert(&(lem->tree), tmp) == -1)
	{
		free(tmp->name);
		free(tmp);
		return (-1);
	}
	ft_printf("%s %lld %lld\n", tmp->name, tmp->x, tmp->y);
	return (1);
}

/*
** READER_ROOM:
** Commands/rooms are always the 2nd type of info (besides possible comments).
** It cannot be the last information.
** We save input in a list if not a comment. We return malloc failure.
** If the last valid line is command or if we don't have a start or an end,
** we return an error.
*/


static inline int	finish_room(t_lemin *lem, int command, char *line)
{
	if (command != (LEM_START + LEM_END))
	{
		free(line);
		return (-1);
	}
	if (push_in_file(lem, line) == -1)
		return (-2);
	free(line);
	return (0);
}

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
			if ((ret = is_command(line, &command)))
			{
				if (ret == -1)
					return (finish_room(lem, -1, line));
			}
			else if ((ret = is_room(lem, line, command)))
			{
				if (ret == -1)
					return (finish_room(lem, -1, line));
				command &= ~LEM_COMMAND;
			}
			else
				return (finish_room(lem, command, line));
			if (push_in_file(lem, line) == -1)
				return (-2);
		}
		free(line);
	}
	return (-1);
}
