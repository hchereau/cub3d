/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <hchereau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:33:02 by hchereau          #+#    #+#             */
/*   Updated: 2023/02/27 14:46:22 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_arg_c(t_data *data, va_list args)
{
	char	c;

	c = va_arg(args, int);
	add_buffer_char(data, c);
}

void	get_arg_string(t_data *data, va_list args)
{
	char	*string;

	string = va_arg(args, char *);
	add_buffer_string(data, string);
}

void	get_char(t_data *data, char c)
{
	char	c_str[2];

	c_str[0] = c;
	c_str[1] = '\0';
	add_buffer_string(data, c_str);
}

int	add_pourcent(t_data *data, ssize_t index_funtab)
{
	if (index_funtab == 8)
	{
		add_buffer_char(data, '%');
		return (1);
	}
	return (-1);
}
