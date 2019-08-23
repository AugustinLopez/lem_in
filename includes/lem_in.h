/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:40:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/08/23 14:12:05 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
** stdlib for malloc/free
** unistd for STDIN and STDERR
** limits for LLONG_MAX
** stdint for uintX_t
** stddef for size_t
*/

# include "libft.h"
# include "rb_tree.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>
# include <stddef.h>

/*
** flags for '##start' and '##end' command.
*/

# define DEBUG 1
# define LEM_END 1
# define LEM_START 2
# define LEM_COMMAND 4

typedef struct		s_road
{
	t_link			*km;
	size_t			length;
	struct s_road	*next;
}					t_road;

typedef struct		s_roadlist
{
	t_road			*first;
	t_road			*current;
	size_t			longest;
	size_t			amount;
	size_t			step;
}					t_roadlist;

typedef struct		s_lnode
{
	t_rb_node		*node;
	size_t			depth;
	struct s_lnode	*next;
	struct s_lnode	*prev;
}					t_lnode;

/*
** LEM_IN:
** - fileline is the start of the file
** - curline is the line of the file that is being processed.
** - room and links are kept in a RB tree.
*/

typedef struct		s_lemin
{
	size_t			nbr_ant;
	size_t			nbr_room;
	size_t			nbr_tube;
	t_rb_node		*start;
	t_rb_node		*end;
	t_rb_node		*tree;
	size_t			max_road_num;
	t_roadlist		*roadlist;
}					t_lemin;

/*
** PARSER FUNCTION
*/

int					parser_ant(t_lemin *lem);
int					parser_room(t_lemin *lem, char **line);
int					parser_tube(t_lemin *lem, char **line);
int					parser(t_lemin *lem);
int					is_tube(t_lemin *lem, char *line);
int					is_comment(char *line);
int					save_line(t_lemin *lem, char *line);
int					lem_feed_tree(t_lemin *lem, t_tree_data *room,
						uint8_t command);




int	benjaug(t_lemin *lem);
t_rb_node *get_origin(t_link *link);
t_rb_node *get_target(t_link *link);

void					ft_nodadd(t_lnode **lnode, t_lnode *new);
//size_t				printer(t_lemin *lem, int ac);

/*
** ALGORITHM FUNCTION
*/
/*
void				lnkoflnk(void *pv, size_t zu);
*t_rb_node			*get_node(t_link *ptr);
int					edmundkarp(t_lemin *lem);
t_link				*init_pathlink(t_lemin *lem, t_solver *sol, t_fifo *fifo,
						t_link **memory);
int					init_edmundkarp(t_lemin *lem, t_fifo *fifo, t_solver *cur);
int					pathfinder(t_lemin *lem, t_fifo *fifo);
void				pathsolver(t_lemin *lem, t_fifo *fifo);
t_link				*get_reverse_path(t_rb_node *node, t_link *path);
*/
/*
** UTILITIES
*/
/*
size_t				step_count(size_t ant, t_solver *sol);
t_link				*get_reverse_path(t_rb_node *node, t_link *path);
int					free_fifo(t_fifo *fifo, int ret);
void				print_path(t_lemin *lem);

void	print_new_explo(int c, t_solver *new, t_solver *old, t_lemin *lem);
void	print_explo(char c, t_link *rev, t_link *path, t_rb_node *node);
void	print_stack(t_fifo *fifo);
*/

#endif
