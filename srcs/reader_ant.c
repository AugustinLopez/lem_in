/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_ant.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:26:54 by aulopez           #+#    #+#             */
/*   Updated: 2019/06/12 10:48:18 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
** LEM_ATOZU:
** We use an underflow to get the max value of a size_t
** We built a limit akin to 10 ^ (log(MAX_SIZE_T) - 1)
** Thus we know when an overflow might happens and deal with it accordingly.
** Return -1 in case of over/underflow.
** Return 0 at the first character that is not a digit, including '\0'.
** Return 0 if the first character is a '0': no leading '0'.
**
** Each character is treated one by one, starting from the beginning.
** *result contains the final calculated value. *index is increased by one
** for each valid character treated: use it for additional error check.
*/

/*
** IS_ANT:
** 1- No leading nor trailing whitespace accepted.
** 2- The first character must be a digit greater than 0.
** 3- Following characters must be digits between 0 and 9.
** 4- Last character must be a line feed.
** 5- The number must be containable in a size_t.
** Reasoning:
** 1- Whitespace are not part of a number and are regular ascii character.
** 2- We cannot treat a negative number of ants.
** Leading '+' and '0' are a nonstandard decimal notation. Thousands separator
** (' ', '.', ',', ...) are nonstandard either.
** 5- Best compromise for a positive value.
*/

/*
** READER_ANT:
** The first information must the number of ant (beside possible comments).
** It cannot be the last information.
** We save input in a list if not a comment. We return malloc failure.
*/

static inline int	lem_atozu(const char *src, size_t *result, size_t *index)
{
	size_t	limit;

	limit = -1;
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
			ret = save_line(lem, line);
			free(line);
			return (ret);
		}
		free(line);
	}
	return (-1);
}
