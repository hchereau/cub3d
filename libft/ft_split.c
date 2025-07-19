#include "includes/libft.h"

static int  count_words(const char *s, char c)
{
    int count = 0;
    while (s && *s)
    {
        while (*s && *s == c)
            s++;
        if (*s)
        {
            count++;
            while (*s && *s != c)
                s++;
        }
    }
    return (count);
}

static char *word_dup(const char *s, char c)
{
    int len = 0;
    char *word;
    while (s[len] && s[len] != c)
        len++;
    word = (char *)malloc(len + 1);
    if (!word)
        return (NULL);
    ft_memcpy(word, s, len);
    word[len] = '\0';
    return (word);
}

static void free_all(char **arr, int i)
{
    while (i >= 0)
    {
        free(arr[i]);
        i--;
    }
    free(arr);
}

char **ft_split(char const *s, char c)
{
    char **res;
    int words;
    int i = 0;

    words = count_words(s, c);
    res = (char **)malloc(sizeof(char *) * (words + 1));
    if (!res)
        return (NULL);
    while (i < words)
    {
        while (*s && *s == c)
            s++;
        res[i] = word_dup(s, c);
        if (!res[i])
        {
            free_all(res, i - 1);
            return (NULL);
        }
        while (*s && *s != c)
            s++;
        i++;
    }
    res[i] = NULL;
    return (res);
}
