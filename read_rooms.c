/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 17:10:08 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/10/25 03:02:15 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	read and store number of ants
**	return position to start of next line
**	otherwise if an error occur the function exit and free all memory malloced
*/

int			ft_read_ants_nbr(t_container *cont)
{
	int		pos;
	int		len;
	long	n;

	pos = 0;
	n = 0;
	if (cont->content[pos] == '#')
		ft_read_comment(cont, &pos);
	if (cont->content[pos] == '+')
		pos++;
	len = 0;
	while (ft_isdigit(cont->content[pos + len]) && len < 10)
	{
		n = n * 10 + (cont->content[pos + len] - '0');
		len++;
	}
	if (cont->content[pos + len] != '\n' || n > MX_INT || n <= 0)
		ft_free_exit(cont, 0);
	cont->nbr_ants = n;
	return (len + pos + 1);
}

/*
**	check the form of coordinates (must be a number and containe two numbers)
**	return position to the next line
**	otherwise if an error occur the function exit and free all memory malloced
*/

int			ft_check_coordinates(t_container *cont, int cur)
{
	int		pos;

	pos = 0;
	if (cont->content[cur] == '-' || cont->content[cur] == '+')
		pos++;
	while (cont->content[cur + pos] && ft_isdigit(cont->content[cur + pos]))
		pos++;
	if (cont->content[cur + pos] != ' ' || pos == 0 || pos > 9 ||
		(pos == 1 && (cont->content[cur] == '+' || cont->content[cur] == '-')))
		ft_free_exit(cont, 0);
	cur += pos + 1;
	pos = 0;
	if (cont->content[pos] == '-' || cont->content[cur] == '+')
		pos++;
	while (cont->content[cur + pos] && ft_isdigit(cont->content[cur + pos]))
		pos++;
	if (cont->content[cur + pos] != '\n' || pos == 0 || pos > 9 ||
			(pos == 1 && !ft_isdigit(cont->content[cur])))
		ft_free_exit(cont, 0);
	return (cur + pos + 1);
}

/*
**	skip comment and store next room as start or end depend on comment
**	return position to line after comment
**	otherwise if an error occur the function exit and free all memory malloced
*/

void		ft_read_comment(t_container *c, int *line)
{
	int		n;

	n = ft_findchar(c->content + *line, '\n');
	if (n > 0 && ft_strncmp("##start\n", c->content + *line, 8) == 0)
	{
		*line += n + 1;
		if (c->source != NULL || (n = ft_findchar(c->content + *line, ' ')) < 0)
			ft_free_exit(c, 0);
		c->source = ft_strndup(c->content + *line, n);
	}
	else if (n > 0 && ft_strncmp("##end\n", c->content + *line, 6) == 0)
	{
		*line += n + 1;
		if (c->sink != NULL || (n = ft_findchar(c->content + *line, ' ')) < 0)
			ft_free_exit(c, 0);
		c->sink = ft_strndup(c->content + *line, n);
	}
	else
	{
		*line += (n < 0 ? ft_strlen(c->content + *line) : n + 1);
		if (c->content[*line] == '#')
			ft_read_comment(c, line);
	}
}

/*
**	parse room's name from input,check name form and insert it to hash_table,
**	with checking of input format.
**	return position to line with room's connection start
**	otherwise if an error occur the function exit and free all memory malloced
*/

int			ft_read_rooms(t_container *c, int line)
{
	int		pos;
	t_room	*new_room;

	while (c->content[line])
	{
		pos = 0;
		if (c->content[line] == '#')
			ft_read_comment(c, &line);
		while (c->content[line + pos] && c->content[line + pos] != ' ' &&
				c->content[line + pos] != '\n')
			pos++;
		if (!c->content[line + pos] || c->content[pos + line] == '\n')
			return (line);
		if (c->content[pos + line] != ' ' || c->content[line] == 'L')
			ft_free_exit(c, 0);
		if (!(new_room = ft_new_t_room(c->content + line, pos)))
			ft_free_exit(c, 0);
		if (!(ft_insert_value(c->hash_table, new_room, c->power)))
			ft_free_exit(c, 0);
		line = ft_check_coordinates(c, line + pos + 1);
	}
	return (line);
}
