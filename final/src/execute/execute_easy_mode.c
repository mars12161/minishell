/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_easy_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:11:35 by yli               #+#    #+#             */
/*   Updated: 2023/07/21 21:16:29 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		execute_easy_mode(t_parse_arr *cmmarr, t_env *env);
void	builtin_exit(t_parse *node, t_env *env);
int		execute_exit(t_shell *shell, t_parse_arr *cmmarr,
			t_env *env, char *str);

int	execute_easy_mode(t_parse_arr *cmmarr, t_env *env)
{
	char	**envp;

	redir_child(cmmarr->cmm[0]);
	if (cmmarr->cmm[0]->command == NULL)
		exit(g_exit);
	envp = ft_env_str(env);
	ft_executer(cmmarr->cmm[0]->whole_line, envp);
	return (1);
}

void	builtin_exit(t_parse *node, t_env *env)
{
	int	check;

	check = exec_builtin(node, &env);
	if (check == -1 || check == 0)
		exit(0);
	else
		exit(g_exit);
}

int	execute_exit(t_shell *shell, t_parse_arr *cmmarr, t_env *env, char *str)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == 0)
		execute_easy_mode(cmmarr, env);
	else
	{
		signal(SIGINT, sigint_process);
		waitpid(pid, &status, 0);
	}
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	free_all_in_loop(&shell, cmmarr, str);
	return (g_exit);
}
