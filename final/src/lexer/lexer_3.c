/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:52:20 by yli               #+#    #+#             */
/*   Updated: 2023/07/12 16:38:26 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *ft_parse_quote_rules(char *str, t_env **env);
char	*new_node_quote(char *str, t_shell **shell, t_env **env);

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

// char	*new_node_sq(char *str, t_shell **shell, t_env **env)
// {
// 	t_shell	*new_node;
// 	int		i;

// 	new_node = init_shell_node();
// 	i = 1;
// 	while (str[i])
// 	{
// 		if (str[i] == 39)
// 			break ;
// 		i++;
// 	}
// 	if (str[i] == 0)
// 	{
// 		free(new_node);
// 		return (new_node_word(str, shell, env));
// 	}
// 	i += 1;
// 	new_node->input = ft_substr((char const *)str, 1, i - 2);
// 	str += i;
// 	new_node->len = ft_strlen(new_node->input);
// 	ft_add_tail(shell, new_node, WORD);
// 	return (str);
// }

static char *ft_parse_quote_rules_substr(char *str, int size, t_env **env)
{
    char *sub1;
    char *sub2;

    sub1 = ft_substr(str, 1, size);
    printf("sub1: %s\n", sub1);
    sub2 = ft_substr(str, size + 1, ft_strlen(str) - size -1);
    printf("sub2: %s\n", sub2);
    return (ft_parse_word_rules_strjoin(sub1, sub2, env));
}

char *ft_parse_quote_rules(char *str, t_env **env)
{
    // int i;
    // int j;
    int signal;
    char *result;

    signal = str[0]; //not consider the '
    if (ft_count_size_lexer(str, signal, 0) == (int)ft_strlen(str))
        return (ft_parse_dollar_frame(str, *env));
	//j = ft_count_size_lexer(str, signal, 1);
	else if (ft_count_size_lexer(str, signal, 1) == ((int)ft_strlen(str) - 1))
	{
		result = ft_substr(str, 1, ft_count_size_lexer(str, signal, 1));
		return (ft_parse_dollar_frame(result, *env));
	}
    result = ft_parse_quote_rules_substr(str, ft_count_size_lexer(str, signal, 0), env);
    if ((ft_count_size_lexer(str, 34, 0)) == (ft_count_size_lexer(str, 39, 0)) && (ft_count_size_lexer(str, 34, 0)) == (int)ft_strlen(str))
        return (result);
    else
        return (ft_parse_word_rules(result, env));
}

char	*new_node_quote(char *str, t_shell **shell, t_env **env)
{
	t_shell	*new_node;
	char *original;
	int		i;

	new_node = init_shell_node();
	i = ft_check_size_str_for_node(str);
	original = ft_substr((char const *)str, 0, i);
	printf("original in new node quote: %s\n", original);
	new_node->input = ft_parse_quote_rules(str, env);
	printf("new_node->input in new node quote: %s\n", new_node->input);
	str += i;
	printf("str in new node quote after trim1: %s\n", str);
	new_node->len = ft_strlen(new_node->input);
	if (new_node->input)
		ft_add_tail(shell, new_node, WORD);
	else
		ft_add_tail(shell, new_node, EMPTY);
	return (str);
}