/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 15:46:40 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/11/10 16:51:35 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_init(t_container *c)
{
	if (!(c->content = ft_get_file_content(0, BUFF_SIZE)))
		ft_free_exit(c, 0);
	c->ants = NULL;
	c->source = NULL;
	c->sink = NULL;
	if (!(c->hash_table = (t_hash**)malloc(sizeof(t_hash*) * H_SIZE)))
		ft_free_exit(c, 0);
	ft_memset(c->hash_table, 0, H_SIZE * sizeof(t_hash*));
}

t_queue			*get_queue(t_container *container)
{
	t_queue		*queue;
	t_room		*room;

	if (!(queue = ft_new_queue()))
		ft_free_exit(container, 0);
	room = ft_get_value(container, container->source);
	room->vis = 1;
	room->parent = NULL;
	ft_enque(queue, room);
	return (queue);
}

/*
**  check if edge source-sink exist
*/

int				source_sink(t_container *c)
{
	t_room		*cur_room;

	cur_room = ft_get_value(c, c->source);
	return (get_neighbor(c->sink, cur_room->neighb_link) ? 1 : 0);
}

/*
**  make a goup containe only one path source-sink.
*/

t_group			*source_sink_group(t_container *c)
{
	t_path		*path;
	t_node		*node;
	t_group		*group;

	path = make_path(c);
	node = make_node(c, c->sink);
	enque_node(path, node);
	node = make_node(c, c->source);
	enque_node(path, node);
	group = make_group(c);
	add_path_group(group, path);
	group->next = NULL;
	return (group);
}

/*
**	find neighbor in the neighbors list
*/

t_link			*get_neighbor(char *to_find, t_link *neighbors)
{
	t_link		*neighbor;

	neighbor = neighbors;
	if (neighbor == NULL)
		return (NULL);
	while (neighbor)
	{
		if (ft_strcmp(((t_room *)neighbor->link)->name, to_find) == 0)
			return (neighbor);
		neighbor = neighbor->next;
	}
	return (NULL);
}
