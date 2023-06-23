/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:01:13 by yli               #+#    #+#             */
/*   Updated: 2023/06/23 12:41:38 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  int input_loop(t_env *env)
{
    t_shell *shell;
    t_parse_arr *cmmarr;
    char *str;

	str = readline("[minishell:]");
    add_history(str);
    if (!str)
        return (0);
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

	(void)argc;
	(void)argv;
	env = NULL;
	env = init_env(envp, env);
	while (42)
		input_loop(env);
}
