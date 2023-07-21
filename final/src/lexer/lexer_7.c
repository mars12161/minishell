/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:20:30 by yli               #+#    #+#             */
/*   Updated: 2023/07/21 15:50:04 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			ft_count_size_lexer(char *str, int c, int start);
char		*ft_parse_original_from_dq(char *str, t_env **env);
char		*ft_parse_original_from_sq(char *str, t_env **env);
int			ft_character_after_dollar(char *str);

int	ft_count_size_lexer(char *str, int c, int start)
{
	while (str[start])
	{
		if (str[start] == c)
			return (start);
		start++;
	}
	return (start);
}

static char	*ft_parse_original_quote_core(char *sub1, char *sub2, t_env **env,
		int signal)
{
	char	*subresult1;
	char	*subresult2;
	char	*result;

	if (signal == 34)
		subresult1 = ft_parse_dollar_frame(sub1, *env, 2);
	else
		subresult1 = ft_strdup(sub1);
	subresult2 = ft_parse_original_from_word(sub2, env);
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

char	*ft_parse_original_from_dq(char *str, t_env **env)
{
	int		k;
	char	*sub1;
	char	*sub2;
	char	*result;

	k = ft_count_size_lexer(str, 34, 1);
	sub1 = ft_substr(str, 1, k - 1);
	if (k == (int)ft_strlen(str))
	{
		result = ft_parse_dollar_frame(sub1, *env, 2);
		free(sub1);
		return (result);
	}
	sub2 = ft_substr(str, k + 1, (int)ft_strlen(str) - k - 1);
	result = ft_parse_original_quote_core(sub1, sub2, env, 34);
	ft_free_3str(sub1, sub2, NULL);
	return (result);
}

char	*ft_parse_original_from_sq(char *str, t_env **env)
{
	int		k;
	char	*sub1;
	char	*sub2;
	char	*result;

	k = ft_count_size_lexer(str, 39, 1);
	sub1 = ft_substr(str, 1, k - 1);
	if (k == (int)ft_strlen(str))
		return (sub1);
	sub2 = ft_substr(str, k + 1, (int)ft_strlen(str) - k - 1);
	result = ft_parse_original_quote_core(sub1, sub2, env, 39);
	ft_free_3str(sub1, sub2, NULL);
	return (result);
}

int	ft_character_after_dollar(char *str)
{
	int	c;

	if (ft_strlen(str) == 1)
		return (1);
	c = str[1];
	if (c == 33 || (c >= 35 && c <= 38) || (c >= 40 && c <= 47) || (c >= 58 && c <= 62) || c == 64 || (c >= 91
			&& c <= 94) || c == 96 || (c >= 123 && c <= 133))
		return (1);
	return (0);
}
