/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:25:01 by yli               #+#    #+#             */
/*   Updated: 2023/07/21 15:46:42 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_pipex(t_parse_arr *cmmarr, t_env *env);

static void	child_pipe_core(int *fd, t_parse *node, t_env *env)
{
	char	**envp;
		
	redir_child(node);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_putstr_fd("dup2 failed", STDERR_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (!check_buildin(node->command))
		builtin_exit(node, env);
	envp = ft_env_str(env);
	ft_executer(node->whole_line, envp);
	ft_free_str(envp);
}

static void	child_pipe_frame(int *fd, t_parse *node, t_env *env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error("fork failed");
	if (pid == 0)
		child_pipe_core(fd, node, env);
	else
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_error("dup2 failed");
		close(fd[1]);
		close(fd[0]);
	}
}

static void	parent_pipe(t_parse_arr *cmmarr, t_env *env)
{
	char	**envp;

	redir_parent(cmmarr);
	if (!check_buildin(cmmarr->cmm[cmmarr->size - 1]->command))
		builtin_exit(cmmarr->cmm[cmmarr->size - 1], env);
	envp = ft_env_str(env);
	ft_executer(cmmarr->cmm[cmmarr->size - 1]->whole_line, envp);
	ft_free_str(envp);
}

static void	pipex(t_parse_arr *cmmarr, t_env *env)
{
	int	fd[2];
	int	i;

	i = 0;
	while (i < cmmarr->size - 1)
	{
		if (pipe(fd) == -1)
			ft_error("pipe failed");
		child_pipe_frame(fd, cmmarr->cmm[i], env);
		i++;
	}
	parent_pipe(cmmarr, env);
}

void	init_pipex(t_parse_arr *cmmarr, t_env *env)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == -1)
		ft_error("fork failed");
	if (!pid)
		pipex(cmmarr, env);
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
}
