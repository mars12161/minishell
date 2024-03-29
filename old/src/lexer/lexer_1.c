/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:21:54 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/19 16:22:02 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *new_node_WORD(char *str, t_shell **shell, t_env **env);
t_shell *fill_shell(char *str, t_shell *shell, t_env **env);

static int new_node_WORD(char *str)
{
    int i;
    int j;

    
    
    
}
char *new_node_WORD(char *str, t_shell **shell, t_env **env) // for WORD
{
    t_shell *new_node;
    int check;


    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);

    while (str[i])
    {
        if (str[i] >= 33 && str[i] <= 126)
            j++;
        if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\t'))
            break ;
        i++;
    }
    new_node->input = ft_parse_dollar_frame(ft_substr((char const *)str, 0, j), *env);
    str += j;
    new_node->len = ft_strlen(new_node->input);
    check = check_word_or_path(*shell);
    if (check == 1)
        ft_add_tail(shell, new_node, INFILEPATH);
    else if (check == 2)
        ft_add_tail(shell, new_node, OUTFILEPATH);
    else
        ft_add_tail(shell, new_node, WORD);
    return (str);
}

static char *new_node_SPACE(char *str, t_shell **shell)
{
    t_shell *new_node;
    int i;
    int space;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
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

t_shell *fill_shell(char *str, t_shell *shell, t_env **env)
{
	while (*str == ' ')
		str++;
	while (*str)
	{
		if (*str == ' ')
			str = new_node_SPACE(str, &shell);
		else if (*str == '|')
			str = new_node_PIPE(str, &shell);
		else if (*str == '\"')
			str = new_node_DQ(str, &shell, env);
		else if (*str == '\'')
			str = new_node_SQ(str, &shell, env);
		else if (*str == '<')
			str = new_node_RED(str, &shell, 60);
		else if (*str == '>')
			str = new_node_RED(str, &shell, 62);
		else if (*str == '$')
			str = new_node_ENV(str, &shell, env);
		else
			str = new_node_WORD(str, &shell, env);
	}
	return (shell);
}