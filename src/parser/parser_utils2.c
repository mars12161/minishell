/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:11:51 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/08 15:19:33 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

t_cmds	*new_cmds(char **str, t_shell *redirections)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->cmd = str;
	new->redirections = redirections;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cmds	*init_cmds(t_parser *parser)
{
	char	**str;
	int		count_args;
	t_shell	*tmp;

	count_args = count_args(parser->list);
	str = ft_calloc(count_args + 1, sizeof(char *));
	tmp = parser->list;
	if (!str)
		return (NULL);
	while (count_args)
	{
		if (tmp->input)
		{
			str[i] = ft_strdup(tmp->input);
			// that specific node then needs to be deleted
			tmp = parser->list;
			i++;
		}
		count_args--;
	}
	return (new_cmds(str, parser->redirections));
}
