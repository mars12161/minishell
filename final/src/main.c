#include "../inc/minishell.h"

t_global globe;

static  int input_loop(t_env *env)
{
	t_shell		*shell;
	t_parse_arr	*cmmarr;
	char		*str;

	str = readline("[minishell:]");
	change_attr(false);
	if (!str)
	{
		write(STDERR_FILENO, "exit\n", 5);
		change_attr(true);
		return (-1);
	}
	else if (str[0] == '\0')
	{
	}
	else
		add_history(str);
	shell = NULL;
	shell = fill_shell(str, shell, &env);
	//print_shell(shell);
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
			return (buildin_easy_mode(&shell, cmmarr, env));
		return (execute_exit(cmmarr, env));
	}
	init_pipex(cmmarr, env);
	unlink("heredoc.txt");
	free_all(&shell, cmmarr);
	free(str);
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
	signal(SIGQUIT, SIG_IGN);
	change_attr(false);
	while (42)
	{
		signal(SIGINT, sigint_handler);
		check = input_loop(env);
		if (check < 0)
			break ;
	}
	free_env(&env);
	rl_clear_history();
	return (globe.g_exit);
}
