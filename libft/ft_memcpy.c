#include "includes/libft.h"

void *ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    size_t i = 0;
    if (!dst && !src)
        return (NULL);
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (dst);
}
