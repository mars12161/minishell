/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_3_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:03:33 by yli               #+#    #+#             */
/*   Updated: 2023/07/14 12:44:24 by mschaub          ###   ########.fr       */
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

static char	*ft_str_trim_vor(char *wstr, int i)
{
	char	*str;
	int		n;

	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = 0;
	n = 0;
	while (n < i)
	{
		str[n] = wstr[n];
		n++;
	}
	return (str);
}

static void	ft_export_name_check(char *str, t_env *env)
{
	int		i;
	char	*name;

	i = ft_count_size(str, '=');
	if (i == 0)
		return ;
	name = ft_str_trim_vor(str, i);
	ft_unset_core(name, &env);
	free(name);
}

int	ft_export(t_parse *node, t_env **env)
{
	t_env	*export;
	int		i;

	export = NULL;
	i = 1;
	if (node->wline_count == 1)
		return (ft_env(node, env));
	if (ft_check_n_export(node->whole_line[1]))
		return (0);
	else
	{
		while (i < node->wline_count)
		{
			ft_export_name_check(node->whole_line[i], *env);
			if (!ft_check_signal_export(node->whole_line[i]))
			{
				export = new_node_environ(node->whole_line[i]);
				ft_add_tail_env(env, export);
			}
			else if (ft_check_signal_export(node->whole_line[i]) == -1)
				ft_error_optimal("not a valid identifier", 1);
			else if (ft_check_signal_export(node->whole_line[i]) == -2)
				ft_error_optimal("syntax error near unexpected token", 1);
			i++;
		}
	}
	g_exit = 0;
	return (g_exit);
}
