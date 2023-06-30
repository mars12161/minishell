/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:15:35 by mschaub           #+#    #+#             */
/*   Updated: 2023/06/30 14:31:10 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_handler(int sig);
void	setting_signal(void);
int		change_attr(bool ctrl_chr);

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (globe.in_heredoc == 1)
			ft_putstr_fd("\n", STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setting_signal(void)
{
	signal(SIGINT, sigint_handler);
}

int	change_attr(bool ctrl_chr)
{
	struct termios	termios_p;
	int				attr;

	attr = tcgetattr(STDOUT_FILENO, &termios_p);
	if (attr == -1)
		return (-1);
	if (ctrl_chr)
		termios_p.c_lflag |= ECHOCTL;
	else
		termios_p.c_lflag &= ~(ECHOCTL);
	attr = tcsetattr(STDOUT_FILENO, TCSANOW, &termios_p);
	if (attr == -1)
		return (-1);
	return (0);
}
