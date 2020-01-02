/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 01:43:23 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/11/15 23:54:49 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		clean_it(t_container *container)
{
	int		jumper;
	t_hash	*hash_temp;

	jumper = -1;
	while (++jumper < H_SIZE)
	{
		if (container->hash_table[jumper])
		{
			hash_temp = container->hash_table[jumper];
			while (hash_temp)
			{
				hash_temp->room->vis = 0;
				hash_temp = hash_temp->next;
			}
		}
	}
	return (1);
}

int		clean_blocked_rooms(t_container *container)
{
	t_room	*temp;
	t_link	*neighbors;
	t_room	*neighbor;
	t_queue	*queue;

	queue = get_queue(container);
	while (queue->last)
	{
		temp = queue->first->addr;
		neighbors = temp->neighb_link;
		while (neighbors)
		{
			neighbor = neighbors->link;
			if (neighbor->blocked == 1)
			{
				neighbor->blocked = 0;
				ft_enque(queue, neighbor);
			}
			neighbors = neighbors->next;
		}
		ft_pop(queue);
	}
	ft_free_queue(queue);
	return (1);
}

int		clean_blocked_flow(t_container *container)
{
	t_room	*temp;
	t_link	*neighbors;
	t_room	*neighbor;
	t_queue	*queue;

	queue = get_queue(container);
	while (queue->last)
	{
		temp = queue->first->addr;
		neighbors = temp->neighb_link;
		while (neighbors)
		{
			neighbor = neighbors->link;
			if (neighbor->blocked_flow == 1)
			{
				neighbor->blocked_flow = 0;
				ft_enque(queue, neighbor);
			}
			neighbors = neighbors->next;
		}
		ft_pop(queue);
	}
	ft_free_queue(queue);
	return (1);
}
