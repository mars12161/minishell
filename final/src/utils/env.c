/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:50:57 by yli               #+#    #+#             */
/*   Updated: 2023/07/06 21:23:01 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env *new_node_ENV(char *str);
void ft_add_tail_env(t_env **env, t_env *new_node);
t_env *init_env(char **envp, t_env *env);
char **ft_env_str(t_env *env);

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

static int get_env_size(t_env **env)
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
    return (i);
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
    env->size = get_env_size(&env);
    return (env);
}

char **ft_env_str(t_env *env)
{
    char **envp;
    int i;

    envp = malloc(sizeof(char *) * (env->size + 1));
    envp[env->size] = NULL;
    if (!envp)
        return (NULL);
    i = 0;
    while(env)
    {
        envp[i] = ft_strdup(env->content);
        i++;
        env = env->next;
    }
    return (envp);
}