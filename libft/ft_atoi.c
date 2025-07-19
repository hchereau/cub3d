#include "includes/libft.h"

int ft_atoi(const char *str)
{
    long n = 0;
    int sign = 1;
    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (ft_isdigit(*str))
    {
        n = n * 10 + (*str - '0');
        str++;
    }
    return ((int)(n * sign));
}
