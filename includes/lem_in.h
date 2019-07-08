/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:40:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/07/08 15:20:54 by aulopez          ###   ########.fr       */
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

# define LEM_ROOM 2
# define LEM_END 4
# define LEM_START 8
# define LEM_COMMAND 16

typedef struct		s_fifo
{
	t_list			*first;
	t_list			*last;
	t_list			*tmp;
	t_list			*result;
	size_t			n;
}					t_fifo;

typedef struct 		s_lemin
{
	size_t 			nbr_ant;
	size_t			nbr_room;
	t_list			*fileline;
	t_list			*curline;
	t_rb_node		*start;
	t_rb_node		*end;
	t_rb_node		*tree;
}					t_lemin;

int					reader_ant(t_lemin *lem);
int					reader_room(t_lemin *lem);
int					reader_tube(t_lemin *lem);
int					reader(t_lemin *lem);
int					save_line(t_lemin *lem, char *line);
int					lem_feed_tree(t_lemin *lem, t_tree_data *room);
int					is_comment(char *line);
t_rb_node			*get_node(t_list *ptr);

#endif
