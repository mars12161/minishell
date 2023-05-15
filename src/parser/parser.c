/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:01:39 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/15 14:09:09 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

t_cmds *init(t_shell *list)
{
	int		num_args;
	t_cmds	*new;
	t_shell	*tmp;
	char	**str;
	int		redir_in;
	int 	redir_out;

	num_args = count_args(list);
	tmp = list;
	str = ft_calloc(num_args + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (num_args > 0)
	{
		if (tmp->input)
		{
			str[i++] = ft_strdup(tmp->input);
			tmp = list;
		}
		if (tmp->type == REDIRECT_IN)
			redir_in = 1;
		else if (tmp->type == HEREDOC)
			redir_in = 2;
		else
			redir_in = 0;
		if (tmp->type == REDIRECT_OUT)
			redir_out = 1;
		else if (tmp->type == APP_M)
			redir_out = 2;
		else
			redir_out = 0;
		// delete the node
		num_args--;
	}
	return (t_cmdsnew(str, redir_in, redir_out));
}
