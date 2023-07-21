/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_multi_env_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:21:31 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/21 20:52:05 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char		*ft_parse_dollar_frame(char *str, t_env *env, int signal);
char		*ft_parse_dollar_core(char *str, t_env *env, int signal);

static char	*ft_parse_dollar_core_utils(char *str,
				t_env *env, int c, int signal)
{
	char	*str2;
	char	*str3;
	char	*result;

	if (str[1] == '?')
	{
		str2 = ft_strdup("?");
		str3 = ft_substr((char const *)str, 2, ft_strlen((char *)str) - 2);
	}
	else
	{
		str2 = ft_substr((char const *)str, 1, ft_count_size(str, c) - 1);
		str3 = ft_substr((char const *)str, ft_count_size(str, c),
				ft_strlen((char *)str) - ft_count_size(str, c));
	}
	result = ft_parse_dollar_core_utils2(str2, str3, env, signal);
	ft_free_3str(str3, str2, NULL);
	return (result);
}

static char	*check_path_valid(char *str, t_env *env, int c, int signal)
{
	size_t	i;

	i = 1;
	if (c == -1)
	{
		str += 1;
		if (check_path_str(str) == (int)ft_strlen(str))
			return (ft_expand(str, &env));
		else
			return (check_path_valid_utils(str, env, signal));
	}
	while (str[i])
	{
		if (check_path_char(str[i]) > 0)
			return (ft_parse_dollar_core_utils(str, env, str[i], signal));
		i++;
	}
	if (i == ft_strlen(str) && c != -1)
		return (ft_parse_dollar_core_utils(str, env, c, signal));
	return (NULL);
}

static char	*check_expand_path_space(char *str, t_env *env, int signal)
{
	int		space;
	int		dollar;
	char	*result;

	space = ft_count_size(str, 32);
	dollar = ft_count_size(str, 36);
	result = NULL;
	if (str[1] == '?')
	{
		result = ft_parse_dollar_core_utils(str, env, '?', signal);
		return (result);
	}
	if (!space && !dollar)
		result = check_path_valid(str, env, -1, signal);
	else if (!dollar && space)
		result = check_path_valid(str, env, 32, signal);
	else if (space < dollar)
		result = check_path_valid(str, env, 32, signal);
	else
		result = check_path_valid(str, env, 36, signal);
	return (result);
}

char	*ft_parse_dollar_core(char *str, t_env *env, int signal)
{
	char	*str1;
	char	*str2;
	char	*path;
	char	*result;

	if (*str == '$')
		result = check_expand_path_space(str, env, signal);
	else
	{
		str1 = ft_substr((char const *)str, 0, ft_count_size(str, 36));
		str2 = ft_substr((char const *)str, ft_count_size(str, 36),
				ft_strlen((char *)(str)) - ft_count_size(str, 36));
		path = check_expand_path_space(str2, env, signal);
		result = ft_check_strjoin(str1, path);
		ft_free_3str(str1, str2, path);
	}
	return (result);
}

char	*ft_parse_dollar_frame(char *str, t_env *env, int signal)
{
	char	*result;
	char	*final;

	final = NULL;
	if (str[0] == '$')
	{
		if (ft_character_after_dollar(str))
			return (ft_parse_dollar_frame_2(str));
	}
	if (!check_dollar(str, 36))
		return (ft_parse_dollar_frame_2(str));
	else
	{
		result = ft_parse_dollar_core(str, env, signal);
		if (!result)
			return (NULL);
		if (check_dollar(result, 36))
		{
			final = ft_parse_dollar_frame(result, env, signal);
			free(result);
		}
		else
			return (result);
	}
	return (final);
}
