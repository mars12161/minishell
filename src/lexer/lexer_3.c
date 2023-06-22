/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:52:20 by yli               #+#    #+#             */
/*   Updated: 2023/06/21 20:52:31 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *new_node_DQ(char *str, t_shell **shell, t_env **env)
{
    t_shell *new_node;
    char    *str;
    char    *result;
    int i;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
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
        return (new_node_WORD(str, shell));
    }
    i += 1;
    str = ft_substr((char const *)str, 1, i - 1);
    result = ft_parse_DQ(str);
    new_node->input = result;
    str += i;
    new_node->len = ft_strlen(new_node->input);
    ft_add_tail(shell, new_node, WORD);
    return (str);
}

char *new_node_SQ(char *str, t_shell **shell)
{
    t_shell *new_node;
    int i;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
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
        return (new_node_WORD(str, shell));
    }
    i += 1;
    new_node->input = ft_substr((char const *)str, 1, i - 1);
    str += i;
    new_node->len = ft_strlen(new_node->input);
    ft_add_tail(shell, new_node, WORD);
    return (str);
}

