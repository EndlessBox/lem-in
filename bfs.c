/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 16:00:31 by ybouladh          #+#    #+#             */
/*   Updated: 2019/08/06 00:23:26 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     bfs(t_queue *queue)
{
	t_room	*temp;
	t_addr	*neighbors;
	t_addr	*curr_neighb;

	while ((t_room*)queue->first->addr)
	{
		temp = (t_room*)(queue->first->addr);
		curr_neighb = temp->neighbors;
		while (curr_neighb)
		{
			if (!(curr_neighb = (t_room*)neighbors->addr)->vis)
			{
				curr_neighb = (ft_push_t_addr(curr_neighb->parents, &temp))->addr;
				curr_neighb->vis = 1;
				ft_enque(queue, curr_neighb);
			}
			neighbors = neighbors->next;
		}
		ft_pop(queue);
		ft_printf("\n");
	}
	return (1);
}
