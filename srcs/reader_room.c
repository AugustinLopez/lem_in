#include <lem_in.h>

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
