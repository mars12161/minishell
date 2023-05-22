/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:17:01 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/19 16:47:25 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

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
		printf("%s\n", input);
	}
	return (0);
}
