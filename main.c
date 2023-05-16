/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:41:17 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/16 15:14:13 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, chr **env)
{
	(void)argc;
	(void)argv;

	if (argc > 1)
	{
		printf("Program does not take any arguments\n");
		return (0);
	}
}
