#include <lem_in.h>

/*
** LEM_ATOZU:
** We use an underflow to get the max value of a size_t
** We built a limit akin to 10 ^ (log(MAX_SIZE_T) - 1)
** Thus we know when an overflow might happens and deal with it accordingly.
** We return -1 in case of overflow, 0 otherwise. We keep track of the index
** for additional error check.
** We return immediately if the first character is a '0': we do not treat
** leading zero.
*/

static inline int	lem_atozu(const char *src, size_t *result, size_t *index)
{
	size_t	limit;
	size_t	tmp;

	limit = -1;
	tmp = limit;
	*result = 1;
	while ((limit /= 10))
		*result *= 10;
	limit = *result / 10;
	*result = 0;
	if (src[*index] == '0')
		return (0);
	while ('0' <= src[*index] && src[*index] <= '9' && *result < limit)
		*result = *result * 10 + src[(*index)++] - '0';
	if ('0' <= src[*index] && src[*index] <= '9')
	{
		*result = *result * 10 + src[(*index)++] - '0';
		if (*result < 10 || ('0' <= src[*index] && src[*index] <= '9'))
			return (-1);
	}
	return (0);
}

static inline int	is_ant(t_lemin *lem, char *line)
{
	size_t	i;

	i = 0;
	if (lem_atozu(line, &(lem->nbr_ant), &i) == -1)
		return (0);
	if (!line[i] || line[i] != '\n')
		return (0);
	return (1);
}

/*
** READER_ANT:
** The first information must the number of ant (beside possible comments).
** It cannot be the last information.
** We save input in a list if not a comment. We return malloc failure.
** We keep a strict model:
** - No whitespace accepted.
** - The first character must be a digit greater than 0.
** - Following characters must be digits between 0 and 9.
** - Last character must be a line feed.
** - The number must be containable in a size_t.
** Reasoning:
** - Whitespace are not part of a number.
** - We cannot treat a negative number of ants (making the '+' useless too).
** Leading '+' and '0' are a nonstandard decimal notation. Thousands separator
** (' ', '.', ',', ...) are nonstandard either.
** - NA
** - NA
** - Best compromise (I would rather use int but whatever).
*/

int					reader_ant(t_lemin *lem)
{
	int		ret;
	char	*line;

	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		if (!is_comment(line))
		{
			if (!is_ant(lem, line))
			{
				free(line);
				return (-1);
			}
			ret = push_in_file(lem, line);
			free(line);
			return (ret);
		}
		free(line);
	}
	return (-1);
}
