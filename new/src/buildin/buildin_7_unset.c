/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:17:01 by yli               #+#    #+#             */
/*   Updated: 2023/06/21 18:17:03 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_unset(t_parse *node, t_env **env);

static void	del_node(t_env **env,t_env *node)
{
	t_env	*temp;

	if (*env == node)
	{
		*env = (*env)->next;
		free(node);
		return ;
	}
	temp = *env;
	while (temp->next && temp->next != node)
		temp = temp->next;
	if (temp->next == node)
	{
		temp->next = node->next;
		free(node);
	}
}

int ft_unset(t_parse *node, t_env **env)
{
    t_env *temp;

    temp = *env;
    while (temp)
    {
		if (ft_count_size(node->whole_line[1], '='))
			ft_error("invalid parameter name"); //free something later  g_exit == 1
        if (!strncmp(temp->content, node->whole_line[1], ft_strlen(node->whole_line[1])))
        {
            del_node(env,temp);
            return (0);
        }
        temp = temp->next;
    }
    return (0);
}