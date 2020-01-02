/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_group.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 02:06:08 by ybouladh          #+#    #+#             */
/*   Updated: 2019/10/24 23:13:04 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_group		*make_group(t_container *c)
{
	t_group	*group;

	if ((group = (t_group*)malloc(sizeof(t_group))))
	{
		group->paths = NULL;
		group->flow = 0;
		group->score = 0;
		group->total_dep = 0;
		group->last = NULL;
		group->last_g = NULL;
		group->next = NULL;
		return (group);
	}
	else
		ft_free_exit(c, 0);
	return (NULL);
}

int			enque_group(t_group **grp_container, t_group *group)
{
	group->next = NULL;
	if (*grp_container == NULL)
	{
		*grp_container = group;
		(*grp_container)->last_g = group;
		return (1);
	}
	(*grp_container)->last_g->next = group;
	(*grp_container)->last_g = (*grp_container)->last_g->next;
	return (1);
}

void		add_path_group(t_group *group, t_path *path)
{
	path->next = NULL;
	if (group->paths == NULL)
	{
		group->paths = path;
		group->last = group->paths;
	}
	else
	{
		group->last->next = path;
		group->last = path;
	}
}
