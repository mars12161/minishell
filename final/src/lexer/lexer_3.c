/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:52:20 by yli               #+#    #+#             */
/*   Updated: 2023/07/13 21:18:20 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*new_node_dq(char *str, t_shell **shell, t_env **env);
char	*new_node_sq(char *str, t_shell **shell, t_env **env);

char	*new_node_dq(char *str, t_shell **shell, t_env **env)
{
	t_shell	*new_node;
	char	*path;
	int		i;

	new_node = init_shell_node();
	i = ft_i_start_from_dq(str, 0);
	path = ft_substr(str, 0, i);
	new_node->input = ft_parse_original_from_dq(path, env);
	//free(path); not sure
	str += i;
	new_node->len = ft_strlen(new_node->input);
	if (new_node->input)
		ft_add_tail(shell, new_node, WORD);
	else
		ft_add_tail(shell, new_node, EMPTY);
	return (str);
}

char	*new_node_sq(char *str, t_shell **shell, t_env **env)
{
	t_shell	*new_node;
	char *path;
	int		i;

	new_node = init_shell_node();
	i = ft_i_start_from_sq(str, 0);
	path = ft_substr(str, 0, i);
	new_node->input = ft_parse_original_from_sq(path, env);
	str += i;
	new_node->len = ft_strlen(new_node->input);
	if (new_node->input)
		ft_add_tail(shell, new_node, WORD);
	else
		ft_add_tail(shell, new_node, EMPTY);
	return (str);
}