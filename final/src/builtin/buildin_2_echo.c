/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:03:08 by yli               #+#    #+#             */
/*   Updated: 2023/06/30 10:17:03 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(t_parse *node);

static int	ft_check_each_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_n(char *str)
{
	if (str[0] == '-')
	{
		str += 1;
		if (ft_check_each_n(str))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	ft_echo(t_parse *node)
{
	int	i;
	int	flag;
	int	fd;

	i = 0;
	flag = 0;
	fd = ft_redirection_out(node);
	if (node->wline_count == 1)
	{
		ft_putstr_fd("\n", fd);
		return (0);
	}
	if (ft_check_n(node->whole_line[1]))
	{
		i = 1;
		flag = 1;
	}
	while (i++ < node->wline_count - 1)
	{
		ft_putstr_fd(node->whole_line[i], fd);
		if (i == node->wline_count - 1)
			break ;
		ft_putstr_fd(" ", fd);
	}
	if (flag == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}
