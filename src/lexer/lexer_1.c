/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:21:54 by mschaub           #+#    #+#             */
/*   Updated: 2023/06/20 17:51:47 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell *fill_shell(char *str, t_shell *shell, t_env **env)
{
	while (*str == ' ')
		str++;
	while (*str)
	{
		if (*str == ' ')
			str = new_node_SPACE(str, &shell, 32);
		else if (*str == '|')
			str = new_node_PIPE(str, &shell, 124);
		else if (*str == '\"')
			str = new_node_DSQ(str, &shell, 34, env);
		else if (*str == '\'')
			str = new_node_DSQ(str, &shell, 39, env);
		//else if (*str == '\n')
		//	str = new_node_NL_ESC(str, &shell, 10);
		else if (*str == '<')
			str = new_node_RED(str, &shell, 60);
		else if (*str == '>')
			str = new_node_RED(str, &shell, 62);
		// else if (*str == '\\')
		// 	str = new_node_NL_ESC(str, &shell, 92);
		else
			str = new_node_DW(str, &shell, env);
	}
	//ft_free(result);
	return (shell);
}
