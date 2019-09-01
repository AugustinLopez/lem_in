/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:29:12 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/02 00:15:27 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>
#include <rb_tree.h>

static inline int	lem_atoll_minus(const char *src, long long *result,
						size_t *index)
{
	long long	limit;

	limit = LLONG_MAX;
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

static inline int	lem_atoll(const char *src, long long *result, size_t *index)
{
	long long	limit;

	if (src[*index] == '-')
		return (lem_atoll_minus(src, result, index));
	limit = LLONG_MAX;
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

static inline int	is_room(t_lemin *lem, char *line, uint8_t *command)
{
	size_t		i;
	t_tree_data	room;

	room.fin = 0;
	room.line = line;
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
	if (lem_feed_tree(lem, &room, *command) == -1)
		return (0);
	if (lem->flags & F_COORDINATE && lem_feed_xy(lem, &room, *command) == -1)
		return (0);
	++(lem->nbr_room);
	return (1);
}

static inline int	is_command(char *line, uint8_t *command)
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

int					parser_room(t_lemin *lem, char **line)
{
	int		ret;
	uint8_t	command;

	command = 0;
	while ((ret = ft_gnl(STDIN_FILENO, line, 1) > 0))
	{
		if (is_comment(*line))
			ret = 1;
		else if (!(ret = is_command(*line, &command)))
			ret = is_room(lem, *line, &command);
		if (ret == 1 && !(lem->flags & F_NOFILE))
				ft_printf("%s", *line);
		else if (!(ret == 1))
		{
			if (command != (LEM_END | LEM_START))
				ret = -1;
			if (ret == -1)
				free(*line);
			return (ret);
		}
		free(*line);
	}
	return (-1);
}
