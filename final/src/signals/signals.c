/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:15:35 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/08 13:40:38 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_handler(int sig);
int		change_attr(bool ctrl_chr);

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
			return ;
	}
}

/*int	change_attr(bool ctrl_chr)
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
}*/
