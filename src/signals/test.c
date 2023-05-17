/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:17:01 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/16 17:20:11 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>

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
		signal(SIGINT, sigint_handler);
		//signal(SIGQUIT, ft_sighandler);
		if (!ft_strcmp(input, "exit"))
			return (1);
		printf("%s\n", input);
	}
}

int	main(void)
{
	minishell_loop();
}