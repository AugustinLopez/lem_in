/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:45:39 by bcarlier          #+#    #+#             */
/*   Updated: 2019/05/16 17:03:20 by bcarlier         ###   ########.fr       */
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
	while ((src[*index] >= 9 && src[*index] <= 13) || src[*index] == ' ')
		*index = *index + 1;
	*result = 0;
	if (src[*index] == '+')
		*index = *index + 1;
	while ('0' <= src[*index] && src[*index] <= '9' && *result < limit)
		*result = *result * 10 + src[(*index)++] - '0';
	if ('0' <= src[*index] && src[*index] <= '9')
	{
		*result = *result * 10 + src[(*index)++] - '0';
		if (*result < 10)
			return (-1);
	}
	return (0);
}
