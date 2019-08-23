/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfromlink.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 13:43:51 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/23 13:45:55 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rb_node	*get_origin(t_link *link)
{
	return ((t_rb_node *)(link->origin));
}

t_rb_node	*get_target(t_link *link)
{
	return ((t_rb_node *)(link->target));
}
