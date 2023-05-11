#include "builtin.h"

static int ft_check_each_n(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

static int ft_check_n(char *str)
{
    int i;

    i = 0;
    if (str[0] == '-')
    {
        str += 1;
        if (ft_check_each_n(str))
            return (1);
        else 
            return (0);
    }
    else
        return (0);
}

int    ft_echo(t_builtin *node)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    if (node->size == 1)
        return (printf("\n"));
    if (ft_check_n(node->command[1]))
    {
        i = 1;
        flag = 1;
    }
    while (i++ < node->size - 1)
    {
        printf("%s", node->command[i]);
        if (i == node->size - 1)
            break ;
        printf(" ");
    }
    if (flag == 0)
        printf("\n");
    return (0);
}


