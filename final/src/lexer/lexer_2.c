/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:54 by yli               #+#    #+#             */
/*   Updated: 2023/07/19 20:18:19 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*new_node_env(char *str, t_shell **shell, t_env **env);
char	*new_node_pipe(char *str, t_shell **shell);
char	*new_node_red_2(char *str, t_shell **shell, int c);
char	*new_node_red(char *str, t_shell **shell, int c);

char	*new_node_env(char *str, t_shell **shell, t_env **env)
{
	t_shell	*new_node;
	char	*path;
	char	*result;
	int		i;
	int		j;

	new_node = init_shell_node();
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] >= 33 && str[i] <= 126)
			j++;
		if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' '
				|| str[i + 1] == '\t'))
			break ;
		i++;
	}
	path = ft_substr((char const *)str, 0, j);
	result = ft_parse_dollar_frame(path, *env, 0);
	free(path);
	new_node->input = result;
	str += j;
	if (new_node->input)
		new_node->len = ft_strlen(new_node->input);
	else
		new_node->len = 0;
	if (new_node->input)
		ft_add_tail(shell, new_node, WORD);
	else
		ft_add_tail(shell, new_node, EMPTY);
	return (str);
}

char	*new_node_pipe(char *str, t_shell **shell)
{
	t_shell	*new_node;

	new_node = init_shell_node();
	new_node->input = ft_substr((char const *)str, 0, 1);
	str += 1;
	new_node->len = ft_strlen(new_node->input);
	ft_add_tail(shell, new_node, PIPE);
	return (str);
}

char	*new_node_red_2(char *str, t_shell **shell, int c)
{
	t_shell	*new_node;
	int		i;
	int		flag;

	new_node = init_shell_node();
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == c)
			flag++;
		i++;
	}
	new_node->input = ft_substr((char const *)str, 0, flag);
	str += flag;
	new_node->len = ft_strlen(new_node->input);
	if (c == 60)
		ft_add_tail(shell, new_node, HEREDOC);
	else if (c == 62)
		ft_add_tail(shell, new_node, APP_M);
	return (str);
}

char	*new_node_red(char *str, t_shell **shell, int c)
{
	t_shell	*new_node;
	int		i;
	int		flag;

	new_node = init_shell_node();
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == c)
			flag++;
		if (str[i] != c)
			break ;
		i++;
	}
	if (flag == 2)
		return (new_node_red_2(str, shell, c));
	else if (flag > 2)
		return ("error");
	new_node->input = ft_substr((char const *)str, 0, 1);
	str += 1;
	new_node->len = ft_strlen(new_node->input);
	if (c == 60)
		ft_add_tail(shell, new_node, REDIRECT_IN);
	else if (c == 62)
		ft_add_tail(shell, new_node, REDIRECT_OUT);
	return (str);
}
