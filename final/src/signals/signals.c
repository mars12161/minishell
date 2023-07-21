/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:15:35 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/21 11:13:56 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <sys/ioctl.h>

void	sigint_heredoc(int sig);
void	sigint_process(int sig);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);

void	sigint_heredoc(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_exit = 130;
}

void	sigint_process(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	g_exit = 130;
}

void	sigint_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	g_exit = 131;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
