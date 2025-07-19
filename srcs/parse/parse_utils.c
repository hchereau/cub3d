#include "parse.h"

int is_empty_line(char *line)
{
    size_t i;

    i = 0;
    while (line && line[i])
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}

int is_map_line(char *line)
{
    while (*line == ' ')
        line++;
    return (*line == '1' || *line == '0' || *line == 'N'
            || *line == 'S' || *line == 'E' || *line == 'W');
}

void    free_split(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return ;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}
