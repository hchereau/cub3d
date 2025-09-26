/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:01:39 by imback            #+#    #+#             */
/*   Updated: 2024/05/20 11:46:45 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstmap;
	t_list	*transi;

	lstmap = NULL;
	while (lst != NULL)
	{
		transi = ft_lstnew(f(lst->content));
		if (transi == NULL)
			return (ft_lstclear(&lstmap, del), NULL);
		lst = lst->next;
		ft_lstadd_back(&lstmap, transi);
	}
	return (lstmap);
}
