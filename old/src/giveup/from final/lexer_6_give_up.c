/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:28:25 by yli               #+#    #+#             */
/*   Updated: 2023/07/12 18:35:28 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
int ft_count_size_lexer(char *str, int c, int start);
char *ft_parse_word_rules_strjoin(char *sub1, char *sub2, t_env **env);
char *ft_parse_word_rules(char *str, t_env **env);
   
int ft_count_size_lexer(char *str, int c, int start) //where
{
    while(str[start])
    {
        if (str[start] == c)
            return (start);
        start++;
    }
    return (start);
}

char *ft_parse_word_rules_strjoin(char *sub1, char *sub2, t_env **env)
{
    char *subresult1;
    char *subresult2;
    char *result;

    subresult1 = ft_parse_dollar_frame(sub1, *env);
    subresult2 = ft_parse_dollar_frame(sub2, *env);
    if (!subresult1 && subresult2)
        return (subresult2);
    if (!subresult2 && subresult1)
        return (subresult1);
    if (!subresult1 && !subresult2)
        return (NULL);
    result = ft_strjoin(subresult1, subresult2);
    ft_free_3str(subresult1, subresult2, NULL);
    //ft_free_3str(sub1, sub2, NULL);
    return (result);
}

static char *ft_parse_word_rules_substr(char *str, int signal, int size, t_env **env)
{
    char *sub1;
    char *sub2;
    char *sub3;
    int i;

    sub1 = ft_substr(str, 0, size);
    printf("sub1: %s\n", sub1);
    str += (size);
    printf("str[0]: %c\n", str[0]);
    i = ft_count_size_lexer(str, signal, 1);
    sub2 = ft_substr(str, 1, i - 1);
    printf("sub2: %s\n", sub2);
    if (i == (int)ft_strlen(str) - 1 && str[0] == 34)
    {
        printf("return 0 in word rules %s\n", ft_parse_word_rules_strjoin(sub1, sub2, env));
        return (ft_parse_word_rules_strjoin(sub1, sub2, env));
    }
    else if (i == (int)ft_strlen(str) - 1 && str[0] == 39)
    {
        printf("return 1 in word rules %s\n", ft_strjoin(sub1, sub2));
        return (ft_strjoin(sub1, sub2));
    }
    else
    {
        sub3 = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
        if (str[0] == 34)
        {
            printf("return 2 in word rules %s\n", ft_strjoin(ft_parse_word_rules_strjoin(sub1, sub2, env), sub3));
            return (ft_strjoin(ft_parse_word_rules_strjoin(sub1, sub2, env), sub3));
        }
        else
        {
            printf("return 3 in word rules %s\n", ft_strjoin(ft_strjoin(sub1, sub2), sub3));
            return (ft_strjoin(ft_strjoin(sub1, sub2), sub3));
        }
    }
    printf("return 4\n"); 
    return (NULL);
}

char *ft_parse_word_rules(char *str, t_env **env)
{
    int i;
    int j;
    char *result;

    i = ft_count_size_lexer(str, 34, 0);
    j = ft_count_size_lexer(str, 39, 0);
    if (i < j) //meet '' first
        result = ft_parse_word_rules_substr(str, 34, i, env);
    else if (j < i) //meet ' first
        result = ft_parse_word_rules_substr(str, 39, j, env);
    if (j == (int)ft_strlen(str) && i == (int)ft_strlen(str))
        return (ft_parse_dollar_frame(str, *env));
    return (ft_parse_word_rules(result, env));
}