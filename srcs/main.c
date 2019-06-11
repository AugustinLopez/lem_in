#include <lem_in.h>

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

int				main(void)
{
	t_lemin	lem;
	int		ret;
	//t_rb_node *tree;

	ft_bzero(&lem, sizeof(lem));
	if ((ret = reader_ant(&lem)) || lem.nbr_ant == 0)
	{
		ft_dprintf(STDERR_FILENO, "Error when setting number of ants\n");
		ft_gnl(-1, 0, 0);
		lem_free_tree(&(lem.tree));
		ft_lstdel(&(lem.fileline), *ft_lstfree);
		return (ret);
	}
	ft_dprintf(STDOUT_FILENO, "Number of ants: %d\n", lem.nbr_ant);
	if ((ret = reader_room(&lem)))
	{
		ft_dprintf(STDERR_FILENO, "Error when setting rooms\n");
		ft_gnl(-1, 0, 0);
		lem_free_tree(&(lem.tree));
		ft_lstdel(&(lem.fileline), *ft_lstfree);
		return (ret);
	}
	if ((ret = reader_tube(&lem)))
	{
		ft_dprintf(STDERR_FILENO, "Error when setting tube\n");
		ft_gnl(-1, 0, 0);
		lem_free_tree(&(lem.tree));
		ft_lstdel(&(lem.fileline), *ft_lstfree);
		return (ret);
	}
	ft_printf("%zu %zu\n", ft_lstsize((lem.end)->link), ft_lstsize((lem.start)->link));
	ft_gnl(-1, 0, 0);
	lem_free_tree(&(lem.tree));
	ft_lstdel(&(lem.fileline), *ft_lstfree);
	return (ret);
}
