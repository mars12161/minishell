#include "builtin.h"

static int ft_check_n_export(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] != '=')
            return (0);
        i++;
    }
    return (1);
}

static int ft_check_signal_export(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (str[1] >= '0' && str[1] <= '9')
        return (-1);
    while(str[i])
    {
        if (str[i] == '=')
            break ;
        i++;
    }
    while(j < i)
    {
        if (str[j] == '!' ||str[j] == '@' || str[j] == '#' || str[j] == '%' || str[j] == '+'|| str[j] == '-'|| str[j] == '/')
            return (-1);
        else if (str[j] == '(' ||str[j] == ')')
            return (-2);
        else if (str[j] == ')')
            return (-3);
        j++;
    }
    return (0);
}

int ft_export(t_builtin *node, t_env **env)
{
    t_env *export;

    export = NULL;
    if (node->size == 1)
        return (ft_env(env));
    if (ft_check_n_export(node->command[1]))
        return (0);
    else
    {
        if (!ft_check_signal_export(node->command[1]))
        {
            export = new_node_env(node->command[1]);
            ft_add_tail_env(env, export);
            ft_env(env);
        }
        else if (ft_check_signal_export(node->command[1]) == -1)
            printf("%s: '%s': not a valid identifier", node->command[0], node->command[1]);
        else if (ft_check_signal_export(node->command[1]) == -2)
            printf("syntax error near unexpected token `('");
        else if (ft_check_signal_export(node->command[1]) == -3)
            printf("syntax error near unexpected token `)'");
    }
    return (0);
}