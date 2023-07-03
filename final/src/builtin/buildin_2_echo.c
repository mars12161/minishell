/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_2_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:03:08 by yli               #+#    #+#             */
/*   Updated: 2023/07/03 16:31:53 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(t_parse *node);

static int	ft_check_each_n(char *str) //return 1 all n, return 0 nnnann
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

static int	ft_check_n(char *str) //return 1 -nnnnn return 0 nnnn or -nnnann
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
		if (fd != 1)
			close(fd);
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
	if (fd != 1)
		close(fd);
	return (0);
}
