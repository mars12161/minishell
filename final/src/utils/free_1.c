/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:42:56 by yli               #+#    #+#             */
/*   Updated: 2023/06/30 08:41:57 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void    free_shell(t_shell **shell);

void    ft_free_str(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (*str != NULL)
        {
            free(str[i]);
            i++;
        }
        *str = NULL;
    }
    free (str);
}

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

static void    free_parse(t_parse *node)
{
    if (node == NULL)
        return ;
    ft_free_str(node->whole_line);
    ft_free_str(&node->infilepath);
    ft_free_str(&node->outfilepath);
    free(node); 
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

void    free_all(t_shell **shell, t_parse_arr *node, t_env **env)
{
    free_shell(shell);
    //free_parse(node);
    free_env(env);
}

