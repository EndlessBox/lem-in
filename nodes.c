/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouladh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:22:12 by ybouladh          #+#    #+#             */
/*   Updated: 2019/10/24 23:14:02 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node		*make_node(t_container *c, char *str)
{
	t_node	*node;

	if ((node = (t_node*)malloc(sizeof(t_node))))
	{
		node->next = NULL;
		node->name = str;
		return (node);
	}
	else
		ft_free_exit(c, 0);
	return (NULL);
}

int			enque_node(t_path *path, t_node *node)
{
	if (path->head == NULL)
	{
		path->head = node;
		return (1);
	}
	node->next = path->head;
	path->head = node;
	return (1);
}

void		clean_cost(t_container *container)
{
	int		jumper;
	t_hash	*hash_temp;
	t_link	*temp;

	jumper = -1;
	while (++jumper < H_SIZE)
	{
		if (container->hash_table[jumper])
		{
			hash_temp = container->hash_table[jumper];
			while (hash_temp)
			{
				temp = hash_temp->room->neighb_link;
				while (temp)
				{
					temp->cost = 1;
					temp = temp->next;
				}
				hash_temp = hash_temp->next;
			}
		}
	}
}
