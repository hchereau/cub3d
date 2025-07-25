/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchereau <hchereau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:01:19 by hchereau          #+#    #+#             */
/*   Updated: 2023/03/02 15:53:03 by hchereau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_arg_d(t_data *data, va_list args)
{
	int		arg_nb;
	char	*free_itoa;

	arg_nb = va_arg(args, int);
	free_itoa = ft_itoa(arg_nb);
	add_buffer_string(data, free_itoa);
	free(free_itoa);
}

void	get_arg_u(t_data *data, va_list args)
{
	unsigned int		arg_nb;
	char				*free_uitoa;

	arg_nb = va_arg(args, unsigned int);
	free_uitoa = ft_uitoa(arg_nb);
	add_buffer_string(data, free_uitoa);
	free(free_uitoa);
}

void	get_arg_x(t_data *data, va_list args)
{
	size_t	arg_nb;

	arg_nb = va_arg(args, unsigned int);
	convert_base(data, arg_nb, BASE_HEXA_MINUS);
}

void	get_arg_xmaj(t_data *data, va_list args)
{
	size_t	argnb;

	argnb = va_arg(args, unsigned int);
	convert_base(data, argnb, BASE_HEXA_MAJUS);
}
