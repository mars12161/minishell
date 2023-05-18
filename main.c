/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:41:17 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/18 14:51:21 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	minishell_loop(void)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		signal(SIGINT, sigint_handler);
		change_attr(false);
		input = readline("=> ");
		if (!input)
		{
			write(STDERR_FILENO, "exit\n", 5);
			change_attr(true);
			break ;
		}
		// process input
		printf("%s\n", input);
	}
	return (0);
}

int	main(int argc, char **argv, chr **env)
{
	(void)argc;
	(void)argv;

	if (argc > 1)
	{
		printf("Program does not take any arguments\n");
		return (0);
	}
	minishell_loop();
}
