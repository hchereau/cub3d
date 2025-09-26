/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <hchereau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:32:05 by hchereau          #+#    #+#             */
/*   Updated: 2023/03/02 15:55:21 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	add_last_buffer(t_data *data, char *str)
{
	size_t	i;

	i = 0;
	while (data->index_buffer < BUFFER_SIZE_PRINTF)
	{
		data->buffer[data->index_buffer] = str[i];
		++i;
		++data->index_buffer;
	}
	return (i);
}

void	add_buffer_string(t_data *data, char *str)
{
	size_t	len_str;
	size_t	index_str;

	if (str)
	{
		len_str = ft_strlen(str);
		if (data->index_buffer + len_str <= BUFFER_SIZE_PRINTF)
		{
			ft_memcpy(data->buffer + data->index_buffer, str, len_str + 1);
			data->index_buffer += len_str;
		}
		else
		{
			index_str = add_last_buffer(data, str);
			add_to_file(BUFFER_SIZE_PRINTF, data);
			data->len_str_final += BUFFER_SIZE_PRINTF;
			ft_bzero(data->buffer, BUFFER_SIZE_PRINTF);
			data->index_buffer = 0;
			add_buffer_string(data, str + index_str);
		}
	}
	else
		add_buffer_string(data, "(null)");
}

void	add_buffer_char(t_data *data, char c)
{
	size_t	len_c;

	len_c = 1;
	if (data->index_buffer + len_c <= BUFFER_SIZE_PRINTF)
	{
		ft_memcpy(data->buffer + data->index_buffer, &c, len_c + 1);
		data->index_buffer += len_c;
	}
	else
	{
		add_to_file(BUFFER_SIZE_PRINTF, data);
		data->len_str_final += BUFFER_SIZE_PRINTF;
		ft_bzero(data->buffer, BUFFER_SIZE_PRINTF + 1);
		data->index_buffer = 0;
		add_buffer_char(data, c);
	}
}

/*
	{
		index_str = add_last_buffer(data, str);
		add_str(&data->str_final, data->buffer, BUFFER_SIZE_PRINTF);

		ft_bzero(data->buffer, BUFFER_SIZE_PRINTF);
		data->index_buffer = 0;
		add_buffer_string(data, str + index_str);
	}
*/
