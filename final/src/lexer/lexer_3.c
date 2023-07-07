/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:52:20 by yli               #+#    #+#             */
/*   Updated: 2023/07/07 20:39:55 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*new_node_dq(char *str, t_shell **shell, t_env **env);
char	*new_node_sq(char *str, t_shell **shell, t_env **env);

char	*new_node_dq(char *str, t_shell **shell, t_env **env)
{
	t_shell	*new_node;
	char	*path;
	char	*result;
	int		i;

	new_node = init_shell_node();
	i = 1;
	while (str[i])
	{
		if (str[i] == 34)
			break ;
		i++;
	}
	if (str[i] == 0)
	{
		free(new_node);
		return (new_node_word(str, shell, env));
	}
	i += 1;
	path = ft_substr((char const *)str, 1, i - 2);
	result = ft_parse_dollar_frame(path, *env);
	new_node->input = result;
	str += i;
	new_node->len = ft_strlen(new_node->input);
	if (new_node->input)
		ft_add_tail(shell, new_node, WORD);
	else
		ft_add_tail(shell, new_node, EMPTY);
	return (str);
}

// char	*new_node_dq(char *str, t_shell **shell, t_env **env)
// {
// 	t_shell	*new_node;
// 	char	*path;
// 	char	*result;
// 	int		i;

	// new_node = init_shell_node();
// 	i = 1;
// 	while (str[i])
// 	{
// 		if (str[i] == 34)
// 			break ;
// 		i++;
// 	}
// 	if (str[i] == 0)
// 	{
// 		free(new_node);
// 		return (new_node_word(str, shell, env));
// 	}
// 	i += 1;
// 	path = ft_substr((char const *)str, 1, i - 2);
// 	result = ft_parse_dollar_frame(path, *env);
// 	new_node->input = result;
// 	str += i;
// 	new_node->len = ft_strlen(new_node->input);
// 	if (new_node->input)
// 		ft_add_tail(shell, new_node, WORD);
// 	else
// 		ft_add_tail(shell, new_node, EMPTY);
// 	return (str);
// }

char	*new_node_sq(char *str, t_shell **shell, t_env **env)
{
	t_shell	*new_node;
	int		i;

	new_node = init_shell_node();
	i = 1;
	while (str[i])
	{
		if (str[i] == 39)
			break ;
		i++;
	}
	if (str[i] == 0)
	{
		free(new_node);
		return (new_node_word(str, shell, env));
	}
	i += 1;
	new_node->input = ft_substr((char const *)str, 1, i - 2);
	str += i;
	new_node->len = ft_strlen(new_node->input);
	ft_add_tail(shell, new_node, WORD);
	return (str);
}

// char *parse_quote_in_lexer(char *str, t_shell **shell, t_env **env)
// {
	
// }