/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:17:01 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/17 11:55:16 by mschaub          ###   ########.fr       */
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

	while (42)
	{
		input = readline("=> ");
		change_attr(true);
		signal(SIGINT, sigint_handler);
		if (!ft_strcmp(input, "exit"))
			return (1);
		if (input == NULL)
		{
			if (isatty(STDERR_FILENO))
				write(STDERR_FILENO, "exit\n", 5);
			change_attr(false);
			break;
		}
		printf("%s\n", input);
	}
	return (0);
}

int	main(void)
{
	minishell_loop();
}