/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:01:39 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/12 16:03:54 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

int	parser(t_shell *list)
{
	int	num_pipes;
	t_cmds	*new;

	num_pipes = count_pipes(list);
	if (!list)
		return (0);
	while (list)
	{

	}
}
