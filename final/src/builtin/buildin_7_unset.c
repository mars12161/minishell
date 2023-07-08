/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_7_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:17:01 by yli               #+#    #+#             */
/*   Updated: 2023/07/08 14:31:18 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_unset_core(char *str, t_env **env);
int		ft_unset(t_parse *node, t_env **env);

static void	del_node(t_env **env, t_env *node)
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

void	ft_unset_core(char *str, t_env **env)
{
	t_env	*temp;
	t_env	*head;

	temp = *env;
	head = *env;
	while (temp)
	{
		if (!strncmp(temp->content, str, ft_strlen(str)))
		{
			del_node(env, temp);
			return ;
		}
		temp = temp->next;
	}
	temp = head;
}

int	ft_unset(t_parse *node, t_env **env)
{
	int	i;

	i = 1;
	if (!node->whole_line[1])
		return (0);
	while (i < node->wline_count)
	{
		ft_unset_core(node->whole_line[i], env);
		i++;
	}
	return (0);
}
