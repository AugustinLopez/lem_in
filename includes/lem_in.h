/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:40:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/02 16:17:55 by bcarlier         ###   ########.fr       */
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
** See lem-in -h
*/

# define F_FLAG "hFAispncelx"
# define F_HELP 1
# define F_NOFILE 2
# define F_NOANT 4
# define F_INFO 8
# define F_SOLVER 16
# define F_PATH 32
# define F_NUMBER 64
# define F_COLOR 128
# define F_EXPLO 256
# define F_LIMIT 512
# define F_COORDINATE 1024

/*
** flags for '##start' and '##end' command.
*/

# define LEM_END 1
# define LEM_START 2
# define LEM_COMMAND 4

/*
** flags for algorithm
*/

# define CASE_EXPLO 1
# define CASE_END 2
# define CASE_MINUS 4

typedef struct		s_road
{
	t_list			*km;
	size_t			length;
	size_t			ant_to_launch;
	struct s_road	*next;
}					t_road;

typedef struct		s_roadlist
{
	t_road			*first;
	size_t			longest;
	size_t			exploration;
	size_t			nbr_road;
	size_t			step;
}					t_roadlist;

typedef struct		s_lnode
{
	t_rb_node		*node;
	size_t			depth;
	struct s_lnode	*next;
	struct s_lnode	*prev;
}					t_lnode;

typedef struct		s_fifo
{
	size_t			index;
	t_list			*first;
	t_list			*last;
}					t_fifo;

typedef struct		s_lemin
{
	size_t			nbr_room;
	size_t			nbr_tube;
	size_t			nbr_ant;
	size_t			exploration;
	t_roadlist		*roadlist;
	t_rb_node		*start;
	t_rb_node		*tree;
	t_rb_node		*end;
	t_rb_node		*coordinate;
	uint32_t		flags;
}					t_lemin;

/*
** PARSER FUNCTION
*/

int					parser_ant(t_lemin *lem);
int					parser_room(t_lemin *lem, char **line);
int					parser_tube(t_lemin *lem, char **line);
int					parser(t_lemin *lem);
int					is_comment(char *line);
int					lem_feed_tree(t_lemin *lem, t_tree_data *room,
						uint8_t command);
int					lem_feed_xy(t_lemin *lem, t_tree_data *room,
						uint8_t command);
/*
** ALGO FIRST STEP
*/

int					dijkstra(t_lemin *lem);
void				print_stack(t_lemin *lem, t_lnode *stack);
int					conclude_exploration(t_lemin *lem, t_lnode *stack);

/*
** ALGO ALL OTHER STEPS
*/

int					benjaug(t_lemin *lem);
int					case_basic(t_lemin *lem, t_lnode *stack, t_link **link);
int					case_upstream(t_lemin *lem, t_lnode *stack, t_link **link);
int					case_reexplore(t_lemin *lem, t_lnode *stack, t_link **link);
int					try_without_longest_path(t_lemin *lem,
						t_roadlist *roadlist);
int					explore(t_lemin *lem, t_lnode *stack, t_link **link,
						int option);
/*
** ROADLIST
*/

int					create_roadlist(t_lemin *lem);
void				free_roadlist(t_roadlist **roadlist);
int					ft_newroad(t_road **road);
int					ft_kmadd(t_road *road, t_link *km);
void				print_path(t_list *km);
int					step_count(t_lemin *lem, t_roadlist *roadlist);
int					sort_roadlist(t_roadlist *roadlist);

/*
** OTHERS
*/

void				pathsolver(t_lemin *lem);
void				printer(t_lemin *lem);
void				ft_lnodadd(t_lnode **lnode, t_lnode *new);
t_lnode				*ft_lnodnew(t_lnode *stack);
t_lnode				*ft_stackinit(t_lemin *lem);
void				ft_stackdel(t_lnode *stack);
void				ft_stackdelfirst(t_lnode **stack);
void				ft_lnkdel(t_rb_node *node);
t_rb_node			*get_origin_node(t_link *link);
t_rb_node			*get_target(t_link *link);
#endif
