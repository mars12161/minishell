/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DQ_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:27:32 by yli               #+#    #+#             */
/*   Updated: 2023/06/21 21:27:33 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_parse_dollar_frame(char *str, t_env *env);

static char *ft_parse_dollar_core_utils(char *str, t_env *env, int c)
{
    char *str2;
    char *str3;
    char *path;
    char *result;

    str2 = ft_substr((char const *)str, 1, ft_count_size(str, c) - 1);
    path = ft_expand(str2, &env);
    str3 = ft_substr((char const *)str, ft_count_size(str, c), ft_strlen((char *)str));
    result = ft_check_strjoin(path, str3);
    ft_free_3str(str3, str2, path);
    return (result);
}

static char *check_path_valid(char *str, t_env *env, int c)
{
    int i;
    char *result;

    i = 0;
    while (str[i])
    {
        if (check_path_char(str[i + 1]))
            return (ft_parse_dollar_core_utils(str, env, str[i]));   
        i++;
    }
    if (i == ft_strlen(str) && c != -1)
        return (ft_parse_dollar_core_utils(str, env, c));
    str += 1;
    result = ft_expand(str, &env);
    return (result);
}

static char *check_expand_path_space(char *str, t_env *env)
{
    int space;
    int dollar;
    char *result;

    space = ft_count_size(str, 32);
    dollar = ft_count_size(str, 36);
    result = NULL; 
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
    //printf("hello in ft_parse_dollar_frame\n");
    return(result);
}
