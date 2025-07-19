#include "parse.h"
#include <stdio.h>

void    parse_error(const char *msg)
{
    printf("Error\n%s\n", msg);
    exit(1);
}
