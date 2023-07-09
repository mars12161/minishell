/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:07 by yli               #+#    #+#             */
/*   Updated: 2023/07/09 14:36:31 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_expand(char *str, t_env **env);

char	*ft_expand(char *str, t_env **env)
{
	t_env	*temp;
	char	*path;
	char	*result;

	temp = *env;
	while (temp)
	{
		if (str[0] == '?')
			return (ft_itoa(g_globe.g_exit));
		if (!ft_strncmp(temp->content, str, ft_strlen(str)))
		{
			path = ft_strtrim(temp->content, str); // can cause leaks
			if (*path != '=')
				return (NULL);
			result = ft_strtrim(path, "=");
			return (result);
		}
		temp = temp->next;
	}
	return (NULL);
}

// char	*ft_expand(char *str, t_env **env)
// {
// 	t_env	*temp;
// 	char	*path;
// 	char	*result;

// 	temp = *env;
// 	printf("in ft_expand: %s\n", str);
// 	while (temp)
// 	{
// 		if (str[0] == '?')
// 			return (ft_itoa(globe.g_exit));
// 		if (!ft_strncmp(temp->content, str, ft_strlen(str)))
// 		{
// 			path = ft_strtrim(temp->content, str);
// 			printf("in ft_expand path: %s\n", path);
// 			if (*path != '=')
// 				return (NULL);
// 			result = ft_strtrim(path, "=");
// 			printf("in ft_expand result: %s\n", result);
// 			return (result);
// 		}
// 		temp = temp->next;
// 	}
// 	return (NULL);
// }