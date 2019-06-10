/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:45:39 by bcarlier          #+#    #+#             */
/*   Updated: 2019/06/10 11:08:54 by aulopez          ###   ########.fr       */
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
