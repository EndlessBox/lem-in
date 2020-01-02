/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_connections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:30:30 by ybouladh          #+#    #+#             */
/*   Updated: 2019/11/10 16:08:32 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** The function set_connection add a relationship to the room1 with room2 and
** and vice versa.
** return 1 if connection seted otherwise return 0 for an error.
*/

int		set_connection(t_room *room1, t_room *room2)
{
	if (!room1 || !room2)
		return (0);
	if (room1 != room2)
	{
		if (!(room1->neighb_link = ft_push_t_link(room1->neighb_link, room2)))
			return (0);
		if (!(room2->neighb_link = ft_push_t_link(room2->neighb_link, room1)))
			return (0);
	}
	return (1);
}

/*
** The function get_first get the first part of the realtion and prepare it to
** be added to the relationshop list !
*/

char	*get_first(t_container *c, int *pos, int line)
{
	char	*temp;

	while (c->content[line + (*pos)] && c->content[line + (*pos)] != '-' &&
			c->content[line + (*pos)] != '\n')
		(*pos)++;
	if (c->content[line + (*pos)] != '-')
		ft_free_exit(c, 0);
	temp = ft_strndup(c->content + line, (*pos));
	return (temp);
}

/*
** The function get second get the second part of the realtion and prepare it to
** be added to the relationshop list !
*/

char	*get_second(t_container *c, int *pos, int line, int first_break)
{
	char	*temp;

	(*pos)++;
	while (c->content[line + (*pos)] && c->content[line + (*pos)] != '\n' &&
			c->content[line + *pos] != ' ')
		(*pos)++;
	if (c->content[line + (*pos)] != '\n')
		ft_free_exit(c, 0);
	temp = ft_strndup(c->content + line + first_break, (*pos) - first_break);
	return (temp);
}

/*
** The function that read every line from the input and read the rooms
** while checking bad relationships between rooms and the start and the end
** rooms !
*/

int		get_relations(t_container *c, int line)
{
	int		pos;
	char	*temp;
	t_room	*room1;
	t_room	*room2;
	int		first_break;

	while (c->content[line])
	{
		pos = 0;
		if (c->content[line] == '#')
			ft_read_comment(c, &line);
		if (!c->content[line])
			break ;
		temp = get_first(c, &pos, line);
		room1 = ft_get_value(c, temp);
		free(temp);
		first_break = pos + 1;
		temp = get_second(c, &pos, line, first_break);
		room2 = ft_get_value(c, temp);
		free(temp);
		if (!set_connection(room1, room2))
			ft_free_exit(c, 0);
		line += pos + 1;
	}
	return (1);
}
