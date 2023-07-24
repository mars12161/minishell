/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:59:08 by yli               #+#    #+#             */
/*   Updated: 2023/07/24 09:07:36 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit = 0;

static	int	ft_check_readline_in_loop(void)
{
	write(STDERR_FILENO, "exit\n", 5);
	g_exit = 130;
	return (-1);
}

static int	ft_empty_cmmarr(char *str, t_shell *shell)
{
	free(str);
	free_shell(&shell);
	return (0);
}

/*static	int	input_loop_2(t_env *env, t_shell *shell,
				t_parse_arr *cmmarr, char *str)
{
	if (g_exit != 130)
	{
		if (!(check_buildin(cmmarr->cmm[0]->command)))
			return (buildin_easy_mode(&shell, cmmarr, env, str));
		signal(SIGQUIT, sigquit_handler);
		return (execute_exit(shell, cmmarr, env, str));
	}
	return (0);
}*/
// not sure about return (0);

/*static int	input_loop_2(t_env *env, t_shell *shell,
				t_parse_arr *cmmarr, char *str)
{
	if (!cmmarr)
		return (ft_empty_cmmarr(str, shell));
	if (cmmarr->size == 1)
	{
		if (g_exit != 130)
		{
			if (!(check_buildin(cmmarr->cmm[0]->command)))
				return (buildin_easy_mode(&shell, cmmarr, env, str));
			signal(SIGQUIT, sigquit_handler);
			return (execute_exit(shell, cmmarr, env, str));
		}
	}
	if (g_exit != 130)
	{
		init_pipex(cmmarr, env);
		g_exit = 0;
	}
	unlink("heredoc.txt");
	free_all_in_loop(&shell, cmmarr, str);
}

static int	input_loop(t_env *env)
{
	t_shell		*shell;
	t_parse_arr	*cmmarr;
	char		*str;

	str = readline("[minishell:]");
	if (!str)
		return (ft_check_readline_in_loop());
	else if (str[0] != '\0')
		add_history(str);
	if (g_exit == 130 && !ft_strncmp(str, "echo $?", 7))
	{
		printf("%d\n", g_exit);
		return (1);
	}
	else if (g_exit != 127)
		g_exit = 0;
	shell = NULL;
	shell = fill_shell(str, shell, &env);
	cmmarr = parse_array_create(shell, env);
	input_loop_2(env, shell, cmmarr, str);
	return (1);
}*/

int	input_loop(t_env *env)
{
	t_shell		*shell;
	t_parse_arr	*cmmarr;
	char		*str;

	str = readline("[minishell:]");
	if (!str)
		return (ft_check_readline_in_loop());
	else if (str[0] != '\0')
		add_history(str);
	if (g_exit == 130 && !ft_strncmp(str, "echo $?", 7))
	{
		printf("%d\n", g_exit);
		return (1);
	}
	else if (g_exit != 127 && g_exit != 131)
		g_exit = 0;
	shell = NULL;
	shell = fill_shell(str, shell, &env);
	cmmarr = parse_array_create(shell, env);
	if (!cmmarr)
		return (ft_empty_cmmarr(str, shell));
	if (cmmarr->size == 1)
	{
		if (g_exit != 130)
		{
			if (!(check_buildin(cmmarr->cmm[0]->command)))
				return (buildin_easy_mode(&shell, cmmarr, env, str));
			signal(SIGQUIT, sigquit_handler);
			return (execute_exit(shell, cmmarr, env, str));
		}
	}
	if (g_exit != 130)
	{
		init_pipex(cmmarr, env);
		g_exit = 0;
	}
	unlink("heredoc.txt");
	free_all_in_loop(&shell, cmmarr, str);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		check;

	(void)argv;
	if (argc > 1)
	{
		ft_error_optimal("Program does not take any arguments\n", 126);
		return (1);
	}
	check = 0;
	env = NULL;
	env = init_env(envp, env);
	while (42)
	{
		init_signals();
		check = input_loop(env);
		if (check < 0)
			break ;
		signal(SIGQUIT, SIG_IGN);
	}
	free_env(&env);
	rl_clear_history();
	return (g_exit);
}
