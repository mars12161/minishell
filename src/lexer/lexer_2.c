/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:54 by yli               #+#    #+#             */
/*   Updated: 2023/06/23 12:35:58 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *new_node_ENV(char *str, t_shell **shell, t_env **env);
char *new_node_PIPE(char *str, t_shell **shell);
char *new_node_RED_2(char *str, t_shell **shell, int c);
char *new_node_RED(char *str, t_shell **shell, int c);

char *new_node_ENV(char *str, t_shell **shell, t_env **env) //$
{
    t_shell *new_node;
    char *path;
    char *result;
    int i;
    int j;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] >= 33 && str[i] <= 126)
            j++;
        if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\t'))
            break ;
        i++;
    }
    path = ft_substr((char const *)str, 1, j);
    result = ft_expand(str, env);
    new_node->input = result;
    free(path);
    str += j;
	printf("%s\n", new_node->input);
    new_node->len = ft_strlen(new_node->input);
    ft_add_tail(shell, new_node, WORD);
    return (str);
}

char *new_node_PIPE(char *str, t_shell **shell)
{
    t_shell *new_node;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    new_node->input = ft_substr((char const *)str, 0, 1);
    str += 1;
    new_node->len = ft_strlen(new_node->input);
    ft_add_tail(shell, new_node, PIPE);
    return (str);
}

char *new_node_RED_2(char *str, t_shell **shell, int c)
{
    t_shell *new_node;
    int i;
    int flag;

    new_node = NULL;
    i = 0;
    flag = 0;
    while(str[i])
    {
        if (str[i] == c)
            flag++;
        i++;
    }
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    new_node->input = ft_substr((char const *)str, 0, flag);
    str += flag;
    new_node->len = ft_strlen(new_node->input);
    if (c == 60)
        ft_add_tail(shell, new_node, HEREDOC);
    else if (c == 62)
        ft_add_tail(shell, new_node, APP_M);
    return (str);
}

char *new_node_RED(char *str, t_shell **shell, int c)
{
    t_shell *new_node;
    int i;
    int flag;

    new_node = NULL;
    i = 0;
    flag = 0;
    while(str[i])
    {
        if (str[i] == c)
            flag++;
        if (str[i] != c)
            break ;
        i++;
    }
    if (flag == 2)
        return (new_node_RED_2(str, shell, c));
    else if (flag > 2)
        return ("error"); //todo later
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    new_node->input = ft_substr((char const *)str, 0, 1);
    str += 1;
    new_node->len = ft_strlen(new_node->input);
    if (c == 60)
        ft_add_tail(shell, new_node, REDIRECT_IN);
    else if (c == 62)
        ft_add_tail(shell, new_node, REDIRECT_OUT);
    return (str);
}


