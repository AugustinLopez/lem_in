#include <lem_in.h>

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

/*
** READER_TUBE:
** This function come after Reader_room. At this point we did an additional
** reading which is neither a room or a comment: hence the check before the
** read loop.
** The tube are the last information. They come after the room.
** We save input in a list if not a comment. We return malloc failure.
** Model:
** - No whitespace accepted.
*/

int				reader_tube(t_lemin *lem)
{
	int		ret;
	int		i;
	char	*line;

	if (is_tube(lem, (char *)(lem->tmp->pv)) == 0)
		return (-1);
	i = 0;
	while ((ret = ft_gnl(STDIN_FILENO, &line, 1) > 0))
	{
		if (!is_comment(line))
		{
			if (!is_tube(lem, line))
			{
				free(line);
				return (-1);
			}
			i = push_in_file(lem, line);
		}
		free(line);
		if (i == -1)
			return (-1);
	}
	return (0);
}
