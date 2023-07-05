/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:50:57 by yli               #+#    #+#             */
/*   Updated: 2023/07/03 18:06:06 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env *new_node_ENV(char *str);
void ft_add_tail_env(t_env **env, t_env *new_node);
t_env *init_env(char **envp, t_env *env);
int get_env_size(t_env **env);
char **ft_env_str(t_env **env);

t_env *new_node_ENV(char *str)
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
        ft_add_tail_env(&env,new_node_ENV(envp[i]));
        i++;
    }
    return (env);
}

int get_env_size(t_env **env)
{
    t_env *temp;
    int i;

    i = 0;
    temp = *env;
    if (!env || !*env)
        return (0);
    while (temp)
    {
        i++;
        temp = temp->next;
    }
    //printf("env size: %d\n ", i);
    return (i);
}

char **ft_env_str(t_env **env)
{
    t_env *temp;
    char **envp;
    int i;

    i = get_env_size(env);
    envp = malloc(sizeof(char *) * (i + 1));
    envp[i] = NULL;
    if (!envp)
        return (NULL);
    temp = *env;
    i = 0;
    while(temp)
    {
        envp[i] = ft_strdup(temp->content);
        //printf("envp[i]: %s\n", envp[i]);
        i++;
        temp = temp->next;
    }
    //printf("env size: %d\n ", i);
    return (envp);
}