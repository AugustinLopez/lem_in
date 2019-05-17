#include <lem_in.h>

int	is_not_atoi(t_lemin *lem, char *line)
{
	size_t	i;
	size_t	ret;

	i = 0;
	ret = ft_strlen(line);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (lem_atozu(line, &(lem->nbr_ant), &i))
		return (PARSE_FATAL_ERROR);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i] != '\n')
		return (PARSE_FATAL_ERROR);
	return (0);
}

//OK

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

//OK

int	is_ant(t_lemin *lem, char **line)
{
	lem->flag &= ~LEM_ANT;
	lem->flag |= LEM_ROOM;
	if (is_not_atoi(lem, *line))
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
	if (line[i] == '#' && (!ft_strlcmp(line + i + 1, "#end\n")))
	{
		if (lem->flag & LEM_END)
			return (PARSE_FATAL_ERROR);
		lem->flag |= LEM_END;
		lem->flag ^= LEM_COMMAND;
		return (PARSE_COMMAND);
	}
	if (line[i] == '#' && (!ft_strlcmp(line + i + 1, "#start\n")))
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
	//verifier room avec nom comportant '-'
	while (line[name[1]] && !ft_strchr(" \t-" ,line[name[1]]))
		name[1]++;
	i = name[1];
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	if (lem_atozu(line, &x, &i) || lem_atozu(line, &y, &i))
		return (0);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i] != '\n')
		return (0);
	lem->flag &= ~LEM_COMMAND;
	return (PARSE_ROOM);
}

int	is_tube(t_lemin *lem, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && line[i] != '-' && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i++] != '-')
		return (PARSE_INVALID);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (PARSE_INVALID);
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

int				push_in_file(t_lemin *lem, int type, char *line, t_list **tmp)
{
	if (type != PARSE_COMMENT)
	{
		if (!lem->file)
		{
			if(!(lem->file = ft_lstnew(0, 0)))
				return (-1);
			*tmp = lem->file;
			if(!(lem->file->pv = ft_strdup(line)))
				return (-1);
		}
		else
		{
			if(!((*tmp)->next = ft_lstnew(0, 0)))
				return (-1);
			*tmp = (*tmp)->next;
			if(!((*tmp)->pv = ft_strdup(line)))
				return (-1);
		}
	}
	return (0);
}

int				parser_master(t_lemin *lem)
{
	ssize_t	ret;
	int		type;
	char	*line;
	int		i;
	int		count;
	int		a;
	t_list	*file;

	a = 0;
	i = 0;
	ret = 0;
	count = 0;
	lem->flag |= LEM_ANT;
	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		type = parser_lines(lem, &line);
		if (lem->flag & LEM_COMMAND && lem->flag & LEM_START && !(a & 1))
		{
			ft_printf("START-");
			a |= 1;
		}
		if (lem->flag & LEM_COMMAND && lem->flag & LEM_END && !(a & 2))
		{
			ft_printf("END-");
			a |= 2;
		}
		if (type == PARSE_COMMAND)
			count++;
		if (count > 2 || (count < 2 && type == PARSE_TUBE))
			type = PARSE_FATAL_ERROR;
		else if (type == PARSE_COMMAND && !(lem->flag & LEM_COMMAND))
			type = PARSE_FATAL_ERROR;
		else if (type != PARSE_COMMAND && type != PARSE_COMMENT && lem->flag & LEM_COMMAND)
			type = PARSE_FATAL_ERROR;
		printer(type, ++i);
		if (type == PARSE_FATAL_ERROR || type == PARSE_INVALID)
			break ;
		if ((push_in_file(lem, type, line, &file)))
		{
			ft_memdel((void**)&line);
			break ;
		}
		if (line)
			ft_memdel((void**)&line);
		else
			break ;
	}
	if (line)
		ft_memdel((void**)&line);
	ft_gnl(-1, 0, 0);
	file = lem->file;
	if (type != PARSE_FATAL_ERROR)
	{
		while (file)
		{
			ft_printf("%s", (char*)(file->pv));
			file = file->next;
		}
	}
	ft_lstdel(&(lem->file), *ft_lstfree);
	//lem_listdel(&(lem->roomlist));
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
