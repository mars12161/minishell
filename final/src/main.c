/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:34:04 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/09 15:05:31 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_global g_globe;

static  int input_loop(t_env *env)
{
	t_shell		*shell;
	t_parse_arr	*cmmarr;
	char		*str;

	str = readline("[minishell:]");
	if (!str)
	{
		write(STDERR_FILENO, "exit\n", 5);
		return (-1);
	}
	else if (str[0] == '\0')
	{
	}
	else
		add_history(str);
	shell = NULL;
	shell = fill_shell(str, shell, &env);
    cmmarr = parse_array_create(shell, env);
    if (!cmmarr)
    {
        free(str);
        free_shell(&shell);
        return (0);
    } 
    if (cmmarr->size == 1)
	{
		if (!(check_buildin(cmmarr->cmm[0]->command)))
			return (buildin_easy_mode(&shell, cmmarr, env, str));
		signal(SIGQUIT, sigquit_handler);
		return (execute_exit(shell, cmmarr, env, str));
	}
	init_pipex(cmmarr, env);
	unlink("heredoc.txt");
	free_all_in_loop(&shell, cmmarr, str);
	return (1);
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
	//change_attr(false);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	while (42)
	{
		check = input_loop(env);
		if (check < 0)
			break ;
		signal(SIGQUIT, SIG_IGN);
	}
	free_env(&env);
	rl_clear_history();
	return (g_globe.g_exit);
}
