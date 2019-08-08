/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_t_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouhaddo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:24:25 by nouhaddo          #+#    #+#             */
/*   Updated: 2019/08/01 17:30:53 by nouhaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_addr		*ft_push_t_addr(t_addr *head, void *addr)
{
	t_addr	*curr;

	curr = head;
	if (!head)
		return (ft_new_t_addr(addr));
	else
	{
		while (curr->next)
		{
			if (curr->addr == addr)
				return (head);
			curr = curr->next;
		}
		if (curr->addr != addr)
			if(!(curr->next = ft_new_t_addr(addr)))
				return (NULL);
	}
	return (head);
}
