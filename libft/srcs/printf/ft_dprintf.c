/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 07:19:16 by hchereau          #+#    #+#             */
/*   Updated: 2024/09/17 11:04:07 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_string(const char *str, t_data *data,
					va_list args, void (*funtab[])(t_data *, va_list))
{
	ssize_t			index_funtab;

	while (*str)
	{
		index_funtab = how_printable(str[1]);
		if (*str == '%' && index_funtab != -1)
		{
			if (add_pourcent(data, index_funtab) == -1)
				funtab[index_funtab](data, args);
			++str;
		}
		else
			if (str[0] != '%' || str[1] != '\0')
				add_buffer_char(data, str[0]);
		++str;
	}
	get_size_final(data);
}

void	init_data(t_data *data)
{
	data->str_final = NULL;
	data->len_str_final = 0;
	ft_bzero(data->buffer, BUFFER_SIZE_PRINTF);
	data->index_buffer = 0;
}

int	ft_dprintf(int fd, const char *str, ...)
{
	struct s_data	data;
	va_list			args;
	static void		(*funtab[])(t_data *, va_list) = {get_arg_c, get_arg_string,
		get_arg_p, get_arg_d, get_arg_d, get_arg_u, get_arg_x, get_arg_xmaj};

	if (str == NULL)
		return (-1);
	va_start(args, str);
	init_data(&data);
	get_string(str, &data, args, funtab);
	va_end(args);
	data.len_str_final = write(fd, data.str_final, data.len_str_final);
	free(data.str_final);
	return (data.len_str_final);
}
