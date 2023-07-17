/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:23:48 by yli               #+#    #+#             */
/*   Updated: 2023/07/17 18:27:11 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_quote_in_word(char *str);
int	ft_i_start_from_sq(char *str, int pre);
int	ft_i_start_from_word(char *str, int pre);
int	ft_i_start_from_dq(char *str, int pre);

int	ft_check_quote_in_word(char *str)
{
	int	i;
	int	j;
	int	k;

	i = ft_count_size_lexer(str, 34, 0);
	j = ft_count_size_lexer(str, 39, 0);
	k = (int)ft_strlen(str);
	if (i == j && i == k && j == k)
		return (0); //not find
	else
		return (1);
}

int	ft_check_quote_before_space(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (-1);
		if (str[i] >= 33 && str[i] <= 126)
			j++;
		if (str[i] >= 33 && str[i] <= 126 && str[i + 1] == 32)
			break ;
		i++;
	}
	return (j);
}

int	ft_i_start_from_word(char *str, int pre)
{
	int	i;
	int	j;

	if (ft_check_quote_before_space(str) != -1)
		return (ft_check_quote_before_space(str) + pre);
	if (!ft_check_quote_in_word(str))
	{
		i = ft_count_size_lexer(str, 32, 0);
		return (i + pre);
	}
	else if (str[0] == 34)
		return (ft_i_start_from_dq(str, pre));
	else if (str[0] == 39)
		return (ft_i_start_from_sq(str, pre));
	else
	{
		i = ft_count_size_lexer(str, 34, 0);
		j = ft_count_size_lexer(str, 39, 0);
		if (i < j)
		{
			pre += i;
			str += i;
			return (ft_i_start_from_dq(str, pre));
		}
		else
		{
			pre += j;
			str += j;
			return (ft_i_start_from_sq(str, pre));
		}
	}
	return (0);
}

int	ft_i_start_from_sq(char *str, int pre)
{
	int	i;
	int	j;

	i = ft_count_size_lexer(str, 39, 1);
	// printf("sq i : %d ", i);
	// printf("pre : %d ", pre);
	// printf("strlen : %s %d\n", str, (int)ft_strlen(str));
	j = (int)ft_strlen(str);
	if (i == j - 1 || i == j - 2 || (i == j && str[pre] == 39))
		return (j + pre);
	if (str[i + 1] == 32)
		return (pre + i + 1);
	if (str[i + 1] == 39)
	{
		pre += i + 1;
		str += i + 1;
		return (ft_i_start_from_dq(str, pre));
	}
	else
	{
		pre += i + 1;
		str += i + 1;
		return (ft_i_start_from_word(str, pre));
	}
	return (-1);
}

int	ft_i_start_from_dq(char *str, int pre)
{
	int	i;
	int	j;

	i = ft_count_size_lexer(str, 34, 1);
	// printf("dq i : %d ", i);
	// printf("pre : %d ", pre);
	// printf("strlen : %s %d\n", str, (int)ft_strlen(str));
	j = (int)ft_strlen(str);
	// printf("i: %d j: %d str[pre]: %c pre: %d str: %s\n", i, j, str[pre], pre, str);
	// if (i == j - 1 || i == j - 2 || (i == j && str[pre] == 34))
	if (i == j - 1 || i == j - 2 || i == j)
		return (j + pre);
	if (str[i + 1] == 32)
		return (pre + i + 1);
	if (str[i + 1] == 34)
	{
		pre += i + 1;
		str += i + 1;
		return (ft_i_start_from_dq(str, pre));
	}
	else
	{
		pre += i + 1;
		str += i + 1;
		return (ft_i_start_from_word(str, pre));
	}
	return (-1);
}
