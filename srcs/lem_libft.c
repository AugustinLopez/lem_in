/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:45:39 by bcarlier          #+#    #+#             */
/*   Updated: 2019/06/12 10:10:00 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

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

int					lem_atoll(const char *src, long long *result, size_t *index)
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
