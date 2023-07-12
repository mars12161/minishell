/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:21:54 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/12 16:38:32 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char		*new_node_word(char *str, t_shell **shell, t_env **env);
t_shell		*fill_shell(char *str, t_shell *shell, t_env **env);

char	*new_node_word(char *str, t_shell **shell, t_env **env) // for WORD
{
	t_shell	*new_node;
	char *original;
	int		check;
	int		i;
	
	new_node = init_shell_node();
	i = ft_check_size_str_for_node(str);
	original = ft_substr((char const *)str, 0, i);
	new_node->input = ft_parse_word_rules(original, env);
	str += i;
	printf("str in new node after trim0: %s\n", str);
	new_node->len = ft_strlen(new_node->input);
	check = check_word_or_path(*shell);
	if (check == 1)
		ft_add_tail(shell, new_node, INFILEPATH);
	else if (check == 2)
		ft_add_tail(shell, new_node, OUTFILEPATH);
	else if(new_node->input)
		ft_add_tail(shell, new_node, WORD);
	else
		ft_add_tail(shell, new_node, EMPTY);
	return (str);
}

static char	*new_node_space(char *str, t_shell **shell)
{
	t_shell	*new_node;
	int		i;
	int		space;

	new_node = init_shell_node();
	i = 0;
	space = 0;
	while (str[i])
	{
		if (str[i] == 32)
			space++;
		if (str[i] == 32 && str[i + 1] != 32)
			break ;
		i++;
	}
	new_node->input = ft_substr((char const *)str, 0, space);
	str += space;
	new_node->len = ft_strlen(new_node->input);
	ft_add_tail(shell, new_node, SPA);
	return (str);
}
char *ft_parse_quote_rules(char *str, t_env **env);

t_shell	*fill_shell(char *str, t_shell *shell, t_env **env)
{
	while (*str == ' ')
		str++;
	while (*str)
	{
		if (*str == ' ')
			str = new_node_space(str, &shell);
		else if (*str == '|')
			str = new_node_pipe(str, &shell);
		else if (*str == '\'' || *str == '\"')
			str = new_node_quote(str, &shell, env);
		else if (*str == '<')
			str = new_node_red(str, &shell, 60);
		else if (*str == '>')
			str = new_node_red(str, &shell, 62);
		else if (*str == '$')
			str = new_node_env(str, &shell, env);
		else
			str = new_node_word(str, &shell, env);
	}
	return (shell);
}
