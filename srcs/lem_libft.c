/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:45:39 by bcarlier          #+#    #+#             */
/*   Updated: 2019/06/07 13:39:14 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static size_t	trim_strlen(const char *s)
{
	size_t	len;
	size_t	offset;

	len = 0;
	offset = 0;
	while (*s)
	{
		if (*s == ' ' || *s == '\t')
			++offset;
		else
			offset = 0;
		++s;
		++len;
	}
	return (len - offset);
}

char			*lem_strtrim(char const *s)
{
	char	*p;
	char	*buf;
	size_t	len;

	if (!s)
		return (0);
	while (*s == ' ' || *s == '\t')
		s++;
	len = trim_strlen(s);
	if (!(p = ft_strnew(len)))
		return (0);
	buf = p;
	while (len--)
		*(buf++) = *(s++);
	*buf = '\0';
	return (p);
}

/*
** We could handle whitespace in a more complex way using those functions.
** But we want to keep a rigid structure to avoid potential error.
** We keep those so it would be easier to add a more complex handling
** in the future.
*/

size_t			lem_whitespace(char *line, size_t i)
{
	if (i && line[i])
		i++;
	return (i);
}

size_t			lem_endspace(char *line, size_t i)
{
	(void)line;
	return (i);
}

int				lem_atozu(const char *src, size_t *result, size_t *index)
{
	size_t	limit;
	size_t	tmp;

	limit = -1;
	*result = 1;
	while ((limit /= 10))
		*result *= 10;
	tmp = -1;
	limit = *result / 10;
	*result = 0;
	*index = (src[*index] == '+') ? *index + 1 : *index;
	while (src[*index] == '0')
		*index = *index + 1;
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

int				lem_atoll(const char *src, long long *result, size_t *index)
{
	long long	limit;
	long long	tmp;
	char		minus;

	limit = LLONG_MAX;
	tmp = LLONG_MAX;
	minus = 0;
	*result = 1;
	while ((limit /= 10))
		*result *= 10;
	minus = (src[*index] == '-');
	limit = !minus ? *result / 10 : -(*result / 10);
	*result = 0;
	*index = (src[*index] == '+' || src[*index] == '-') ? *index + 1 : *index;
	while (src[*index] == '0')
		*index = *index + 1;
	if (!minus)
		while ('0' <= src[*index] && src[*index] <= '9' && *result < limit)
			*result = *result * 10 + src[(*index)++] - '0';
	else if (minus)
		while ('0' <= src[*index] && src[*index] <= '9' && *result > limit)
			*result = *result * 10 - src[(*index)++] + '0';
	if ('0' <= src[*index] && src[*index] <= '9')
	{
		*result = *result * 10 + (1 - 2 * minus) * (src[(*index)++] - '0');
		if ((!minus && *result < 10) || (minus && *result > -10)
				|| ('0' <= src[*index] && src[*index] <= '9'))
			return (-1);
	}
	return (0);
}
