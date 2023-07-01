/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:43 by yli               #+#    #+#             */
/*   Updated: 2023/07/01 12:31:23 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cd(t_parse *node, t_env **env);

static int	ft_cd_env(char *str, t_env **env)
{
	t_env	*temp;
	char	*result;
	int		homefound;

	homefound = 0;
	temp = *env;
	while (temp)
	{
		if (!strncmp(temp->content, str, ft_strlen(str)))
		{
			result = ft_strtrim((char const *)temp->content, (char const *)str);
			printf("%s\n", result);
			chdir(result);
			if (!strncmp(str, "HOME=", ft_strlen(str)))
				homefound = 1;
			else
				homefound = 0;
		}
		temp = temp->next;
	}
	if (!homefound)
		ft_error("HOME not set");
	return (0);
}

static int	ft_split_homepath(char *str, t_parse *node, t_env **env)
{
	char	*result;
	char	*homepath;
	char	*finalpath;
	t_env	*temp;

	temp = *env;
	result = ft_strtrim(node->whole_line[1], "~");
	while (temp)
	{
		if (!strncmp(temp->content, "HOME=", 5))
		{
			homepath = ft_strtrim((char const *)temp->content, "HOME=");
			finalpath = ft_strjoin(homepath, result);
			if (chdir(finalpath) == -1)
				ft_error("cd: no such file or directory");
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
	else if (node->whole_line[1][0] == '~' && node->whole_line[1][1] == '\0')
		return (ft_cd_env("HOME=", env));
	else if (node->whole_line[1][0] == '~' && node->whole_line[1][1] != '\0')
		ft_split_homepath("~", node, env);
	else if (chdir(node->whole_line[1]) == -1)
		ft_error("cd: no such file or directory");
	else if (node->whole_line[2])
		ft_error("cd: too many arguments");
	return (0);
}
