/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:43 by yli               #+#    #+#             */
/*   Updated: 2023/06/23 10:23:13 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(t_parse *node, t_env **env);

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
			chdir(result);
        }
        temp = temp->next;
    }
    return (0);
}

/*int ft_cd(t_parse *node, t_env **env)
{
    int i;

    if (node->wline_count == 1)
        return (-1);
    if (node->whole_line[1][0] == '-')
        return (ft_cd_env("OLDPWD=", env));
        //return (ft_lastpwd(node));
    if (chdir(node->whole_line[1]) == -1)
        return (-1); //free & error
    else 
        return (ft_cd_env("PWD=", env));
}*/

int ft_cd(t_parse *node, t_env **env)
{
	if (node->wline_count == 1)
		return (ft_cd_env("HOME=", env));
	else if (node->whole_line[1][0] == '-')
		return (ft_cd_env("OLDPWD=", env));
	else if (node->whole_line[1][0] == '~')
		return ft_cd_env("HOME=", env);
	//return (ft_lastpwd(node));
	if (chdir(node->whole_line[1]) == -1)
		return (-1); //free & error
	else
		return (chdir(node->whole_line[1]));
}
