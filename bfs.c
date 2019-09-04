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

void     bfs(t_queue *queue, t_container *container)
{
    t_room  *curr;
    t_addr  *nei;
    t_room  *holder;ft_pop(queue);
    t_room  *fiw;


    curr = queue->first->addr;
    if (ft_strcmp(curr->name, container->sink) == 0)
    {
        fiw = curr;
        while (fiw)
        {
            ft_printf("%s - ", fiw->name);
            fiw = fiw->parent;
        }
        ft_putchar('\n');
    }
    nei = curr->neighbors;
    while (nei)
    {
        holder = nei->addr;
        if (!holder->vis)
        {
            holder->parent = curr;
            if (ft_strcmp(holder->name, container->sink) != 0)
                holder->vis = 1;
            ft_enque(queue, holder);
        }
        nei = nei->next;
    }
    ft_pop(queue);
    bfs(queue, container);
}
