#include "parse.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    t_config cfg;

    (void)argc;
    ft_memset(&cfg, 0, sizeof(cfg));
    if (!argv[1])
        return (printf("Error\nNo file\n"), 1);
    parse_file(argv[1], &cfg);
    printf("Loaded map %dx%d\n", cfg.map.width, cfg.map.height);
    return (0);
}
