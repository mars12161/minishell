/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_6_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:55 by yli               #+#    #+#             */
/*   Updated: 2023/07/06 16:31:19 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_parse *node);

int	ft_pwd(t_parse *node)
{
	static char	pwd[PATH_SIZE];
	int			fd;

	fd = ft_redirection_out(node);
	if (getcwd(pwd, PATH_SIZE))
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
	}
	return (-1);
}
