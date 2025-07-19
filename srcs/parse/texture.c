#include "parse.h"

int parse_texture(char *line, char **store)
{
    while (*line && *line != ' ')
        line++;
    while (*line == ' ')
        line++;
    if (*store)
        return (-1);
    *store = ft_strdup(line);
    if (!*store)
        return (-1);
    return (0);
}
