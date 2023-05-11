#include "builtin.h"

static int ft_cd_env(char *str, t_env **env)
{
    t_env *temp;
    char *result;

    temp = *env;
    while (temp)
    {
        if (!strncmp(temp->content, str, ft_strlen(str)))
        {
            result = ft_strtrim((char const *)temp->content, (char const *)str);
            printf("%s\n", result);
        }
        temp = temp->next;
    }
    return (0);
}

int ft_cd(t_builtin *node, t_env **env)
{
    int i;

    if (node->size == 1)
        return (-1);
    if (node->command[1][0] == '-')
        return (ft_cd_env("OLDPWD=", env));
        //return (ft_lastpwd(node));
    if (chdir(node->command[1]) == -1)
        return (-1); //free & error
    else 
        return (ft_cd_env("PWD=", env));
    return (0);
}