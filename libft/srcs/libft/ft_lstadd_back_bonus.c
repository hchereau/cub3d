/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:05:11 by imback            #+#    #+#             */
/*   Updated: 2024/09/07 11:51:00 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr_node;

	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			curr_node = *lst;
			while (curr_node->next != NULL)
			{
				curr_node = curr_node->next;
			}
			curr_node->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}
