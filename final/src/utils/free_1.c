/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:42:56 by yli               #+#    #+#             */
/*   Updated: 2023/07/06 23:18:51 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    free_shell(t_shell **shell);
void    free_env(t_env **env);
void    free_all(t_shell **shell, t_parse_arr *cmmarr);

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
    if (node->redirection_in)
        free(node->infilepath);
    if (node->redirection_out)
        free(node->outfilepath);
    free(node); 
}

static void free_cmmarr(t_parse_arr *cmmarr)
{
    int i;

    i = 0;
    if (!cmmarr)
        return ;
    while (i <= cmmarr->size)
    {
        if (cmmarr->cmm[i])
            free_parse(cmmarr->cmm[i]);
        i++;
    }
    free(cmmarr->cmm);
    free(cmmarr);  
}

void    free_env(t_env **env)
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

void    free_all(t_shell **shell, t_parse_arr *cmmarr)
{
    free_shell(shell);
    free_cmmarr(cmmarr);
}