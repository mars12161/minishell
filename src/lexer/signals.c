/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:15:35 by mschaub           #+#    #+#             */
/*   Updated: 2023/06/23 16:29:09 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
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
