/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:16:35 by yli               #+#    #+#             */
/*   Updated: 2023/07/21 18:31:49 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int				check_word_or_path(t_shell *shell);
void			ft_add_tail(t_shell **shell, t_shell *new_node,
					enum e_token type);

static	int	check_word_or_path_2(t_shell *shell)
{
	t_shell	*bottom;

	bottom = get_parse_bottom(shell);
	if (bottom->type == REDIRECT_IN || bottom->type == HEREDOC)
		return (1);
	else if (bottom->type == REDIRECT_OUT || bottom->type == APP_M)
		return (2);
	else if (bottom->type == SPA && (bottom->pre->type == REDIRECT_IN
			|| bottom->pre->type == HEREDOC))
		return (1);
	else if (bottom->type == SPA && (bottom->pre->type == REDIRECT_OUT
			|| bottom->pre->type == APP_M))
		return (2);
	return (0);
}

int	check_word_or_path(t_shell *shell)
{
	int		i;

	i = get_shell_size(shell);
	if (i == 0)
		return (0);
	if (i == 1)
	{
		if (shell->type == REDIRECT_IN || shell->type == HEREDOC)
			return (1);
		else if (shell->type == REDIRECT_OUT || shell->type == APP_M)
			return (2);
	}
	else
		return (check_word_or_path_2(shell));
	return (0);
}

void	ft_add_tail(t_shell **shell, t_shell *new_node, enum e_token type)
{
	t_shell	*bottom;

	if (!new_node)
		return ;
	new_node->type = type;
	new_node->next = 0;
	if (!*shell)
	{
		*shell = new_node;
		return ;
	}
	bottom = get_shell_bottom(*shell);
	bottom->next = new_node;
	new_node->pre = bottom;
}
