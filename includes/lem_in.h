/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:40:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/05/16 17:26:09 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STRUCT_H
# define LEM_IN_STRUCT_H

# include <libft.h>
# include <stdlib.h>
# include <unistd.h>

# define PARSE_COMMENT 1
# define PARSE_COMMAND 2
# define PARSE_ROOM 3
# define PARSE_TUBE 4
# define PARSE_INVALID 5
# define PARSE_FATAL_ERROR 6
# define PARSE_ANT 7

# define LEM_ANT 1
# define LEM_ROOM 2
# define LEM_END 4
# define LEM_START 8
# define LEM_COMMAND 16

typedef struct		s_room
{
	char 			*name;
	int				index;
	int				x;
	int				y;
	struct s_room	*next;
}					t_room;

typedef struct 		s_lemin
{
	size_t 			nbr_ant;
	int				flag;
	t_list			*file;
	size_t			nb_lines;
	size_t			nb_command;
	t_room			*roomlist;
	long			**link;
	void			*roomarray; // once roomlist is finished, we can index them
								// so we don't have to go through the full list
								// each time we want to retrieve an element.
}					t_lemin;

char				*lem_strtrim(char const *s);
int					lem_atozu(const char *src, size_t *result, size_t *index);

#endif
