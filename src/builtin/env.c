#include "builtin.h"

t_env *new_node_env(char *str)
{
    t_env *new_node;
    int i;

    i = 0;
    new_node = NULL;
    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->content = str;
    new_node->next = 0;
    return (new_node);
}

void ft_add_tail_env(t_env **env, t_env *new_node)
{
    t_env *temp;

    if (!new_node)
        return ;
    if (!*env)
    {
		*env = new_node;
        return ;
    }
    temp = *env;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
}

t_env *init_env(char **envp, t_env *env)
{
    int     i;

    i = 0;
    while(envp[i])
    {
        ft_add_tail_env(&env,new_node_env(envp[i]));
        i++;
    }
    return (env);
}

int ft_env(t_env **env)
{
    t_env *temp;

    temp = *env;
    while (temp)
    {
        printf("%s\n", temp->content);
        temp = temp->next;
    }
    return (0);
}