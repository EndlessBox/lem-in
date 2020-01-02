/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:58:14 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/11/15 23:54:15 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				mini_track(t_container *c, t_path *path)
{
	t_room		*temp;
	t_node		*temp_node;
	t_link		*p;
	int			depth;

	temp = ft_get_value(c, c->sink);
	depth = 0;
	while (temp)
	{
		depth++;
		temp_node = make_node(c, temp->name);
		enque_node(path, temp_node);
		temp->blocked = 1;
		if (ft_strcmp(c->source, temp->name) != 0)
		{
			p = get_neighbor(temp->name, ((t_room*)temp->parent)->neighb_link);
			temp->blocked = 1;
		}
		if (ft_strcmp(c->source, temp->name) && ft_strcmp(c->sink, temp->name))
			temp->blocked_flow = 1;
		temp = temp->parent;
	}
	return (depth - 1);
}

int				route_found(t_container *c, t_room *neighbor, t_group *group,
				t_room *cur_room)
{
	t_path		*path;

	neighbor->parent = cur_room;
	path = make_path(c);
	path->depth = mini_track(c, path);
	path->regulator = path->depth;
	if (check_score(c->nbr_ants, group, path))
	{
		group->flow++;
		group->score = update_score(c->nbr_ants, group, path);
		group->total_dep += path->depth;
		add_path_group(group, path);
	}
	else
		free_paths(path);
	clean_it(c);
	return (1);
}

/*
** get_routes follow all path with 0 cost, from the start to the sink.
** making a path and then add it to the group if this path will make the
** score lower.
*/

int				get_routes(t_queue *queue, t_container *c, t_group *group)
{
	t_room		*cur;
	t_link		*list;
	t_room		*nxt;

	while (queue->last)
	{
		cur = queue->first->addr;
		list = cur->neighb_link;
		while (list)
		{
			nxt = list->link;
			if (!ft_strcmp(nxt->name, c->sink) && !list->cost)
				return (route_found(c, nxt, group, cur));
			if (!nxt->vis && !nxt->blocked && !list->cost)
			{
				nxt->vis = 1;
				nxt->parent = cur;
				ft_enque(queue, nxt);
			}
			list = list->next;
		}
		ft_pop(queue);
	}
	clean_it(c);
	return (0);
}

t_group			*find_paths(t_container *container, t_queue **queue)
{
	t_queue		*new;
	t_group		*temp;
	t_group		*group;

	group = NULL;
	while (search_graph(((*queue) = get_queue(container)), container))
	{
		clean_it(container);
		clean_blocked_flow(container);
		temp = make_group(container);
		new = get_queue(container);
		while (get_routes(new, container, temp) && ft_free_queue(new)
				&& (new = get_queue(container)))
			;
		clean_blocked_rooms(container);
		ft_free_queue(new);
		enque_group(&group, temp);
		ft_free_queue(*queue);
	}
	temp = low_score(group);
	free_groups(group, temp);
	if (temp != NULL)
		temp->next = NULL;
	return (temp);
}

int				main(void)
{
	t_container c;
	int			line;
	t_group		*group;
	t_queue		*queue;

	ft_init(&c);
	line = ft_read_ants_nbr(&c);
	line = ft_read_rooms(&c, line);
	if (!c.source || !c.sink)
		ft_free_exit(&c, 0);
	get_relations(&c, line);
	group = (source_sink(&c) ? source_sink_group(&c) : find_paths(&c, &queue));
	if (!group)
		ft_free_exit(&c, 0);
	ft_free_queue(queue);
	c.ants = new_ants(c.nbr_ants);
	calcul_spread_ants(&c, group);
	ft_putendl(c.content);
	send_it(&c);
	free_groups(group, NULL);
	free(c.ants);
	ft_free_exit(&c, 1);
	return (0);
}
