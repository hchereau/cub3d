/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linux <linux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:22:29 by linux             #+#    #+#             */
/*   Updated: 2025/07/21 10:41:08 by linux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define EXIT_FAILURE 1
# define BUFFER_SIZE_PARSING_CUBE 1024

typedef enum e_state_parsing
{
	PARSING_FAILURE = -1,
	PARSING_SUCCESS
}	t_state_parsing;

void	parse_file(const char *file, t_config *config);
char	*file_to_string(const char *path);
void	parse_error(const char *msg);
int		is_empty_line(char *line);
int		is_map_line(char *line);
void	free_split(char **tab);
int		parse_color(char *line, t_config *cfg, int is_floor);
int		parse_texture(char *line, char **store);
int		parse_map(char **lines, int start, t_config *cfg);
void	validate_map(t_config *cfg);

#endif
