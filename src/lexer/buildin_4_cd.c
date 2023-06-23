/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:43 by yli               #+#    #+#             */
/*   Updated: 2023/06/23 13:30:11 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_parse *node, t_env **env);

static int	ft_cd_env(char *str, t_env **env)
{
	t_env	*temp;
	char	*result;

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

int	ft_cd(t_parse *node, t_env **env)
{
	if (node->wline_count == 1)
		return (ft_cd_env("HOME=", env));
	else if (node->whole_line[1][0] == '-')
		return (ft_cd_env("OLDPWD=", env));
	else if (node->whole_line[1][0] == '~')
		return (ft_cd_env("HOME=", env));
	if (chdir(node->whole_line[1]) == -1) //print to STDERR instead
		printf("cd: no such file or directory: %s\n", node->whole_line[1]);
	return (0);
}
