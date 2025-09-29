/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:51:33 by linux             #+#    #+#             */
/*   Updated: 2025/09/29 14:10:42 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define EXIT_FAILURE 1
# define BUFFER_SIZE_PARSING_CUBE 1024
# define CUB_EXTENSION ".cub"

typedef enum e_state_parsing
{
	PARSING_FAILURE = -1,
	PARSING_SUCCESS
}	t_state_parsing;

typedef struct s_parse_ctx
{
	t_config	*cfg;
	char		**lines;
}	t_parse_ctx;

void	parse_file(const char *file, t_config *config);
char	*file_to_string(const char *path);
void	parse_error(const char *msg, t_parse_ctx *ctx);
void	parse_error_detail(const char *msg, const char *detail,
			t_parse_ctx *ctx);
int		is_empty_line(char *line);
int		is_map_line(char *line);
void	free_split(char **tab);
int		has_cub_extension(const char *path);
int		parse_color(char *line, t_config *cfg, int is_floor,
			t_parse_ctx *ctx);
int		parse_texture(char *line, char **store, t_parse_ctx *ctx,
			char *label);
int		parse_map(char **lines, int start, t_config *cfg,
			t_parse_ctx *ctx);
void	validate_map(t_config *cfg, t_parse_ctx *ctx);
void	free_config(t_config *cfg);

#endif
