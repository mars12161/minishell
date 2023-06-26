/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:01:13 by yli               #+#    #+#             */
/*   Updated: 2023/06/26 17:20:46 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static  int input_loop(t_env *env)
{
    t_shell *shell;
    t_parse_arr *cmmarr;
    char *str;

	str = readline("[minishell:]");
	//change_attr(false);
    if (!str)
	{
		write(STDERR_FILENO, "exit\n", 5);
		change_attr(true);
		return (1);
	}
	else if (str[0] == '\0')
	{}
	else
		add_history(str);
    shell = NULL;
    shell = fill_shell(str, shell, &env);
	//print_shell(shell);
    cmmarr = parse_array_create(shell, env);
    //print_parse_arr(cmmarr);
    if (!cmmarr)
    {
        free(str);
        free_shell(&shell);
        return (-1);
    }
    if (cmmarr->size == 1 && !(check_buildin(cmmarr->cmm[0]->command)))
        return (buildin_easy_mode(&shell, cmmarr, env)); //todo
    return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		printf("Program does not take any arguments\n");
		return (1);
	}
	t_env	*env;
    int check;

    check = 0;
	(void)argc;
	(void)argv;
	env = NULL;
	env = init_env(envp, env);
	signal(SIGQUIT, SIG_IGN);
	change_attr(false);
	while (42)
	{
		signal(SIGINT, sigint_handler);
		check = input_loop(env);
		if (check == 1)
			break;
	}
	change_attr(true);
	// free everything
}
