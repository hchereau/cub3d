#include "includes/libft.h"

void *ft_memset(void *b, int c, size_t len)
{
    unsigned char *p = (unsigned char *)b;
    size_t i = 0;
    while (i < len)
        p[i++] = (unsigned char)c;
    return (b);
}
