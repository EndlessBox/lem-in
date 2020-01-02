# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nouhaddo <nouhaddo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/01 14:40:46 by nouhaddo          #+#    #+#              #
#    Updated: 2019/10/24 08:30:03 by nouhaddo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC = main.c\
	  read_rooms.c\
	  read_connections.c\
	  hash_functions.c\
	  ft_tools.c\
	  ft_tools2.c\
	  ft_queue.c\
	  bfs.c\
	  paths.c\
	  nodes.c\
	  score.c\
	  move_ants.c\
	  ft_clean.c\
	  ft_group.c

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror

LIBFT = ./libft

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(OBJ)  $(LIBFT)/libft.a -o $(NAME)

$(OBJ): %.o : %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	make -C ./libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all
