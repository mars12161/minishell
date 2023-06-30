/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:11:55 by yli               #+#    #+#             */
/*   Updated: 2023/06/30 08:50:26 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*str_ncpy(char *str, int n);
char	*ft_strjoin_path_cmd(char const *s1, char c, char const *s2);
static char    *get_path(char *cmd, char **envp);
void    builtin_exit(t_parse *node, t_env *env);
void	ft_executer(char **whole_line, char **env);

char    *str_ncpy(char *str, int n)
{
	char    *result;
	int i;

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

static char    *get_path(char *cmd, char **envp)
{
    int i;
    char *path;
    char *dir;
    char *result;

    i = 0;
    while(envp[i] && !strncmp(envp[i], "PATH=", 5))
        i++;
    if (!envp[i])
        return (cmd);
    path = envp[i] + 5;
    while (path && ft_count_size(path, ':'))
    {
        dir = str_ncpy(path, ft_count_size(path, ':'));
        result = ft_strjoin_path_cmd(dir, '/', cmd);
        free(dir);
        if (!access(result, F_OK))
            return (result);
        free(result);
        path += ft_count_size(path, ':') + 1;
    }
    return (cmd);
}

void    builtin_exit(t_parse *node, t_env *env)
{
    int check;

    check = exec_builtin(node, &env);
    if (!check)
        exit(0);
    else
        exit(1);
}

void	ft_executer(char **whole_line, char **env)
{
    char *path;

    if (!access(whole_line[0], F_OK))
        path = whole_line[0];
    else
        path = get_path(whole_line[0], env);
    execve(path, whole_line, env);
    free(path); //not sure
    ft_error("child survived");
}