/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:48:44 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/17 10:05:02 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_buildin(char *str);
int	ft_redirection_out(t_parse *node);
int	buildin_easy_mode(t_shell **shell, t_parse_arr *cmmarr, 
		t_env *env, char *str);
int	ft_strcmpn(char *str1, char *str2, int size);

int	check_buildin(char *str)
{
	if (!ft_strcmpn(str, "echo", 4) || !ft_strcmpn(str, "cd", 2)
		|| !ft_strcmpn(str, "pwd", 3) || !ft_strcmpn(str, "export", 6)
		|| !ft_strcmpn(str, "unset", 5) || !ft_strcmpn(str, "env", 3)
		|| !ft_strcmpn(str, "exit", 4))
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

int	ft_strcmpn(char *str1, char *str2, int size)
{
	int	i;

	i = ft_strlen(str1);
	if (i != size)
		return (1);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtin(t_parse *node, t_env **env)
{
	if (!ft_strcmpn(node->command, "echo", 4))
		return (ft_echo(node, env));
	else if (!ft_strcmpn(node->command, "cd", 2))
		return (ft_cd(node, env));
	else if (!ft_strcmpn(node->command, "pwd", 3))
		return (ft_pwd(node));
	else if (!ft_strcmpn(node->command, "env", 3))
		return (ft_env(node, env));
	else if (!ft_strcmpn(node->command, "export", 6))
		return (ft_export(node, env));
	else if (!ft_strcmpn(node->command, "unset", 5))
		return (ft_unset(node, env));
	else if (!ft_strcmpn(node->command, "exit", 4))
		return (ft_exit(node));
	return (0);
}

/* TODO
 * if (g_exit)
 * 	free_all(shell, cmarr->cmm[0], &env)
 *
 */
int	buildin_easy_mode(t_shell **shell, t_parse_arr *cmmarr, 
		t_env *env, char *str)
{
	int	check;

	if (cmmarr->cmm[0]->redirection_out)
		ft_redirection_out(cmmarr->cmm[0]);
	check = exec_builtin(cmmarr->cmm[0], &env);
	free_all_in_loop(shell, cmmarr, str);
	return (check);
}

// int	buildin_easy_mode(t_shell **shell, t_parse_arr *cmmarr, 
// 		t_env *env, char *str)
// {
// 	if (cmmarr->cmm[0]->redirection_out)
// 		ft_redirection_out(cmmarr->cmm[0]);
// 	exec_builtin(cmmarr->cmm[0], &env);
// 	free_all_in_loop(shell, cmmarr, str);
// 	printf("g_exit: %d\n", g_exit);
// 	return (g_exit);
// }
