/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:25:01 by yli               #+#    #+#             */
/*   Updated: 2023/07/05 20:49:59 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_pipex(t_parse_arr *cmmarr, t_env *env);

static void	child_pipe_core(int *fd, t_parse *node, t_env *env)
{
	char **envp;

	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("dup2 failed");
	redir_child(node); //check
	close(fd[0]);
	if (!check_buildin(node->command))
		builtin_exit(node, env);
	envp = ft_env_str(&env);
	printf("%s\n", envp[3]);
	printf("%s\n", envp[10]);
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
	}
}

static void	parent_pipe(t_parse_arr *cmmarr, t_env *env)
{
	char	**envp;

	redir_parent(cmmarr);
	if (!check_buildin(cmmarr->cmm[cmmarr->size - 1]->command))
		builtin_exit(cmmarr->cmm[cmmarr->size - 1], env);
	envp = ft_env_str(&env);
	ft_executer(cmmarr->cmm[cmmarr->size -1]->whole_line, envp);
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

int	init_pipex(t_parse_arr *cmmarr, t_env *env)
{
	int	pid;
	int	check;

	pid = fork();
	check = 0;
	if (pid == -1)
		ft_error("fork failed");
	if (!pid)
		pipex(cmmarr, env);
	else
		check = waitpid(pid, NULL, 0);
	if (!check)
		return (-1); //failed
	return (0);
}
