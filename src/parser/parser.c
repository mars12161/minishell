/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:01:39 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/06 16:48:19 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

int	parser(t_shell *list)
{
	t_shell	*tmp;
	t_cmds	*cmds;

	tmp = list;
	cmds = NULL;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	cmds->cmd = ft_split(tmp->content, ' ');
}

