#include "builtin.h"

int ft_exit(void)
{
    printf("exit\n");
    //free everything
    exit(0);
}