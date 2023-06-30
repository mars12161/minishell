/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DQ_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:27:32 by yli               #+#    #+#             */
/*   Updated: 2023/06/30 08:41:15 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *ft_parse_dollar_frame(char *str, t_env *env);

static char *ft_parse_dollar_core_utils(char *str, t_env *env, int c)
{
    char *str2;
    char *str3;
    char *path;
    char *result;

    if (str[1] == '?')
    {
        str2 = ft_strdup("?");
        str3 = ft_substr((char const *)str, 2, ft_strlen((char *)str) - 2);
    }
    else
    {
        str2 = ft_substr((char const *)str, 1, ft_count_size(str, c) - 1);
        str3 = ft_substr((char const *)str, ft_count_size(str, c), ft_strlen((char *)str) - ft_count_size(str, c));
    }
    path = ft_expand(str2, &env);
    result = ft_check_strjoin(path, str3);
    //ft_free_3str(str3, str2, path);
    return (result);
}

static char *check_path_valid(char *str, t_env *env, int c)
{
    int i;
    char *result;

    printf("c: %c\n", (char)c);
    i = 1;
    // if (c == -1)
    // {
    //     str += 1;
    //     result = ft_expand(str, &env);
    //     return (result);
    // }
    while (str[i])
    {
        printf("c: %c\n", str[i]);
        if (check_path_char(str[i]) > 0)
            return (ft_parse_dollar_core_utils(str, env, str[i])); 
        i++;
    }
    printf("in check_path_valid\n");
    if (i == ft_strlen(str) && c != -1)
        return (ft_parse_dollar_core_utils(str, env, c));
    return (NULL);
}

static char *check_expand_path_space(char *str, t_env *env)
{
    int space;
    int dollar;
    char *result;

    space = ft_count_size(str, 32);
    dollar = ft_count_size(str, 36);
    result = NULL;
    if (str[1] == '?')
        result = ft_parse_dollar_core_utils(str, env, '?');
    if (!space && !dollar)
        result = check_path_valid(str, env, -1);
    else if (!dollar && space)
        result = check_path_valid(str, env, 32);
    else if (space < dollar)
        result = check_path_valid(str, env, 32);
    else
        result = check_path_valid(str, env, 36);
    return (result);   
}

static char *ft_parse_dollar_core(char *str, t_env *env)
{
    char *str1;
    char *str2;
    char *path;
    char *result;

    if (*str == '$')
        result = check_expand_path_space(str, env);
    else
    {
        str1 = ft_substr((char const *)str, 0, ft_count_size(str, 36));
        str2 = ft_substr((char const *)str, ft_count_size(str, 36), ft_strlen((char *)(str)) - ft_count_size(str, 36));
        path = check_expand_path_space(str2, env);
        result = ft_check_strjoin(str1, path);
        ft_free_3str(str1, str2, path);
    }
    return (result);
}

char *ft_parse_dollar_frame(char *str, t_env *env)
{
    char *result;

    if (!check_dollar(str, 36))
        return (str);
    else if (check_dollar(str, 36))
        result = ft_parse_dollar_core(str, env);
    if (check_dollar(result, 36))
        result = ft_parse_dollar_frame(result, env);
    return(result);
}
