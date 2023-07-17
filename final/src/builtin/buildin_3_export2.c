/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_3_export2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:30:06 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/17 10:33:55 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_loop(int i, t_parse *node, t_env **env, t_env *export)
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
