/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_easy_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:11:35 by yli               #+#    #+#             */
/*   Updated: 2023/07/07 14:07:37 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_easy_mode(t_parse_arr *cmmarr, t_env *env);
void    builtin_exit(t_parse *node, t_env *env);
int  execute_exit(t_parse_arr *cmmarr, t_env *env);

int	execute_easy_mode(t_parse_arr *cmmarr, t_env *env)
{
    char **envp;

    redir_child(cmmarr->cmm[0]);
    envp = ft_env_str(env);
    ft_executer(cmmarr->cmm[0]->whole_line, envp);
    return (0);
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

int  execute_exit(t_parse_arr *cmmarr, t_env *env)
{
    int pid;
    int status;

	pid = fork();
    status = 0;
	if (pid == 0)
		execute_easy_mode(cmmarr, env);
    else
	{
		globe.cmd = 1;
		waitpid(pid, &status, 0);
	}
	globe.cmd = 0;
    if (WIFEXITED(status))
		globe.g_exit = WEXITSTATUS(status);
    return (globe.g_exit);
}
