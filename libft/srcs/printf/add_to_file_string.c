/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_file_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <hchereau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:49:20 by hchereau          #+#    #+#             */
/*   Updated: 2023/02/26 16:51:22 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnjoin_file(size_t size, t_data *data)
{
	char	*join;

	join = (char *)malloc((data->len_str_final + size + 1) * sizeof(char));
	if (join != NULL)
	{
		ft_memcpy(join, data->str_final, data->len_str_final);
		ft_memcpy(join + data->len_str_final, data->buffer, size + 1);
		join[data->len_str_final + size] = '\0';
	}
	return (join);
}

void	add_to_file(size_t size, t_data *data)
{
	char	*p1;

	p1 = data->str_final;
	data->str_final = ft_strnjoin_file(size, data);
	free(p1);
}
