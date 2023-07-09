/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:11:55 by yli               #+#    #+#             */
/*   Updated: 2023/07/09 14:00:20 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char		*str_ncpy(char *str, int n);
char		*ft_strjoin_path_cmd(char const *s1, char c, char const *s2);
static char	*get_path(char *cmd, char **envp);
void		ft_executer(char **whole_line, char **env);

char	*str_ncpy(char *str, int n)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (n + 1));
	if (!result)
		return (NULL);
	while (i < n)
		result[i++] = *str++;
	result[n] = 0;
	return (result);
}

char	*ft_strjoin_path_cmd(char const *s1, char c, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = c;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

static char	**split_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH=", 5))
		{
			path = ft_split(envp[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**path;
	char	*result;

	i = 0;
	path = split_path(envp);
	if (!path[0])
		return (NULL);
	while (path[i])
	{
		result = ft_strjoin_path_cmd(path[i], '/', cmd);
		if (access(result, F_OK) != -1)
		{
			ft_free_str(path);
			return (result);
		}
		free(result);
		i++;
	}
	ft_free_str(path);
	return (cmd);
}

void	ft_executer(char **whole_line, char **envp)
{
	char	*path;

	if (!access(whole_line[0], F_OK))
		path = whole_line[0];
	else
		path = get_path(whole_line[0], envp);
	execve(path, whole_line, envp);
	free(path);
	ft_error_optimal("command not found", 127);
	exit(g_globe.g_exit);
}
