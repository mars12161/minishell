/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_3_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:03:33 by yli               #+#    #+#             */
/*   Updated: 2023/07/05 23:01:09 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_export(t_parse *node, t_env **env);

static int	ft_check_n_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_signal_export(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (-1);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	while (j < i)
	{
		if (str[j] == '!' || str[j] == '@' || str[j] == '#'
			|| str[j] == '%' || str[j] == '+' || str[j] == '-' || str[j] == '/')
			return (-1);
		else if (str[j] == '(' || str[j] == ')')
			return (-2);
		j++;
	}
	return (0);
}

int	ft_export(t_parse *node, t_env **env)
{
	t_env	*export;

	export = NULL;
	if (node->wline_count == 1)
		return (ft_env(node, env));
	if (ft_check_n_export(node->whole_line[1]))
		return (0);
	else
	{
		if (!ft_check_signal_export(node->whole_line[1]))
		{
			export = new_node_ENV(node->whole_line[1]);
			ft_add_tail_env(env, export);
		}
		else if (ft_check_signal_export(node->whole_line[1]) == -1)
		{
			ft_error_optimal("not a valid identifier", 1);
			return (globe.g_exit);
		}
		else if (ft_check_signal_export(node->whole_line[1]) == -2)
		{
			ft_error_optimal("syntax error near unexpected token", 1);
			return (globe.g_exit);
		}
	}
	return (0);
}
