/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ant.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 10:26:54 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/01 15:51:33 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

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

int					parser_ant(t_lemin *lem)
{
	int		ret;
	char	*line;

	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		if (is_ant(lem, line))
		{
			if (!(lem->flags & F_NOFILE))
				ft_printf("%s", line);
			free(line);
			return (0);
		}
		else if (is_comment(line))
		{
			if (!(lem->flags & F_NOFILE))
				ft_printf("%s", line);
			free(line);
		}
		else
		{
			free(line);
			break ;
		}
	}
	return (-1);
}
