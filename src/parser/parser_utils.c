/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:32:52 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/08 15:40:33 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

t_parser	init_parser(t_shell *list)
{
	t_parser	parser;

	parser.list = list;
	parser.redirections = NULL;
	return (parser);
}

/*
 Function to count all the arguments
 separated by a Pipe
 */
int	count_args(t_shell *list)
{
	t_shell	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

/*
 Function to count all the pipes
 */
int	count_pipes(t_shell *list)
{
	t_shell	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

/*
 Function to get the next command
 after a pipe
 */
t_shell	*get_next_pipe(t_shell *list)
{
	t_shell	*tmp;

	tmp = list;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	return (tmp);
}

void	del_node(t_shell **list, t_shell *node)
{
	t_shell	*current;

	if (*list == node)
	{
		*list = node->next;
		free(node);
		return ;
	}
	current = *list;
	while (current->next && current->next != node)
		current = current->next;
	if (current->next == node)
	{
		current->next = node->next;
		free(node);
	}
}
