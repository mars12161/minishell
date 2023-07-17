/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_easy_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:11:35 by yli               #+#    #+#             */
/*   Updated: 2023/07/17 14:56:59 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		execute_easy_mode(t_parse_arr *cmmarr, t_env *env);
void	builtin_exit(t_parse *node, t_env *env);
int		execute_exit(t_shell *shell, t_parse_arr *cmmarr,
			t_env *env, char *str);

/* static int	no_pipe_builtin(t_cmd_arr *cmd_arr, t_envp *envl,
 	char *input, t_lex *head)
 {
 	bool	exit;
 	int		stdout_backup;

 	stdout_backup = dup(STDOUT_FILENO);
 	if (cmd_arr->cmds[0]->redir_out == true || cmd_arr->cmds[0]->append == true)
 		redir_out(cmd_arr->cmds[0]);
 	exit = false;
 	g_exit = exec_builtin(cmd_arr->cmds[0], envl, &exit);
 	free_cmd_arr(cmd_arr);
 	free(input);
 	ft_lstclear_lex(&head);
 	dup2(stdout_backup, STDOUT_FILENO);
 	if (exit == true)
 		return (0);
 	return (1);
 }*/

/*static void printCharString(char** str) {
	if (str == NULL) {
		printf("Empty string\n");
		return;
	}

	while (*str != NULL) {
		printf("%s\n", *str);
		str++;
	}
}*/

int	execute_easy_mode(t_parse_arr *cmmarr, t_env *env)
{
	char	**envp;

	redir_child(cmmarr->cmm[0]);
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
		g_exit = 130;
		waitpid(pid, &status, 0);
	}
	//g_exit = 0;
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	free_all_in_loop(&shell, cmmarr, str);
	return (g_exit);
}

// int	execute_easy_mode(t_parse_arr *cmmarr, t_env *env)
// {
//     char **envp;

//     redir_child(cmmarr->cmm[0]);
//     envp = ft_env_str(env);
//     ft_executer(cmmarr->cmm[0]->whole_line, envp);
//     return (0);
// }

// void    builtin_exit(t_parse *node, t_env *env)
// {
//     int check;

//     check = exec_builtin(node, &env);
//     if (!check)
//         exit(0);
//     else
//         exit(1);
// }
