/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:23:18 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/10 16:51:07 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path			*make_path(t_container *c)
{
	t_path		*path;

	if ((path = (t_path*)malloc(sizeof(t_path))))
	{
		path->head = NULL;
		path->depth = 0;
		path->regulator = 0;
		path->allowed_ants = 0;
		path->next = NULL;
		return (path);
	}
	else
		ft_free_exit(c, 0);
	return (NULL);
}

void			free_nodes(t_node *node)
{
	t_node	*temp;

	if (!node)
		return ;
	while (node)
	{
		temp = node;
		node = node->next;
		free(temp);
	}
}

void			free_paths(t_path *path)
{
	t_path	*temp;

	if (!path)
		return ;
	while (path)
	{
		temp = path;
		path = path->next;
		free_nodes(temp->head);
		free(temp);
	}
}

void			free_groups(t_group *group, t_group *dont)
{
	t_group	*temp;

	if (!group)
		return ;
	while (group)
	{
		if (!dont || group != dont)
		{
			temp = group;
			group = group->next;
			free_paths(temp->paths);
			free(temp);
		}
		else
			group = group->next;
	}
}
