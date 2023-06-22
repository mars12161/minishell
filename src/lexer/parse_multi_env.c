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

static int check_dollar(char *str, int c)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(str)
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

static char *ft_count_size(char *str, int c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (0); 
}

static char *ft_parse_dollar_2(char *str, t_env *env, int c)
{
    char *path;
    char *str2;
    char *str3;
    char *result;

    if (!ft_count_size(str, 32))
    {
        if (!c)
        {
            path = ft_expand(str, &env);
            return (path);
        }
        else
            return (result);
    }
    else
    {
        str2 = ft_substr((char const *)str, 0, ft_count_size(str, 32));
        path = ft_expand(str2, &env);
        str3 = ft_substr((char const *)str, ft_count_size(str, 32) + 1, ft_strlen((char *)str));
        result = ft_strjoin(path, str3);
    }
    return (result);
}

static char *ft_parse_dollar_1(char *str, t_env *env)
{
    char *str1;
    char *str2;
    char *done;
    char *result;

    if (ft_count_size(str, 36))
    {
        str1 = ft_substr((char const *)str, 0, ft_count_size(str, 36));
        str2 =  ft_substr((char const *)str, ft_count_size(str, 36) + 1, ft_strlen((char *)str));
        done = ft_parse_dollar_2(str2, env);
        result = ft_strjoin(str1, done);
    }
    return(result);
}
