/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_multi_env_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:55:39 by yli               #+#    #+#             */
/*   Updated: 2023/07/17 18:22:26 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *check_path_valid_utils(char *str, t_env *env);
int	check_path_str(char *str);

static char *check_path_valid_utils_free(char *str, int i, t_env *env)
{
	char *path;
	char *sub1;

	path = ft_substr(str, 0, i);
	sub1 = ft_expand(path, &env);
	if (path)
		free(path);
	return (sub1);
}
char *check_path_valid_utils(char *str, t_env *env)
{
	int i;
	char *sub1;
	char *sub2;
	char *result;

	if ((str[ft_strlen(str) - 1] == str[ft_strlen(str) - 2] && str[ft_strlen(str) - 1] == 34) || (str[ft_strlen(str) - 1] == str[ft_strlen(str) - 2] && str[ft_strlen(str) - 1] == 39))
		return (ft_expand(str, &env));
	i = check_path_str(str);
	// sub1 = ft_expand(ft_substr(str, 0, i), &env);
	sub1 = check_path_valid_utils_free(str, i, env);
	if ((str[i] == str[i + 1] && str[i] == 34) || (str[i] == str[i + 1] && str[i] == 39))
		sub2 = ft_substr(str, i + 2, (int)ft_strlen(str) - i - 2);
	else
		sub2 = ft_substr(str, i, (int)ft_strlen(str) - i);
	if (!sub1 && sub2)
		return (sub2);
	if (sub1 && !sub2)
		return (sub1);
	if (!sub1 && !sub2)
		return (NULL);
	result = ft_strjoin(sub1, sub2);
	// if (str)
	// 	free(str);
	ft_free_3str(sub1, sub2, NULL);
	return (result);
}

int	check_path_str(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (check_path_char(str[i]) == 1)
			break ;
		i++;
	}
	return (i);
}