/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:07:24 by linux             #+#    #+#             */
/*   Updated: 2025/09/29 14:10:42 by linux            ###   ########.fr       */
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

static void	parse_exit(t_parse_ctx *ctx)
{
	parse_cleanup(ctx);
	exit(EXIT_FAILURE);
}

void	parse_error(const char *msg, t_parse_ctx *ctx)
{
	printf("Error\n%s\n", msg);
	parse_exit(ctx);
}

void	parse_error_detail(const char *msg, const char *detail,
		t_parse_ctx *ctx)
{
	if (!detail)
	{
		parse_error(msg, ctx);
		return ;
	}
	printf("Error\n%s%s\n", msg, detail);
	parse_exit(ctx);
}
