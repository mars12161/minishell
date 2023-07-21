/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:07 by yli               #+#    #+#             */
/*   Updated: 2023/07/21 15:48:57 by yli              ###   ########.fr       */
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
			return (ft_itoa(g_exit));
		if (!ft_strncmp(temp->content, str, ft_strlen(str)))
		{
			path = ft_strtrim(temp->content, str);
			if (*path != '=')
			{
				free(path);
				return (NULL);
			}
			result = ft_strtrim(path, "=");
			free(path);
			return (result);
		}
		temp = temp->next;
	}
	return (NULL);
}