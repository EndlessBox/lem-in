/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:50:51 by ybouladh          #+#    #+#             */
/*   Updated: 2019/10/24 23:56:13 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		update_score(int ants, t_group *group, t_path *path)
{
	if (group->score == 0)
		return ((path->depth + ants + group->flow - 1) / group->flow);
	return ((group->total_dep +
				path->depth + group->flow - 1 + ants) / group->flow);
}

int		check_score(int ants, t_group *group, t_path *path)
{
	int new_score;
	int old_score;

	if (group->score == 0)
		return (1);
	old_score = (group->total_dep + group->flow + ants - 1) / group->flow;
	new_score = (group->total_dep + path->depth + group->flow + ants) /
		(group->flow + 1);
	if (new_score <= old_score)
		return (1);
	return (0);
}

t_group	*low_score(t_group *group)
{
	t_group *best_grp;
	t_group *temp;

	temp = group;
	best_grp = NULL;
	while (temp)
	{
		if (best_grp == NULL)
			best_grp = temp;
		if (best_grp->score > temp->score)
			best_grp = temp;
		else if (best_grp->score == temp->score)
			if (best_grp->flow <= temp->flow)
				best_grp = temp;
		temp = temp->next;
	}
	return (best_grp);
}

void	assigne_ant_routes(t_container *container, int *jumper, t_node *head)
{
	((container->ants) + (*jumper))->name = (*jumper) + 1;
	((container->ants) + (*jumper))->current = head;
	(*jumper)++;
}

void	calcul_spread_ants(t_container *container, t_group *group)
{
	t_path	*temp;
	int		jumper;
	int		ants;
	int		holder;

	jumper = 0;
	ants = container->nbr_ants;
	while (ants && jumper < container->nbr_ants)
	{
		holder = group->paths->regulator;
		temp = group->paths;
		while (temp)
		{
			if (ants > 0 && temp->regulator <= holder)
			{
				temp->regulator++;
				temp->allowed_ants++;
				ants--;
				assigne_ant_routes(container, &jumper, temp->head);
			}
			temp = temp->next;
		}
	}
}
