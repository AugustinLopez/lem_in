/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:40:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/07/16 14:50:37 by aulopez          ###   ########.fr       */
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
	t_list			*cur;
	t_list			*last;
	t_list			*tmp;
	t_list			*cur_path;
	t_list			*mem_path;
	size_t			n;
	size_t			max;
}					t_fifo;

typedef struct		s_pathprint
{
	t_list			*road;
	size_t			*length;
	size_t			*number;
	size_t			sum_number;
	size_t			path;
	size_t			max_index;
	size_t			index;
	size_t			ant;
}					t_pathprint;

typedef struct 		s_lemin
{
	size_t 			nbr_ant;
	size_t			nbr_room;
	t_list			*fileline;
	t_list			*curline;
	t_list			*dijkstra;
	t_list			*path;
	t_rb_node		*start;
	t_rb_node		*end;
	t_rb_node		*tree;
}					t_lemin;

int					parser_ant(t_lemin *lem);
int					parser_room(t_lemin *lem);
int					parser_tube(t_lemin *lem);
int					parser(t_lemin *lem);
int					is_tube(t_lemin *lem, char *line);

int					save_line(t_lemin *lem, char *line);
int					lem_feed_tree(t_lemin *lem, t_tree_data *room);
int					is_comment(char *line);
t_rb_node			*get_node(t_list *ptr);
int					dijkstra(t_lemin *lem);
void				lstremove(t_list **begin, t_list *one, t_list *two);
t_list				*lstfind(t_list *begin, t_list *elem);
void				lstoflst(void *pv, size_t zu);
int					remove_bad_paths(t_lemin *lem);
void				solve_one_path(t_lemin *lem);
int				solve(t_lemin *lem);
void				debug(t_lemin *lem);
void				print_path(t_lemin *lem);
int				edmundkarp(t_lemin *lem);
#endif
