/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:20:30 by yli               #+#    #+#             */
/*   Updated: 2023/07/17 11:34:26 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			ft_count_size_lexer(char *str, int c, int start);
char		*ft_parse_original_from_dq(char *str, t_env **env);
char		*ft_parse_original_from_sq(char *str, t_env **env);
int			ft_character_after_dollar(char *str);

//where
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
		subresult1 = ft_parse_dollar_frame(sub1, *env);
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

// static char *ft_parse_original_from_word_core(char *str, t_env **env,
//		int signal, int size)
// {
//     char *sub1;
//     char *sub2;
//     char *result;
//     int k;

//     k = ft_count_size_lexer(str, signal, size + 1); // abc"dd$USER"
//     sub1 = ft_substr(str, 0, size);
//     printf("in word core: sub1: %s\n", sub1); //should be abc
//     printf("in word core:str[size] %c str[k] %c size = %d k= %d\n",
//		str[size], str[k], size , k);
//     sub2 = ft_substr(str, size + 1, k - size - 1); //not sure k or k-1
//     printf("in word core: sub2: %s\n", sub2); //should be dd$USER
//     result = ft_parse_word_rules_strjoin_quote(sub1, sub2, env, signal);
//     //ft_free_3str(sub1, sub2, NULL); //75% sure
//     if (str[k + 1])
//     {
//         str += k + 1;
//         printf("str in sub3: %s\n", str);
//         return (ft_strjoin(result, ft_parse_original_from_word(str, env)));
//     }
//     else
//         return (result);
// }

char	*ft_parse_original_from_dq(char *str, t_env **env)
{
	int		k;
	char	*sub1;
	char	*sub2;
	char	*result;

	k = ft_count_size_lexer(str, 34, 1); //"dd$USER"abc
	sub1 = ft_substr(str, 1, k - 1);
	// printf("in dq: sub1: %s\n", sub1); //should be dd$USER
	// printf("k %d strlen %d\n", k, (int)ft_strlen(str));
	if (k == (int)ft_strlen(str) - 1) //"xyz"
		return (ft_parse_dollar_frame(sub1, *env));
	sub2 = ft_substr(str, k + 1, (int)ft_strlen(str) - k - 1);
	// printf("in dq: sub2: %s\n", sub2); //should be abc
	result = ft_parse_original_quote_core(sub1, sub2, env, 34);
	//ft_free_3str(sub1, sub2, NULL);
	return (result);
}

char	*ft_parse_original_from_sq(char *str, t_env **env)
{
	int		k;
	char	*sub1;
	char	*sub2;
	char	*result;

	k = ft_count_size_lexer(str, 39, 1); //'dd$USER'abc
	sub1 = ft_substr(str, 1, k - 1);
	// printf("in sq: sub1: %s\n", sub1); //should be dd$USER
	if (k == (int)ft_strlen(str) - 1) //'xyz'
		return (sub1);
	sub2 = ft_substr(str, k + 1, (int)ft_strlen(str) - k - 1);
	// printf("in sq: sub2: %s\n", sub2); //should be abc
	result = ft_parse_original_quote_core(sub1, sub2, env, 39);
	//ft_free_3str(sub1, sub2, NULL);
	return (result);
}

int	ft_character_after_dollar(char *str)
{
	int	c;

	if (ft_strlen(str) == 1)
		return (1);
	c = str[1];
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 62) || c == 64 || (c >= 91
			&& c <= 94) || c == 96 || (c >= 123 && c <= 133))
		return (1);
	return (0);
}
