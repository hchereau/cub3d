#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

size_t ft_strlen(const char *s);
char *ft_strdup(const char *s1);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strchr(const char *s, int c);
void *ft_calloc(size_t count, size_t size);
void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memset(void *b, int c, size_t len);
int ft_atoi(const char *str);
char **ft_split(char const *s, char c);
int ft_isdigit(int c);

#endif
