/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_4_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:43 by yli               #+#    #+#             */
/*   Updated: 2023/07/24 08:54:46 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cd(t_parse *node, t_env **env);

int	ft_replace_oldpwd(char *str, t_env *env)
{
	char	*new_oldpwd;
	size_t	len;

	len = ft_strlen("OLDPWD=") + ft_strlen(str) + 1;
	while (env)
	{
		if (!ft_strncmp(env->content, "OLDPWD=", 7))
		{
			new_oldpwd = (char *)malloc(len);
			if (!new_oldpwd)
				return (0);
			ft_strlcpy(new_oldpwd, "OLDPWD=", len);
			ft_strlcat(new_oldpwd, str, len);
			free(env->content);
			env->content = new_oldpwd;
		}
		env = env->next;
	}
	return (0);
}

static int	ft_cd_env(char *str, t_env **env)
{
	t_env	*temp;
	char	pwd[PATH_SIZE];
	int		homefound;

	homefound = 0;
	temp = *env;
	while (temp)
	{
		homefound = cd_env_loop(env, temp, pwd, str);
		if (homefound == 1)
			break ;
		temp = temp->next;
	}
	if (!homefound && !ft_strncmp(str, "HOME=", ft_strlen(str)))
		ft_error_optimal("HOME not set", 1);
	else
		g_exit = 0;
	return (0);
}

/* Function used when the input is ~ with a following path: (cd ~/Desktop) */
static int	ft_split_homepath(t_parse *node, t_env **env)
{
	char	*result;
	char	*homepath;
	char	*finalpath;
	char	pwd[PATH_SIZE];
	t_env	*temp;

	temp = *env;
	result = ft_strtrim(node->whole_line[1], "~");
	while (temp)
	{
		if (!ft_strncmp(temp->content, "HOME=", 5))
		{
			getcwd(pwd, PATH_SIZE);
			ft_replace_oldpwd(pwd, *env);
			homepath = ft_strtrim((char const *) temp->content, "HOME=");
			finalpath = ft_strjoin(homepath, result);
			if (chdir(finalpath) == -1)
				ft_error_optimal("cd: no such file or directory", 1);
		}
		temp = temp->next;
	}
	return (0);
}

static int	ft_change_dir(t_parse *node, t_env **env)
{
	char	pwd[PATH_SIZE];

	getcwd(pwd, PATH_SIZE);
	ft_replace_oldpwd(pwd, *env);
	if (chdir(node->whole_line[1]) == -1)
		ft_error_optimal("cd: no such file or directory", 1);
	else
		g_exit = 0;
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
		ft_split_homepath(node, env);
	else if (node->whole_line[2])
		ft_error_optimal("cd: too many arguments", 1);
	else
		ft_change_dir(node, env);
	return (0);
}
