/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:23:48 by yli               #+#    #+#             */
/*   Updated: 2023/07/11 17:53:47 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_shell *init_shell_node(void);
int ft_check_size_str_for_node(char *str);
static int ft_count_size_in_str_normal(char *str, int i, int pre, int times);
static int ft_count_size_in_str_quote(char *str, int i, int pre, int times);

t_shell *init_shell_node(void)
{
	t_shell *new_node;

	new_node = NULL;
	new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
	return (new_node);
}

static int ft_count_size_in_str_quote_utils(char *str, int i)
{
	int flag1;
    int flag2;

    flag1 = 0;
    flag2 = 0;
    while(str[i])
    {
        if (str[i] == 34)
            flag2 += 1;
        if (str[i] == 39)
            flag1 += 1;
        if (flag1 == 2 || flag2 == 2)
            break ;
        i++;
    }
	return (i);
}

static int ft_count_size_in_str_quote(char *str, int i, int pre, int times)
{
    i = ft_count_size_in_str_quote_utils(str, i) + 1;
    if (times != 0)
        pre += i;
    if (str[i] == ' ' || str[i] == '\t'|| str[i] == 0)
    {
        if (times != 0)
            return (pre);  
        else
            return (i);
    }
    else
      return (ft_count_size_in_str_normal(str, i, pre, times));
}

static int ft_count_size_in_str_normal(char *str, int i, int pre, int times)
{
    int flag;

    flag = 0;
    str += i;
    i = 0;
    while(str[i])
    {
        if (str[i] == 34 || str[i] == 39)
            flag += 1;
		if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' '
				|| str[i + 1] == '\t') && flag == 0)
            return (i + pre + 1);        
        if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' '
				|| str[i + 1] == '\t') && flag)
            return (ft_count_size_in_str_quote(str, 0, pre, times));               
		i++;
    }
    return (i + pre);
}

int ft_check_size_str_for_node(char *str)
{
    int i;
    char *substr;
    int times1;
    int times2;

    i = ft_count_size(str, '|');
    if (i)
        substr = ft_substr(str, 0, i);
    else
        substr = ft_strdup(str);
    times1 = check_dollar(substr, 39);
    times2 = check_dollar(substr, 34);
    if (times1 >= 2 ||  times2 >= 2)
        i = ft_count_size_in_str_normal(substr, 0, 0, 1);
    else
        i = ft_count_size_in_str_normal(substr, 0, 0, 0);
    free(substr);
    return (i);
}