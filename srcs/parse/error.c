/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:07:24 by linux             #+#    #+#             */
/*   Updated: 2025/09/29 13:05:44 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	parse_cleanup(t_parse_ctx *ctx)
{
	if (!ctx)
		return ;
	if (ctx->lines)
		free_split(ctx->lines);
	if (ctx->cfg)
		free_config(ctx->cfg);
}

void	parse_error(const char *msg, t_parse_ctx *ctx)
{
	printf("Error\n%s\n", msg);
	parse_cleanup(ctx);
	exit(EXIT_FAILURE);
}
