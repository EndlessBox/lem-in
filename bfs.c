/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <ybouladh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 16:00:31 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/15 23:45:58 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	back_track(t_container *container)
{
	t_room	*temp;
	t_link	*temp_curr;
	t_link	*temp_nei;

	temp = ft_get_value(container, container->sink);
	while (temp)
	{
		if (ft_strcmp(container->source, temp->name) != 0)
		{
			temp_nei = get_neighbor(((t_room *)temp->parent)->name,
					temp->neighb_link);
			(temp_nei->cost)++;
			temp_curr = get_neighbor(temp->name,
							((t_room *)(temp->parent))->neighb_link);
			(temp_curr->cost)--;
		}
		temp = temp->parent;
	}
}

int		check_sink(t_container *cont, t_link *neighbors, t_room *temp)
{
	t_room	*neighbor;

	neighbor = neighbors->link;
	if (ft_strcmp(neighbor->name, cont->sink) == 0 && neighbors->cost)
	{
		neighbor->parent = temp;
		back_track(cont);
		return (1);
	}
	return (0);
}

int		traverse(int go_block, t_link *neighbors, t_room *temp, int *go_out)
{
	t_room	*neighbor;

	neighbor = neighbors->link;
	if (go_block == 1 && neighbor->vis == 0 &&
		neighbors->cost > 0 && neighbor->blocked_flow == 1)
	{
		(*go_out) = 1;
		neighbor->parent = temp;
		neighbor->vis = 1;
		return (1);
	}
	else if (go_block == 0 && neighbor->vis == 0 && neighbors->cost > 0)
	{
		neighbor->parent = temp;
		neighbor->vis = 1;
		return (1);
	}
	return (0);
}

int		search_graph(t_queue *queue, t_container *container)
{
	t_room	*cur;
	t_link	*neighbors;
	int		keep_blocking;
	int		found_blocked;

	while (queue->last)
	{
		cur = queue->first->addr;
		neighbors = cur->neighb_link;
		keep_blocking = 0;
		found_blocked = 0;
		if (cur->blocked_flow == 1 && ((t_room*)cur->parent)->blocked_flow == 0)
			keep_blocking = 1;
		while (neighbors)
		{
			if (check_sink(container, neighbors, cur) == 1)
				return (1);
			if (traverse(keep_blocking, neighbors, cur, &found_blocked))
				ft_enque(queue, neighbors->link);
			neighbors = neighbors->next;
		}
		cur->vis = ((keep_blocking == 1 && found_blocked == 0) ? 0 : cur->vis);
		ft_pop(queue);
	}
	return (0);
}
