/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:42:56 by yli               #+#    #+#             */
/*   Updated: 2023/06/20 18:42:57 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void    free_shell(t_shell **shell)
{
    t_shell *temp;

    if (!*shell || !shell)
        return ;
    while (*shell)
    {
        temp = (*shell)->next;
        free(*shell);
        *shell = temp;
    }
    *shell = NULL;
}

static void    free_parse(t_parse **node)
{
    if (node == NULL)
        return ;
    
}


static void    free_env(t_env **env)
{
    t_env *temp;

    if (!*env || !env)
        return ;
    while (*env)
    {
        temp = (*env)->next;
        free(*env);
        *env = temp;
    }
    *env = NULL;
}

void    free_all(t_shell **shell, t_parse **node, t_env **env)
{
    free_shell(shell);
    free_parse(node);
    free_env(env);
}

