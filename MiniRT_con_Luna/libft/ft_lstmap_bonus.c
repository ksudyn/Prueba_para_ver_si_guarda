/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:19:07 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/11 15:30:02 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	void	*new_content;

	if (lst == NULL)
		return (NULL);
	new_content = f(lst->content);
	new_node = ft_lstnew(new_content);
	if (new_node == NULL)
	{
		if (new_content != NULL)
			del(new_content);
		return (NULL);
	}
	new_node->next = ft_lstmap(lst->next, f, del);
	if (new_node->next == NULL && lst->next != NULL)
	{
		ft_lstclear(&new_node, del);
		return (NULL);
	}
	return (new_node);
}
