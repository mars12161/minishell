/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:17:01 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/19 11:17:03 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

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
/*

int	main(void)
{
	minishell_loop();
}*/
