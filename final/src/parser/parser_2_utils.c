/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:44:23 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/22 11:55:49 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*return_here(char *str)
{
	if (g_exit == 130)
	{
		free(str);
		return (NULL);
	}
	else
		return (str);
}

void	check_delim(t_parse *cmm, t_env *env,
					char *delimiter, char *heredoc)
{
	if (!cmm->redirection_in)
	{
		heredoc = read_heredoc(env, delimiter);
		if (!heredoc)
		{
			free(heredoc);
			return ;
		}
		cmm->infilepath = ft_strdup(heredoc);
	}
	else
	{
		free(cmm->infilepath);
		heredoc = read_heredoc(env, delimiter);
		if (!heredoc)
		{
			free(heredoc);
			return ;
		}
		cmm->infilepath = ft_strdup(heredoc);
	}
	free(heredoc);
	cmm->redirection_in = 2;
}
