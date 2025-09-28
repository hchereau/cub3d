/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:07:24 by linux             #+#    #+#             */
/*   Updated: 2025/09/15 16:07:26 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

typedef struct s_parse_state
{
	t_config	*cfg;
	char		**lines;
}	t_parse_state;

static t_parse_state	g_parse_state;

static void	parse_cleanup(void)
{
	if (g_parse_state.lines)
	{
		free_split(g_parse_state.lines);
		g_parse_state.lines = NULL;
	}
	if (g_parse_state.cfg)
	{
		free_config(g_parse_state.cfg);
		g_parse_state.cfg = NULL;
	}
}

void	parse_register_config(t_config *cfg)
{
	g_parse_state.cfg = cfg;
}

void	parse_register_lines(char **lines)
{
	g_parse_state.lines = lines;
}

void	parse_error(const char *msg)
{
	printf("Error\n%s\n", msg);
	parse_cleanup();
	exit(EXIT_FAILURE);
}
