/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_4_cd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:19:06 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/17 11:22:50 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd_env_loop(t_env **env, t_env *temp, char pwd[PATH_SIZE], char *str)
{
	int		homefound;
	char	*result;

	homefound = 0;
	if (!ft_strncmp(temp->content, str, ft_strlen(str)))
	{
		getcwd(pwd, PATH_SIZE);
		result = ft_strtrim((char const *)temp->content, (char const *)str);
		chdir(result);
		free(result);
		ft_replace_oldpwd(pwd, *env);
		if (!ft_strncmp(str, "HOME=", ft_strlen(str)))
			homefound = 1;
	}
	return (homefound);
}
