/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:15:35 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/09 17:30:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_handler(int sig);
void	sigquit_handler(int sig);

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (!g_globe.cmd)
		{
			if (g_globe.in_heredoc)
				g_globe.stop_heredoc = 1;
			ft_putstr_fd("\n", STDERR_FILENO);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (!g_globe.in_heredoc && g_globe.cmd)
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
