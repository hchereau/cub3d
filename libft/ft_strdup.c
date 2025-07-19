#include "includes/libft.h"

char *ft_strdup(const char *s1)
{
    size_t len = ft_strlen(s1);
    char *dup = (char *)malloc(len + 1);
    size_t i = 0;
    if (!dup)
        return (NULL);
    while (i < len)
    {
        dup[i] = s1[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}
