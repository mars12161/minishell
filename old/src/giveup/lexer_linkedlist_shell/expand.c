/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:07 by yli               #+#    #+#             */
/*   Updated: 2023/06/20 17:51:08 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_expand(char *str, t_env **env)
{
    t_env   *temp;
    char    *path;
    char    *result;

    temp = *env;
    while(temp)
    {
        
        if (!strncmp(temp->content, str, ft_strlen(str)))
        {
            path = ft_strtrim(temp->content, str);
            if (*path != '=')
                return (NULL);
            result = ft_strtrim(path, "=");
            return (result);
        }
        temp = temp->next;
    }
    return (NULL);
}