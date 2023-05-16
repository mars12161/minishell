/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmds_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:31:26 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/15 15:11:29 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmds	*t_cmdsnew(char **str, int redirection_in,
					 int redirection_out)
{
	t_cmds	*new;

	new = (t_cmds *)malloc(sizeof(t_cmds));
	if (!new)
		return (0);
	new->cmd = str;
	new->redirection_in = redirection_in;
	new->redirection_out = redirection_out;
	new->infilepath = NULL;
	new->outfilepath = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	t_cmds_addback(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp->next;
}

void	t_cmds_rmfirst(t_cmds **lst)
{
	t_cmds	*tmp;

	if (!*lst)
		return ;
	tmp = (*lst)->next;
	free(*lst);
	*lst = tmp;
}

void	free_cmds(t_cmds **lst)
{
	t_cmds	*current;
	t_cmds	*next;
	char	**str;

	current = *lst;
	while (current)
	{
		str = current->cmd;
		while (*str)
			free(*str);
		free(str);
		free(current);
		current = current->next;
	}
}
