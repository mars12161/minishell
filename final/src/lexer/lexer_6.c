/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:28:25 by yli               #+#    #+#             */
/*   Updated: 2023/07/13 21:11:37 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *ft_parse_original_from_word(char *str, t_env **env);

static char *ft_parse_word_rules_strjoin_quote(char *sub1, char *sub2, t_env **env, int signal)
{
    char *subresult1;
    char *subresult2;
    char *result;

    subresult1 = ft_parse_dollar_frame(sub1, *env);
    if (signal == 34)
        subresult2 = ft_parse_dollar_frame(sub2, *env);
    else
        subresult2 = ft_strdup(sub2);
    if (!subresult1 && subresult2)
        return (subresult2);
    if (!subresult2 && subresult1)
        return (subresult1);
    if (!subresult1 && !subresult2)
        return (NULL);
    result = ft_strjoin(subresult1, subresult2);
    ft_free_3str(subresult1, subresult2, NULL);
    return (result);
}

static char *ft_parse_original_from_word_core(char *str, t_env **env, int signal, int size)
{
    char *sub1;
    char *sub2;
    char *result;
    int k;

    k = ft_count_size_lexer(str, signal, size + 1); // abc"dd$USER"
    sub1 = ft_substr(str, 0, size);
    // printf("in word core: sub1: %s\n", sub1); //should be abc
    // printf("in word core:str[size] %c str[k] %c size = %d k= %d\n", str[size], str[k], size , k);
    sub2 = ft_substr(str, size + 1, k - size - 1); //not sure k or k-1 
    // printf("in word core: sub2: %s\n", sub2); //should be dd$USER
    result = ft_parse_word_rules_strjoin_quote(sub1, sub2, env, signal);
    if (str[k + 1])
    {
        str += k + 1;
        // printf("str in sub3: %s\n", str);
        return (ft_strjoin(result, ft_parse_original_from_word(str, env)));
    }
    else
    {
        //ft_free_3str(sub1, sub2, NULL); //75% sure
        return (result);
    }
    
}

char *ft_parse_original_from_word(char *str, t_env **env)
{
    int i;
    int j;
    int k;

    if (!ft_check_quote_in_word(str))
        return (ft_parse_dollar_frame(str, *env));
    else if(str[0] == 34)
        return (ft_parse_original_from_dq(str, env));
    else if (str[0] == 39)
        return (ft_parse_original_from_sq(str, env));
    i = ft_count_size_lexer(str, 34, 0);
    j = ft_count_size_lexer(str, 39, 0);
    if (i < j)
    {
        //str += i;
        //printf("str in parse original from word i : %s\n", str);
        k = ft_count_size_lexer(str, 34, i + 1);
        if (k == (int)ft_strlen(str) - 1 - i)
            return (str);
        else
            return (ft_parse_original_from_word_core(str, env, 34, i)); 
    }
    else
    {
        //str += j + 1;
        //printf("str in parse original from word j : %s\n", str);
        k = ft_count_size_lexer(str, 39, j + 1);
        if (k == (int)ft_strlen(str) - j - 1)
            return (str);
        else
            return (ft_parse_original_from_word_core(str, env, 39, j)); 
    }
    return (NULL);     
}