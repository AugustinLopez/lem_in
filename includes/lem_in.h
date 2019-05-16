/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:40:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/05/16 11:55:28 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STRUCT_H
# define LEM_IN_STRUCT_H

# include <stdlib.h>
# include <unistd.h>

# define LEM_ANTS 1
# define LEM_END 2
# define LEM_START 4
# define LEM_TUBE 8
# define LEM_COMMENT 16
# define LEM_ERROR 32

typedef struct 		s_lemin
{
	size_t 			nb_of_ants;
	int				flag;
	t_list			file;
	size_t			nb_lines;
	size_t			nb_command;
}					t_lemin;

#endif
