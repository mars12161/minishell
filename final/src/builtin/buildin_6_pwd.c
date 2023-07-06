/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:55 by yli               #+#    #+#             */
/*   Updated: 2023/07/06 17:50:36 by mschaub          ###   ########.fr       */
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
		return (0);
	}
	else
	{
		globe.g_exit = 0;
		return (-1);
	}
}
