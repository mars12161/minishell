/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:11:51 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/08 16:59:04 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

t_cmds	*init_cmds(t_parser *parser)
{
	char	**str;
	int		count_args;
	t_shell	**tmp;

	count_args = count_args(parser->list);
	str = ft_calloc(count_args + 1, sizeof(char *));
	*tmp = parser->list;
	if (!str)
		return (NULL);
	while (count_args)
	{
		if (tmp->input)
		{
			str[i] = ft_strdup(*tmp->input);
			del_node(tmp, *tmp);
			*tmp = parser->list;
			i++;
		}
		count_args--;
	}
	return (new_cmds(str, parser->redirections));
}
