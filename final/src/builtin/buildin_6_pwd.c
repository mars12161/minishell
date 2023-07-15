/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_6_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:48:44 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/08 14:21:17 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_parse *node);

int	ft_pwd(t_parse *node)
{
	static char	pwd[PATH_SIZE];
	int			fd;

	fd = ft_redirection_out(node);
	if (node->wline_count > 1)
	{
		ft_error_optimal("pwd: too many args", 1);
		return (1);
	}
	else if (getcwd(pwd, PATH_SIZE))
	{
		ft_putstr_fd(pwd, fd);
		write(fd, "\n", 1);
		if (fd != 1)
			close (fd);
		return (0);
	}
	else
	{
		if (fd != 1)
			close (fd);
		g_exit = 0;
		return (g_exit);
	}
}
