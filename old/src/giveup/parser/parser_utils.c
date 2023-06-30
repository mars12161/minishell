/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:32:52 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/16 16:10:47 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"


/*
 Function to count all the pipes
 in the input
 */
int		count_pipes(t_shell *list)
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
 * Function to count all arguments
 * before a pipe is found in input
 * Ex.: echo $USER | grep "xzx"
 * Return value is 2
 * */
int		count_args(t_shell *list)
{
	t_shell	*tmp;
	int 	i;

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
