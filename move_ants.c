/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 23:05:29 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/10/25 03:01:37 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_arrived(t_container *c)
{
	int		jumper;

	jumper = -1;
	while (++jumper < c->nbr_ants)
		if (ft_strcmp((c->ants + jumper)->current->name, c->sink) != 0)
			return (1);
	return (0);
}

void		send_it2(t_container *c, int *pos, t_ant *ants, t_room *current)
{
	t_room	*next;

	next = ft_get_value(c, (ants + *pos)->current->next->name);
	ft_printf("L%d-%s", (ants + *pos)->name, next->name);
	if (ft_strcmp(current->name, c->source) != 0)
		current->full = 0;
	if (ft_strcmp(next->name, c->sink) != 0)
		next->full = 1;
	(ants + *pos)->current = (ants + *pos)->current->next;
	ft_putchar(' ');
}

void		send_it(t_container *c)
{
	t_ant	*ants;
	int		ant_number;
	t_room	*current;
	t_room	*next;
	int		pos;

	ants = c->ants;
	ant_number = c->nbr_ants;
	while (check_arrived(c))
	{
		pos = -1;
		while (++pos < ant_number)
			if (ft_strcmp((ants + pos)->current->name, c->sink) != 0)
			{
				current = ft_get_value(c, (ants + pos)->current->name);
				next = ft_get_value(c, (ants + pos)->current->next->name);
				if (next->full == 0)
					send_it2(c, &pos, ants, current);
			}
		ft_putchar('\n');
	}
}
