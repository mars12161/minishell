
#include "../../inc/minishell.h"

int	check_buildin(char *str);
int	ft_redirection_out(t_parse *node);
int	buildin_easy_mode(t_shell **shell, t_parse_arr *cmmarr, t_env *env);

int	check_buildin(char *str)
{
	if (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2)
		|| !ft_strncmp(str, "pwd", 3) || !ft_strncmp(str, "export", 6)
		|| !ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "env", 3)
		|| !ft_strncmp(str, "exit", 4))
		return (0);
	return (1);
}

/* Check later */
int	ft_redirection_out(t_parse *node)
{
	int	outfile_fd;

	outfile_fd = 1;
	if (node->redirection_out == 1)
		outfile_fd = open(node->outfilepath,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->redirection_out == 2)
		outfile_fd = open(node->outfilepath,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (outfile_fd == -1)
		ft_error("open outfile failed");
	return (outfile_fd);
}

int	exec_builtin(t_parse *node, t_env **env)
{
	if (!ft_strncmp(node->command, "echo", 4))
		return (ft_echo(node, env));
	else if (!ft_strncmp(node->command, "cd", 2))
		return (ft_cd(node, env));
	else if (!ft_strncmp(node->command, "pwd", 3))
		return (ft_pwd(node));
	else if (!ft_strncmp(node->command, "env", 3))
		return (ft_env(node, env));
	else if (!ft_strncmp(node->command, "export", 6))
		return (ft_export(node, env));
	else if (!ft_strncmp(node->command, "unset", 5))
		return (ft_unset(node, env));
	else if (!ft_strncmp(node->command, "exit", 4))
		return (ft_exit());
	return (0);
}

/* TODO
 * if (g_exit)
 * 	free_all(shell, cmarr->cmm[0], &env)
 *
 */
int	buildin_easy_mode(t_shell **shell, t_parse_arr *cmmarr, t_env *env)
{
	if (cmmarr->cmm[0]->redirection_out)
		ft_redirection_out(cmmarr->cmm[0]);
	exec_builtin(cmmarr->cmm[0], &env);
	return (globe.g_exit);
}
