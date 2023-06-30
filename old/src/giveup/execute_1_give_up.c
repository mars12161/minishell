/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:12:48 by yli               #+#    #+#             */
/*   Updated: 2023/06/28 20:19:32 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_multi_pipe_exec(t_parse *node, t_env **env);

static char    *get_path(char *cmd, t_env **env)
{
    char *path;
    char *dir;
    char *result;
    t_env   *temp;

    temp = *env;
    while(temp)
    {
        if (!strncmp(temp->content, "PATH=", 5))
            break ;
        temp = temp->next;
    }
    if (!temp->content)
        return (cmd);
    path = temp->content + 5;
    while (path && ft_count_size(path, ':'))
    {
        dir = str_ncpy(path, ft_count_size(path, ':'));
        result = ft_strjoin_path_cmd(dir, '/', cmd);
        free(dir);
        if (access(result, F_OK) == 0)
            return (result);
        free(result);
        path += ft_count_size(path, ':') + 1;
    }
    return (cmd);
}

// static int	ft_executer(char **whole_line, char **env) //todo
// {
//     char *path;

//     if (ft_count_size(whole_line[0], '/'))
//         path = whole_line[0];
//     else
//         path = get_path(whole_line[0], env);
//     execve(path, whole_line, env);
//     ft_error("command not found");
//     return (127);
// }

static int	ft_executer(char **whole_line, char **env) //todo
{
    char *path;

    if (ft_count_size(whole_line[0], '/'))
        path = whole_line[0];
    else
        path = get_path(whole_line[0], env);
    execve(path, whole_line, env);
    ft_error("command not found");
    return (127);
}

static void ft_redir(char **whole_line, char **env, int fd_in) //todo
{
    pid_t pid;
    int fd[2];

    if (pipe(fd) == -1)
    {
        ft_error ("pipe open failed");
        return (1);
    }
    pid = fork();
    if (pid)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        waitpid(pid, NULL, 0);
    }
    else
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        if (fd_in == STDIN_FILENO)
        {
            ft_error("fd_in wrong");
            return (1);
        }
        else
            ft_executer(whole_line, env);
    } 
}

int ft_multi_pipe_exec(t_parse *node, t_env **env)
{
    int fd_in;
    int fd_out;
    int i;
    char **penv;

    i = 0;
    env = ft_env_str(env);
    fd_in = check_infile(node);
    fd_out = check_outfile(node);
    if (fd_in == -1 || fd_out == -1)
    {
        ft_error("open infile or outfile failed");
        return (1);
    }
    dup2(fd_in, STDIN_FILENO);
    dup2(fd_out, STDOUT_FILENO);
    ft_redir(node->whole_line[0], penv, fd_in);
    while(node->whole_line[i])
        ft_redir(node->whole_line[i++], penv, 1);
    ft_executer(node->whole_line[i], penv);
    return (1);
}