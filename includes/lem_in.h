/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:40:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/06/12 10:08:54 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STRUCT_H
# define LEM_IN_STRUCT_H

# include <libft.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <rb_tree.h>

# define PARSE_COMMENT 1
# define PARSE_COMMAND 2
# define PARSE_ROOM 3
# define PARSE_TUBE 4
# define PARSE_INVALID 5
# define PARSE_FATAL_ERROR 6
# define PARSE_ANT 7

//# define LEM_ANT 1
# define LEM_ROOM 2
# define LEM_END 4
# define LEM_START 8
# define LEM_COMMAND 16

typedef struct 		s_lemin
{
	size_t 			nbr_ant;
	size_t			nbr_room;
	int				flag;
	t_list			*fileline;
	t_list			*tmp;
	size_t			nb_lines;
	size_t			nb_command;
	long			**link;
	void			*roomarray; // once roomlist is finished, we can index them
								// so we don't have to go through the full list
								// each time we want to retrieve an element.
								// We use a spare matrix (easier/faster to parse)
								// If we want bonus, might implement a list
	t_rb_node		*start;
	t_rb_node		*end;
	t_rb_node		*tree;
}					t_lemin;

//char				*lem_strtrim(char const *s);
int					lem_atoll(const char *src, long long *result, size_t *index);
int					reader_ant(t_lemin *lem);
int					reader_room(t_lemin *lem);
int					reader_tube(t_lemin *lem);
int					push_in_file(t_lemin *lem, char *line);
int					is_comment(char *line);
#endif
