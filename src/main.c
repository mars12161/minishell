/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:16:01 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/01 15:49:06 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;

	//(void)argc;
	//(void)argv;
//	shell.in = dup(STDIN);
//	shell.out = dup(STDOUT);
//	shell.exit = 0;
//	shell.result = 0; //
//	shell.no_exec = 0;
//	init_fds(&shell);
	//something for envp
	//
	//
	char	*input;
	while (42)
	{
		input = readline("=> ");
		if (!ft_strcmp(input, "exit"))
			exit(1);
		printf("%s\n", input);
	}

//	while(!shell.exit)
//	{
//	}
//	free_env(mini.envp);
//	free_env(//);
//	return (mini.result);
}

