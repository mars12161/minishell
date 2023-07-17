/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_2_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:03:08 by yli               #+#    #+#             */
/*   Updated: 2023/07/17 10:19:23 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(t_parse *node, t_env **env);

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
	if (str)
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
	return (0);
}

static void	ft_echo_home(t_env **env)
{
	char	*home;
	t_env	*tmp;

	home = NULL;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "HOME=", 5))
		{
			home = ft_strtrim((char const *)tmp->content, "HOME=");
			break ;
		}
		tmp = tmp->next;
	}
	if (home)
		ft_putstr_fd(home, 1);
	else
		ft_putstr_fd("~", 1);
	free(home);
}

static void	echo_output(t_parse *node, int i, int fd, t_env **env)
{
	while (i++ < node->wline_count - 1)
	{
		if (!ft_strcmp(node->whole_line[i], "~"))
			ft_echo_home(env);
		else
		{
			ft_putstr_fd(node->whole_line[i], fd);
			if (i == node->wline_count - 1)
				break ;
			ft_putstr_fd(" ", fd);
		}
	}
}

int	ft_echo(t_parse *node, t_env **env)
{
	int	i;
	int	flag;
	int	fd;

	i = 0;
	flag = 0;
	fd = ft_redirection_out(node);
	ft_echo_help(node, fd);
	if (ft_check_n(node->whole_line[1]))
	{
		i = 1;
		flag = 1;
	}
	echo_output(node, i, fd, env);
	if (flag == 0)
		ft_putstr_fd("\n", fd);
	if (fd != 1)
		close(fd);
	g_exit = 0;
	return (0);
}
