/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:21:54 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/24 12:02:45 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char		*new_node_word(char *str, t_shell **shell, t_env **env);
t_shell		*fill_shell(char *str, t_shell *shell, t_env **env);
t_shell		*init_shell_node(void);

char	*new_node_word(char *str, t_shell **shell, t_env **env)
{
	t_shell	*new_node;
	char	*original;
	int		check;
	int		i;

	new_node = init_shell_node();
	i = ft_i_start_from_word(str, 0);
	original = ft_substr((char const *)str, 0, i);
	new_node->input = ft_parse_original_from_word(original, env);
	free(original);
	str += i;
	new_node->len = ft_strlen(new_node->input);
	check = check_word_or_path(*shell);
	if (check == 1)
		ft_add_tail(shell, new_node, INFILEPATH);
	else if (check == 2)
		ft_add_tail(shell, new_node, OUTFILEPATH);
	else if (new_node->input)
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
		else if (*str == '\'')
			str = new_node_sq(str, &shell, env);
		else if (*str == '\"')
			str = new_node_dq(str, &shell, env);
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

t_shell	*init_shell_node(void)
{
	t_shell	*new_node;

	new_node = NULL;
	new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
	return (new_node);
}
