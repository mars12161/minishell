/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:17:08 by yli               #+#    #+#             */
/*   Updated: 2023/07/03 15:14:03 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_parse *node, t_env **env);

int	ft_env(t_parse *node, t_env **env)
{
	int		fd;
	t_env	*temp;

	fd = ft_redirection_out(node);
	temp = *env;
	if (node->wline_count > 1)
	{
		ft_error("env: No such file or directory");
		return (0);
	}
	while (temp)
	{
		ft_putstr_fd(temp->content, fd);
		ft_putstr_fd("\n", fd);
		temp = temp->next;
	}
	return (0);
}
