#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>

void    parse_file(const char *file, t_config *config);
char    *file_to_string(const char *path);
void    parse_error(const char *msg);
int     is_empty_line(char *line);
int     is_map_line(char *line);
void    free_split(char **tab);
int     parse_color(char *line, t_config *cfg, int is_floor);
int     parse_texture(char *line, char **store);
int     parse_map(char **lines, int start, t_config *cfg);
void    validate_map(t_config *cfg);

#endif
