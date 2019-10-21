#include "wolf.h"

void	exit_message(const char *str)
{
	ft_putendl(str);
	exit(0);
}

void    print_usage(void)
{
    ft_putendl("Usage:");
    ft_putendl("\t./wolf3d maps/1.m");
    exit(0);
}
