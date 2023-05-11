#include "builtin.h"

int ft_cd(t_builtin *node)
{
    if (node->size == 1)
        return (-1);
    if (node->command[1] == '-')
        return (ft_lastpwd(node));
    if (chdir(node->command[1]) == -1)
        return (-1); //free & error
    else 
        return (chdir(node->command[1]));
}