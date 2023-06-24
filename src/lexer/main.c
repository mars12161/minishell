/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:01:13 by yli               #+#    #+#             */
/*   Updated: 2023/06/24 14:24:09 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	}
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
	t_env	*env;
    int check;

    check = 0;
	(void)argc;
	(void)argv;
	env = NULL;
	env = init_env(envp, env);
	signal(SIGQUIT, SIG_IGN);
	change_attr(false);
	while (!check)
	{
		signal(SIGINT, sigint_handler);
		check = input_loop(env);
	}
	change_attr(true);
	// free everything
}
