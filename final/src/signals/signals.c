/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:15:35 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/12 15:55:28 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_handler(int sig);
void	sigquit_handler(int sig);

void	sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		g_exit = 150;
	}
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exit != 250)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_exit == 250)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			return ;
		}
	}
}

void	sigquit_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
