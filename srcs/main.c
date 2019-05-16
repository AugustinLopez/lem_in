/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:35:43 by bcarlier          #+#    #+#             */
/*   Updated: 2019/05/16 17:34:58 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int	is_not_atoi(t_lemin *lem, char **line)
{
	size_t	index;
	char	*tmp;
	size_t	ret;

	ret = ft_strlen(*line);
	if ((*line)[ret - 1] != '\n')
		return (-1);
	(*line)[ret - 1] = '\0';
	if(!(tmp = lem_strtrim(*line)))
		return (-1);
	free(*line);
	*line = tmp;
	if ((*line)[0] != '+' && !(ft_isdigit((*line)[0])))
		return (-1);
	index = 0;
	if (lem_atozu(*line, &(lem->nbr_ant), &index) || (*line)[index])
		return (-1);
	return (0);
}

int	is_comment(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '#' && (line[i + 1] != '#'))
		return (PARSE_COMMENT);
	return (0);
}

int	is_ant(t_lemin *lem, char **line)
{
	lem->flag &= ~LEM_ANT;
	lem->flag |= LEM_ROOM;
	if (is_not_atoi(lem, line))
	{
		ft_memdel((void **)line);
		return (PARSE_FATAL_ERROR);
	}
	return (PARSE_ANT);
}

int	is_command(t_lemin *lem, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '#' && (ft_strlcmp(line + i + 1, "#end\n")))
	{
		if (lem->flag & LEM_END)
			return (PARSE_FATAL_ERROR);
		lem->flag |= LEM_END;
		lem->flag ^= LEM_COMMAND;
		return (PARSE_COMMAND);
	}
	if (line[i] == '#' && (ft_strlcmp(line + i + 1, "#start\n")))
	{
		if (lem->flag & LEM_START)
			return (PARSE_FATAL_ERROR);
		lem->flag |= LEM_START;
		lem->flag ^= LEM_COMMAND;
		return (PARSE_COMMAND);
	}
	if (line[i] == '#' && line[i + 1] == '#')
		return (PARSE_COMMENT);
	return (0);
}

int	is_room(t_lemin *lem, char *line)
{
	size_t	name[2];
	size_t	i;
	size_t	x;
	size_t	y;

	name[0] = 0;
	while (line[name[0]] && (line[name[0]] == ' ' || line[name[0]] == '\t'))
		name[0]++;
	name[1] = name[0];
	while (line[name[1]] && line[name[1]] != ' ' && line[name[1]] != '\t')
		name[1]++;
	i = name[1];
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (0);
	if (lem_atozu(line, &x, &i))
		return (PARSE_INVALID);
	if (lem_atozu(line, &y, &i))
		return (PARSE_INVALID);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i] != '\n')
		return (PARSE_INVALID);
	lem->flag &= ~LEM_COMMAND;
	return (PARSE_ROOM);
}

int	is_tube(t_lemin *lem, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && line[i] != '-')
		i++;
	i++;
	while (line[i] && line[i] != '-' && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i] != '\n')
		return (PARSE_INVALID);
	lem->flag &= ~LEM_ROOM;
	return (PARSE_TUBE);
}

int				parser_lines(t_lemin *lem, char **line)
{
	int	ret;

	if ((ret = is_comment(*line)))
		return (ret);
	else if (lem->flag & LEM_ANT && (ret = is_ant(lem, line)))
		return (ret);
	else if ((ret = is_command(lem, *line)))
		return (ret);
	else if (lem->flag & LEM_ROOM && (ret = is_room(lem, *line)))
		return (ret);
	return (is_tube(lem, *line));
}

void			printer(int type, int i)
{
		ft_putnbr(i);
		if (type == PARSE_FATAL_ERROR)
			ft_putendl(". ERROR");
		else if (type == PARSE_INVALID)
			ft_printf(". INVALID\n");
		else if (type == PARSE_COMMENT)
			ft_printf(". COMMENT\n");
		else if (type == PARSE_ANT)
			ft_printf(". ANTS NB\n");
		else if (type == PARSE_COMMAND)
			ft_printf(". COMMAND\n");
		else if (type == PARSE_ROOM)
			ft_printf(". ROOM\n");
		else if (type == PARSE_TUBE)
			ft_printf(". TUBE\n");
}

int				parser_master(t_lemin *lem)
{
	ssize_t	ret;
	int		type;
	char	*line;
	int		i;
	int		count;

	i = 0;
	ret = 0;
	count = 0;
	lem->flag |= LEM_ANT;
	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		type = parser_lines(lem, &line);
		if (type == PARSE_COMMAND)
			count++;
		if (count > 2)
			type = PARSE_FATAL_ERROR;
		else if (type == PARSE_COMMAND && !(lem->flag & LEM_COMMAND))
			type = PARSE_FATAL_ERROR;
		else if (type != PARSE_COMMAND && type != PARSE_COMMENT && lem->flag & LEM_COMMAND)
			type = PARSE_FATAL_ERROR;
		
		printer(type, ++i);
		line ? free(line) : (void)0;
		if (!line || type <= 0)
			break ;
	}
	ft_gnl(-1, 0, 0);
	return (0);
}

int				main(void)
{
	t_lemin	lem;
	int		ret;

	ft_bzero(&lem, sizeof(lem));
	ret = parser_master(&lem);
	return (ret);
}
