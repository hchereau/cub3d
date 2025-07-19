#include "parse.h"

static char *join_buf(char *s1, char *buf, ssize_t r, size_t len)
{
    char    *tmp;

    tmp = ft_calloc(len + r + 1, 1);
    if (!tmp)
        return (NULL);
    if (s1)
        ft_memcpy(tmp, s1, len);
    ft_memcpy(tmp + len, buf, r);
    free(s1);
    return (tmp);
}

char    *file_to_string(const char *path)
{
    int     fd;
    char    buf[1024];
    ssize_t r;
    char    *data;
    size_t  len;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    data = NULL;
    len = 0;
    r = read(fd, buf, 1024);
    while (r > 0)
    {
        data = join_buf(data, buf, r, len);
        if (!data)
            break ;
        len += r;
        r = read(fd, buf, 1024);
    }
    close(fd);
    if (r < 0 || !data)
        return (free(data), NULL);
    return (data);
}
