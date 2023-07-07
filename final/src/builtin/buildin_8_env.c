/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_8_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:17:08 by yli               #+#    #+#             */
/*   Updated: 2023/07/07 16:22:08 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_parse *node, t_env **env);

int	ft_env(t_parse *node, t_env **env)
{
	int		fd;
	t_env	*temp;

	//print_env(env);
	fd = ft_redirection_out(node);
	temp = *env;
	if (node->wline_count > 1)
	{
		ft_error_optimal("env: No such file or directory", 127);
		if (fd != 1)
			close(fd);
		return (globe.g_exit);
	}
	while (temp)
	{
		ft_putstr_fd(temp->content, fd);
		ft_putstr_fd("\n", fd);
		temp = temp->next;
	}
	if (fd != 1)
		close(fd);
	return (0);
}
