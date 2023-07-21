/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:28:25 by yli               #+#    #+#             */
/*   Updated: 2023/07/21 20:42:38 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char		*ft_parse_original_from_word(char *str, t_env **env);
char		*ft_parse_original_from_word_core(char *str, t_env **env,
				int signal, int size);

static char	*ft_parse_word_rules_strjoin_quote(char *sub1, char *sub2,
		t_env **env, int signal)
{
	char	*subresult1;
	char	*subresult2;
	char	*result;

	subresult1 = ft_parse_dollar_frame(sub1, *env, 0);
	if (signal == 34)
		subresult2 = ft_parse_dollar_frame(sub2, *env, 2);
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

static	char	*ft_ft_parse_original_from_word_core_utils(char *result, 
		char *str, t_env **env)
{
	char	*final;
	char	*utils;

	utils = ft_parse_original_from_word(str, env);
	final = ft_strjoin(result, utils);
	ft_free_3str(result, utils, NULL);
	return (final);
}

char	*ft_parse_original_from_word_core(char *str, t_env **env,
		int signal, int size)
{
	char	*sub1;
	char	*sub2;
	char	*result;
	int		k;

	k = ft_count_size_lexer(str, signal, size + 1);
	sub1 = ft_substr(str, 0, size);
	sub2 = ft_substr(str, size + 1, k - size - 1);
	result = ft_parse_word_rules_strjoin_quote(sub1, sub2, env, signal);
	ft_free_3str(sub1, sub2, NULL);
	if (str[k + 1])
	{
		str += k + 1;
		return (ft_ft_parse_original_from_word_core_utils(result, str, env));
	}
	else
		return (result);
}

char	*ft_parse_original_from_word(char *str, t_env **env)
{
	int		i;
	int		j;
	char	*result;

	if (!ft_check_quote_in_word(str))
	{
		result = ft_parse_dollar_frame(str, *env, 0);
		return (result);
	}
	else if (str[0] == 34)
		return (ft_parse_original_from_dq(str, env));
	else if (str[0] == 39)
		return (ft_parse_original_from_sq(str, env));
	i = ft_count_size_lexer(str, 34, 0);
	j = ft_count_size_lexer(str, 39, 0);
	if (i < j)
		return (ft_parse_original_from_word_2(str, env, 34, i));
	else
		return (ft_parse_original_from_word_2(str, env, 39, j));
}
