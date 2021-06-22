/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:53:00 by fhamel            #+#    #+#             */
/*   Updated: 2019/10/22 15:53:01 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"

void	free_lst(t_list *lst, void (*del)(void *))
{
	ft_lstclear(&lst, (*del));
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*current;

	if (!lst || !(*f) || !(*del))
		return (NULL);
	new_lst = ft_lstnew((*f)(lst->content));
	current = new_lst;
	lst = lst->next;
	while (lst)
	{
		if (!(current->next = ft_lstnew((*f)(lst->content))))
		{
			free_lst(new_lst, (*del));
			return (NULL);
		}
		current = current->next;
		lst = lst->next;
	}
	return (new_lst);
}
