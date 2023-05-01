/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:23:25 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/01 17:25:54 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	minishell_loop(void)
{
	char *input;
	while (42)
	{
		input = readline("=> ");
		if (!ft_strcmp(input, "exit"))
			return (1);
		printf("%s\n", input);
	}
}