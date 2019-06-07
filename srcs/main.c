#include <lem_in.h>

/*

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

int				push_in_file(t_lemin *lem, char *line, t_list **tmp)
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
	file = lem->file;
	if (type != PARSE_FATAL_ERROR)
	{
		while (file)
		{
			ft_printf("%s", (char*)(file->pv));
			file = file->next;
		}
	}
	return (0);
}

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
*/
//OK

//OK

/*int	is_ant(t_lemin *lem, char **line)
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
*/

int	is_tube(t_lemin *lem, char *line)
{
	size_t	i;
	size_t	name_1[2];
	size_t	name_2[2];

	(void)lem;
	i = lem_whitespace(line, 0);
	name_1[0] = i;
	while (line[i] && line[i] != '-' && line[i] != ' ')
		i++;
	name_1[1] = i;
	if (line[i++] != '-')
		return (0);
	if (!line[i] || line[i] == '\n')
		return (0);
	name_2[0] = i;
	while (line[i] && line[i] != '-' && line[i] != ' ' && line[i] != '\n')
		i++;
	name_2[1] = i;
	i = lem_endspace(line, i);
	if (line[i] && line[i] != '\n')
		return (0);
	//link_matrice(lem, name_1, name_2);
	ft_printf("%.*s - %.*s\n", name_1[1] - name_1[0], line + name_1[0], name_2[1] - name_2[0], line + name_2[0]);
	return (1);
}


int	is_comment(char *line)
{
	size_t	i;

	i = lem_whitespace(line, 0);
	if (line[i] == '#' && (line[i + 1] != '#'))
		return (1);
	if ((line[i] == '#' && line[i + 1] == '#')
			&& (!ft_strcmp(line + i + 2, "start\n")
				&& !ft_strcmp(line + i + 2, "end\n")))
			return (1);
	return (0);
}

int				push_in_file(t_lemin *lem, char *line)
{
	if (!lem->fileline)
	{
		if(!(lem->fileline = ft_lstnew(0, 0)))
			return (-1);
		lem->tmp = lem->fileline;
		if(!(lem->fileline->pv = ft_strdup(line)))
		return (-1);
	}
	else
	{
		if(!(lem->tmp->next = ft_lstnew(0, 0)))
			return (-1);
		lem->tmp = lem->tmp->next;
		if(!(lem->tmp->pv = ft_strdup(line)))
			return (-1);
	}
	return (0);
}

int	is_command(char *line, int *command)
{
	size_t	i;

	i = lem_whitespace(line, 0);
	if (line[i] == '#' && (!ft_strlcmp(line + i + 1, "#end\n")))
	{
		if (*command & (1 | 8))
			return (-1);
		*command |= 1 | 8;
		return (1);
	}
	if (line[i] == '#' && (!ft_strlcmp(line + i + 1, "#start\n")))
	{
		if (*command & (2 | 8))
			return (-1);
		*command |= 2 | 8;
		return (1);
	}
	return (0);
}

int	is_room(t_lemin *lem, char *line, int command)
{
	size_t	name[2];
	size_t	i;
	long long	xy[2];

	(void)lem;
	(void)command;
	name[0] = lem_whitespace(line, 0);
	name[1] = name[0];
	while (line[name[1]] && !ft_strchr(" -" ,line[name[1]]))
		name[1]++;
	i = lem_whitespace(line, name[1]);
	if (!line[i] || line[i] == '\n' || lem_atoll(line, &xy[0], &i))
		return (0);
	i = lem_whitespace(line, i);
	if (!line[i] || line[i] == '\n' || lem_atoll(line, &xy[1], &i))
		return (0);
	i = lem_endspace(line, i);
	if (line[i] && line[i] != '\n')
		return (0);
	//binary_tree(lem, line, name, xy)
	ft_printf("%.*s - %lld - %lld\n", name[1] - name[0], line + name[0], xy[0], xy[1]);
	return (1);
}

int				reader_room(t_lemin *lem)
{
	int		ret;
	char	*line;
	int		command;

	command = 0;
	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		if (is_comment(line) == 0)
		{
			if ((is_command(line, &command)))
			{
				if (command == -1)
				{
					free(line);
					return (-1);
				}
			}
			else if (is_room(lem, line, command))
				command &= ~8;
			else
			{
				if (command != 3)
				{
					free(line);
					return (-1);
				}
				if (push_in_file(lem, line) == -1)
					return (-2);
				free(line);
				return (0);
			}
			if (push_in_file(lem, line) == -1)
				return (-2);
		}
		free(line);
	}
	return (-1);
}

int	is_not_atoi(t_lemin *lem, char *line)
{
	size_t	i;

	i = lem_whitespace(line, 0);
	if (lem_atozu(line, &(lem->nbr_ant), &i) == -1)
		return (-1);
	i = lem_whitespace(line, i);
	if (line[i] && line[i] != '\n')
		return (-1);
	return (0);
}

int				reader_ant(t_lemin *lem)
{
	int		ret;
	char	*line;
	int		i;

	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		i = lem_whitespace(line, 0);
		if (is_comment(line + i) == 0)
		{
			if (is_not_atoi(lem, line + i) == 1)
			{
				free(line);
				return (-1);
			}
			if (push_in_file(lem, line) == -1)
				return (-2);
			free(line);
			return (0);
		}
		free(line);
	}
	return (-1);
}

int				reader_tube(t_lemin *lem)
{
	int		ret;
	char	*line;
	int		i;

	i = lem_whitespace((char *)lem->tmp->pv, 0);
	if (is_tube(lem, (char *)(lem->tmp->pv) + i) == 0)
		return (-1);
	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		i = lem_whitespace(line, 0);
		if (is_comment(line + i) == 0)
		{
			if (is_tube(lem, line + i) == 0)
			{
				free(line);
				return (-1);
			}
			if (push_in_file(lem, line) == -1)
				return (-2);
		}
		free(line);
	}
	return (0);
}

int				main(void)
{
	t_lemin	lem;
	int		ret;

	ft_bzero(&lem, sizeof(lem));
	if ((ret = reader_ant(&lem)) || lem.nbr_ant == 0)
	{
		ft_dprintf(STDERR_FILENO, "Error when setting number of ants\n");
		ft_gnl(-1, 0, 0);
		if (lem.fileline)
			ft_lstdel(&(lem.fileline), *ft_lstfree);
		return (ret);
	}
	ft_dprintf(STDOUT_FILENO, "Number of ants: %d\n", lem.nbr_ant);
	if ((ret = reader_room(&lem)))
	{
		ft_dprintf(STDERR_FILENO, "Error when setting rooms\n");
		ft_gnl(-1, 0, 0);
		ft_lstdel(&(lem.fileline), *ft_lstfree);
		return (ret);
	}
	if ((ret = reader_tube(&lem)))
	{
		ft_dprintf(STDERR_FILENO, "Error when setting tube\n");
		ft_gnl(-1, 0, 0);
		ft_lstdel(&(lem.fileline), *ft_lstfree);
		return (ret);
	}
	ft_gnl(-1, 0, 0);
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	return (ret);
}
