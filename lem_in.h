/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:07:45 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/11/15 23:55:24 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# define H_SIZE 4001

/*
** debuging defines
*/

# define EX exit(120);
# define NEW_L ft_putchar('\n');
# define DEB1 ft_putendl(MAGENTA("HERE : 1"));
# define DEB2 ft_putendl(RED("HERE : 2"));
# define DEB3 ft_putendl(YELLOW("HERE : 3"));
# define DEB4 ft_putendl(CYAN("HERE : 4"));
# define DEB5 ft_putendl(BLUE("HERE : 5"));
# define DEB6 ft_putendl(GREEN("HERE : 5"));

typedef	struct		s_node
{
	char			*name;
	struct s_node	*next;
}					t_node;

typedef	struct		s_ant
{
	int				name;
	t_node			*current;
}					t_ant;

typedef struct		s_room
{
	char			*name;
	int				vis;
	int				blocked;
	int				blocked_flow;
	void			*parent;
	int				full;
	t_link			*neighb_link;
}					t_room;

typedef struct		s_hash
{
	t_room			*room;
	struct s_hash	*next;
}					t_hash;

typedef struct		s_container
{
	char			*content;
	int				nbr_ants;
	t_hash			**hash_table;
	t_ant			*ants;
	char			*source;
	char			*sink;
	long long		power[101];
}					t_container;

typedef struct		s_queue
{
	t_addr			*first;
	t_addr			*last;
}					t_queue;

typedef struct		s_path
{
	t_node			*head;
	int				depth;
	int				regulator;
	int				allowed_ants;
	struct s_path	*next;
}					t_path;

typedef struct		s_group
{
	t_path			*paths;
	int				flow;
	int				score;
	int				total_dep;
	t_path			*last;
	struct s_group	*last_g;
	struct s_group	*next;
}					t_group;

/*
** operation on hash table map of key and values
*/

long long			ft_hash(char *str, long long *power);
t_hash				*ft_new_t_hash(t_room *room_addr);
int					ft_insert_value(t_hash **hash_table, t_room *new_room,
					long long *power);
t_room				*ft_get_value(t_container *c, char *key);
void				ft_free_hash_table(t_hash **hash_table);
void				print_hash_table(t_hash **hash_table);

/*
** parsing function
*/

int					ft_read_ants_nbr(t_container *cont);
int					ft_check_coordinates(t_container *cont, int curr);
void				ft_read_comment(t_container *cont, int *line);
int					ft_read_rooms(t_container *c, int line);
int					set_connection(t_room *room1, t_room *room2);
int					get_relations(t_container *c, int line);

/*
**	Functions to manage Queue's
*/

t_queue				*ft_new_queue();
void				ft_enque(t_queue *q, void *data);
void				ft_pop(t_queue *q);
int					ft_free_queue(t_queue *q);

/*
** small tools
*/

void				ft_free_exit(t_container *cont, int status);
t_room				*ft_new_t_room(char *s, int len);
void				ft_free_t_room(t_room *head);
int					source_sink(t_container *c);
t_group				*source_sink_group(t_container *c);
void				ft_init(t_container *c);

/*
**	function to test !
*/

t_group				*find_paths(t_container *container, t_queue **queue);
int					search_graph(t_queue *queue, t_container *container);
void				back_track(t_container *container);
int					clean_it(t_container *container);
int					clean_blocked_rooms(t_container *container);
t_group				*make_group(t_container *c);
void				add_path_group(t_group *group, t_path *path);
t_path				*make_path(t_container *c);
void				enque_path(t_container *container, t_path *path,
					t_room *data);
int					enque_group(t_group **main_grp, t_group *group);
int					enque_node(t_path *path, t_node *node);
t_node				*make_node(t_container *c, char *str);
int					update_score(int ants, t_group *group, t_path *path);
int					check_score(int ants, t_group *group, t_path *path);
void				calcul_spread_ants(t_container *container, t_group *group);
t_group				*low_score(t_group *group);
t_ant				*new_ants(int nbr);
void				send_it(t_container *container);
t_link				*get_neighbor(char *to_find, t_link *neighbors);
int					search_graph2(t_queue *queue, t_container *container,
					t_group *group);
void				clean_cost(t_container *container);
t_queue				*get_queue(t_container *container);
int					checker(t_container *container);
int					clean_blocked_flow(t_container *container);
void				free_nodes(t_node *node);
void				free_paths(t_path *path);
void				free_groups(t_group *group, t_group *dont);

/*
** Debug functions
*/

/*
**	void				show_ants(t_ant	*ants, int len);
**	void				show_group_path(t_group *group);
**	void				show_route(t_node *head);
**	void				show_paths(t_path *head);
**	void				show_groups(t_group *group);
**	void				show_queue(t_queue *queue);
**	void				show_node(t_container *container);
*/

#endif
