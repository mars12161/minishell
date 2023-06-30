/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:07 by yli               #+#    #+#             */
/*   Updated: 2023/06/30 08:40:51 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char    *ft_expand(char *str, t_env **env)
{
    t_env   *temp;
    char    *path;
    char    *result;

    temp = *env;
    printf("str in expand: %s\n", str);
    while(temp)
    {
        if (str[0] == '?')
        {
            result = "500"; //g_exit
            return (result);
        }
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