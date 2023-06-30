/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:50:57 by yli               #+#    #+#             */
/*   Updated: 2023/06/30 16:04:05 by mschaub          ###   ########.fr       */
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
    return (i);
} //to env.c

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
        envp[i] = temp->content;
        i++;
        temp = temp->next;
    }
    return (envp);
} //to env.c