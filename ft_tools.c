/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 15:46:40 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/10/23 22:30:14 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_free_exit(t_container *cont, int status)
{
	if (cont->content)
		free(cont->content);
	if (cont->source)
		free(cont->source);
	if (cont->sink)
		free(cont->sink);
	if (cont->hash_table)
		ft_free_hash_table(cont->hash_table);
	if (status != 1 && cont)
	{
		ft_putstr("ERROR\n");
		exit(0);
	}
}

t_room			*ft_new_t_room(char *s, int len)
{
	t_room		*new;

	if (!(new = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	if (len == 0)
	{
		if (!(new->name = ft_strdup(s)))
			return (NULL);
	}
	else
	{
		if (!(new->name = ft_strndup(s, len)))
			return (NULL);
	}
	new->neighb_link = NULL;
	new->vis = 0;
	new->blocked = 0;
	new->blocked_flow = 0;
	new->full = 0;
	new->parent = NULL;
	return (new);
}

void			ft_free_t_room(t_room *head)
{
	if (head)
	{
		free(head->name);
		ft_free_t_link(head->neighb_link);
		free(head);
	}
}

t_ant			*new_ants(int nbr)
{
	t_ant		*new;
	int			jumper;

	new = (t_ant *)malloc(sizeof(t_ant) * nbr);
	jumper = -1;
	while (++jumper < nbr)
	{
		(new + jumper)->name = 0;
		(new + jumper)->current = NULL;
	}
	return (new);
}

void			add_to_previous(t_path *paths, t_path *current, int diff)
{
	t_path		*temp;

	temp = paths;
	while (temp && temp != current)
	{
		temp->regulator += diff;
		temp->allowed_ants += diff;
		temp = temp->next;
	}
}
