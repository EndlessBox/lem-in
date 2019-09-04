/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:58:14 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/08/05 23:57:59 by ybouladh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_free_exit(t_container *cont, char *error)
{
	if (cont->content)
		free(cont->content);
	if (cont->source)
		free(cont->source);
	if (cont->sink)
		free(cont->sink);
	if (cont->hash_table)
		free(cont->hash_table);
	ft_error(error);
}

void			print_hash_table(t_hash **hash_table)
{
	int			i;
	t_hash		*curr;
	t_addr		*nei;
	t_room		*room;

	i = -1;
	while (++i < H_SIZE)
		if (hash_table[i] != NULL)
		{
			curr = hash_table[i];
			while (curr != NULL)
			{
				ft_printf("%s connect to : ", curr->room->name);
				nei = curr->room->neighbors;
				while (nei)
				{
					room = nei->addr;
					ft_printf("| %s |", room->name);
					nei = nei->next;
				}
				ft_printf(" ** ");
				curr = curr->next;
			}
			ft_putchar('\n');
		}
}

void			store_rooms(t_container *container)
{
	int			line;
	t_queue		*queue;
	t_room		*room;

	line = 0;
	container->content = ft_get_file_content(0, 1000);
	line = ft_read_ants_nbr(container);
	line = ft_read_rooms(container, line);
	if (!container->source || !container->sink)
		ft_free_exit(container, RED("room start or end or both not present"));
	get_relations(container, line);
	queue = ft_new_queue();
	room = ft_get_value(container->hash_table, container->source, container->power);
	room->vis = 1;
	room->parent = NULL;
	ft_enque(queue, room);
	bfs(queue, container);
	//print_hash_table(container->hash_table);
}

int				main(void)
{
	t_container	container;


	container.hash_table = (t_hash**)malloc(sizeof(t_hash*) * H_SIZE);
	store_rooms(&container);
	return (0);
}
