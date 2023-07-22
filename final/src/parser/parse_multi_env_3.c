/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_multi_env_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:55:39 by yli               #+#    #+#             */
/*   Updated: 2023/07/22 09:33:05 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*check_path_valid_utils(char *str, t_env *env, int signal);
char	*ft_str_check_quote(char *path, t_env *env, int signal);
int		check_path_str(char *str);
char	*ft_parse_dollar_core_utils2(char *str2, char *str3,
			t_env *env, int signal);

static	char	*check_path_valid_utils_free(char *str, int i, t_env *env)
{
	char	*path;
	char	*sub1;

	path = ft_substr(str, 0, i);
	sub1 = ft_expand(path, &env);
	if (path)
		free(path);
	return (sub1);
}

char	*ft_str_check_quote(char *path, t_env *env, int signal)
{
	char	*result;

	if (path[0] == 34 && ft_count_size(path, 34) && !signal)
		result = ft_parse_original_from_dq(path, &env);
	else if (path[0] == 39 && ft_count_size(path, 39) && !signal)
		result = ft_parse_original_from_sq(path, &env);
	else
		result = ft_strdup(path);
	return (result);
}

char	*check_path_valid_utils(char *str, t_env *env, int signal)
{
	char	*sub1;
	char	*sub2;
	char	*path;
	char	*result;

	if (check_path_str(str) == (int)ft_strlen(str))
		return (ft_expand(str, &env));
	sub1 = check_path_valid_utils_free(str, check_path_str(str), env);
	path = ft_substr(str, check_path_str(str),
			(int)ft_strlen(str) - check_path_str(str));
	sub2 = ft_str_check_quote(path, env, signal);
	free(path);
	if (!sub1 && sub2)
		return (sub2);
	if (sub1 && !sub2)
		return (sub1);
	if (!sub1 && !sub2)
		return (NULL);
	result = ft_strjoin(sub1, sub2);
	ft_free_3str(sub1, sub2, NULL);
	return (result);
}

int	check_path_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_path_char(str[i]) == 1)
			break ;
		i++;
	}
	return (i);
}

char	*ft_parse_dollar_core_utils2(char *str2, char *str3,
			t_env *env, int signal)
{
	char	*path1;
	char	*path2;
	char	*result;

	path1 = ft_expand(str2, &env);
	path2 = ft_str_check_quote(str3, env, signal);
	if (!path1 && path2)
		return (path2);
	if (path1 && !path2)
		return (path1);
	if (!path1 && !path2)
		return (NULL);
	result = ft_check_strjoin(path1, path2);
	ft_free_3str(path1, path2, NULL);
	return (result);
}
