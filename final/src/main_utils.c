/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:07:46 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/24 10:08:46 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_readline_in_loop(void)
{
	write(STDERR_FILENO, "exit\n", 5);
	g_exit = 130;
	return (-1);
}

int	ft_empty_cmmarr(char *str, t_shell *shell)
{
	free(str);
	free_shell(&shell);
	return (0);
}

int	err_heredoc(void)
{
	printf("%d\n", g_exit);
	g_exit = 0;
	return (0);
}
