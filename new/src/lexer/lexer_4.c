/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:16:35 by yli               #+#    #+#             */
/*   Updated: 2023/06/26 12:50:59 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_word_or_path(t_shell *shell);
void ft_add_tail(t_shell **shell, t_shell *new_node, enum e_token type);

static t_shell *get_shell_bottom(t_shell *shell)
{
    while(shell && shell->next != NULL)
        shell = shell->next;
    return (shell);
}

// static t_shell *get_shell_second_from_bottom(t_shell *head)
// {
//     while (head && head->next && head->next->next != NULL)
//         head = head->next;
//     return (head);
// }

static int	get_shell_size(t_shell *shell)
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

int check_word_or_path(t_shell *shell)
{
    // t_shell *bottom;
    // t_shell *second_bottom;
    int i;

    // bottom = get_shell_bottom(shell);
    // second_bottom = get_shell_second_from_bottom(shell);
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
    {
        if (shell->type == REDIRECT_IN || shell->type == HEREDOC)
            return (1);
        else if (shell->type == REDIRECT_OUT || shell->type == APP_M)
            return (2);
        else if (shell->type == SPA && (shell->pre->type == REDIRECT_IN || shell->pre->type == HEREDOC))
            return (1);
        else if (shell->type == SPA && (shell->pre->type == REDIRECT_OUT || shell->pre->type == APP_M))
            return (2);
    }
    return (0);
}

void ft_add_tail(t_shell **shell, t_shell *new_node, enum e_token type)
{
    t_shell *bottom;

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