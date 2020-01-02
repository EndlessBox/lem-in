/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 21:55:13 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/10/24 23:34:23 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue			*ft_new_queue(void)
{
	t_queue		*new;

	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	new->first = NULL;
	new->last = NULL;
	return (new);
}

void			ft_enque(t_queue *q, void *data)
{
	if (q->first)
	{
		q->last->next = ft_new_t_addr(data);
		q->last = q->last->next;
	}
	else
	{
		q->first = ft_new_t_addr(data);
		q->last = q->first;
	}
}

void			ft_pop(t_queue *q)
{
	t_addr		*temp;

	if (!q->first)
		return ;
	temp = q->first;
	q->first = q->first->next;
	temp->next = NULL;
	if (temp == q->last)
		q->last = NULL;
	ft_free_t_addr(temp);
}

int				ft_free_queue(t_queue *q)
{
	if (!q)
		return (1);
	if (q->last)
		ft_free_t_addr(q->first);
	free(q);
	q = NULL;
	return (1);
}
