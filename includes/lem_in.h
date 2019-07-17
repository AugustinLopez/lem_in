/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:40:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/07/17 12:14:26 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STRUCT_H
# define LEM_IN_STRUCT_H

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

# define LEM_END 1
# define LEM_START 2
# define LEM_COMMAND 4

/*
** FIFO:
** - The FIFO approach is well adapted for exploration algorithm.
** - With Edmund Karp, the graph will be explored several time. Each time,
** lots of values will be modified and it would be inefficient to kept track
** of all those modification.
** - We keep track of the number of exploration with 'n'. 'max' is higher than
** the maximum possible value of 'n'.
** - Path and node that are being explored are given the current value of 'n'.
** - Path and node that link to the end are given the value 'max'.
** - Thus we don't have to reinitialize our graph at each iteration: we only
** need to check if a value is lower, higher or equal to 'n'.
*/

typedef struct		s_fifo
{
	t_list			*first;
	t_list			*last;
	size_t			n;
	size_t			max;
}					t_fifo;

/*
** LEM_IN:
** - fileline is the start of the file
** - curline is the line of the file that is being processed.
** - room and links are kept in a RB tree.
*/

typedef struct 		s_lemin
{
	size_t 			nbr_ant;
	size_t			nbr_room;
	size_t			nbr_tube;
	t_list			*fileline;
	t_list			*curline;
	t_rb_node		*start;
	t_rb_node		*end;
	t_rb_node		*tree;
}					t_lemin;

/*
** PARSER FUNCTION
*/

int					parser_ant(t_lemin *lem);
int					parser_room(t_lemin *lem);
int					parser_tube(t_lemin *lem);
int					parser(t_lemin *lem);
int					is_tube(t_lemin *lem, char *line);
int					is_comment(char *line);
int					save_line(t_lemin *lem, char *line);
int					lem_feed_tree(t_lemin *lem, t_tree_data *room, uint8_t command);

/*
** ALGORITHM FUNCTION
*/

t_rb_node			*get_node(t_list *ptr);
int				edmundkarp(t_lemin *lem);

#endif
