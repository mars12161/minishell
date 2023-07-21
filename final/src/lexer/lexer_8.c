/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:00:30 by yli               #+#    #+#             */
/*   Updated: 2023/07/21 17:36:06 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_shell	*get_shell_bottom(t_shell *shell);
int		get_shell_size(t_shell *shell);
t_shell	*get_parse_bottom(t_shell *node);
int		ft_i_start_from_word_2(char *str, int pre);
char	*ft_parse_original_from_word_2(char *str, t_env **env, int c, int j);

t_shell	*get_shell_bottom(t_shell *shell)
{
	while (shell && shell->next != NULL)
		shell = shell->next;
	return (shell);
}

int	get_shell_size(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell)
		return (0);
	while (shell)
	{
		shell = shell->next;
		i++;
	}
	return (i);
}

t_shell	*get_parse_bottom(t_shell *node)
{
	while (node && node->next != NULL)
		node = node->next;
	return (node);
}

int	ft_i_start_from_word_2(char *str, int pre)
{
	int	i;
	int	j;

	i = ft_count_size_lexer(str, 34, 0);
	j = ft_count_size_lexer(str, 39, 0);
	if (i < j)
	{
		pre += i;
		str += i;
		return (ft_i_start_from_dq(str, pre));
	}
	else
	{
		pre += j;
		str += j;
		return (ft_i_start_from_sq(str, pre));
	}
	return (0);
}

char	*ft_parse_original_from_word_2(char *str, t_env **env, int c, int j)
{
	char	*result;
	int		k;

	k = ft_count_size_lexer(str, c, j + 1);
	if (k == (int)ft_strlen(str))
	{
		result = ft_strdup(str);
		return (result);
	}
	else
		return (ft_parse_original_from_word_core(str, env, c, j));
}
