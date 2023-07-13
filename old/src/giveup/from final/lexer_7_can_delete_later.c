/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:28:25 by yli               #+#    #+#             */
/*   Updated: 2023/07/11 21:31:30 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *ft_parse_quote_rules(char *str, t_env **env);

static char *ft_parse_quote_rules_substr(char *str, int signal, int size, t_env **env)
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
    int i;
    int j;
    int signal;
    char *result;

    signal = str[0];
    i = ft_count_size_lexer(str, signal, 1);
    if (i == (int)ft_strlen(str) - 1)
        return (ft_parse_dollar_frame(str, *env));
    result = ft_parse_quote_rules_substr(str, signal, i, env);
    if (ft_count_size_lexer(str, 34, 0) == ft_count_size_lexer(str, 39, 0) == ft_strlen(str))
        return (result);
    else
        return (ft_parse_word_rules(result, env));
}