/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:16:35 by yli               #+#    #+#             */
/*   Updated: 2023/06/21 20:16:36 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_word_or_path(t_shell *shell);
void ft_add_tail(t_shell **shell, t_shell *new_node, enum e_token type);

static t_shell *get_shell_bottom(t_shell *shell)
{
    while(shell && shell->next != NULL)
        shell = shell->next;
    return (shell);
}

static t_shell *get_shell_second_from_bottom(t_shell *head)
{
    while (head && head->next && head->next->next != NULL)
        head = head->next;
    return (head);
}

int check_word_or_path(t_shell *shell)
{
    t_shell *bottom;
    t_shell *second_bottom;

    bottom = get_shell_bottom(shell);
    second_bottom = get_shell_second_from_bottom(shell);
    if (bottom->type == REDIRECT_IN || bottom->type == HEREDOC)
        return (1);
    else if (bottom->type == REDIRECT_OUT || bottom->type == APP_M)
        return (2);
    else if (bottom->type == SPA && (second_bottom->type == REDIRECT_IN || second_bottom->type == HEREDOC))
        return (1);
    else if (bottom->type == SPA && (second_bottom->type == REDIRECT_OUT || second_bottom->type == APP_M))
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
}