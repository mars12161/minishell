/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:01:39 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/16 16:14:33 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

void	print_cmds(t_cmds **lst)
{
	t_cmds *current = *lst;
	while (current)
	{
		printf("Commands:\n");
		char **cmds = current->cmd;
		for (int i = 0; cmds[i] != NULL; i++)
			printf(" %s\n", cmds[i]);
	}
	printf("\n");
	current = current->next;
}

t_cmds **parser(t_shell *list)
{
	
}

/*
 * Initialize a single node of t_cmds
 * Contains all the commands before a pipe
 * */

t_cmds *init_cmds(t_shell *list)
{
	int		num_args;
	int 	i;
	t_shell	*tmp;
	char	**str;
	int		redir_in;
	int 	redir_out;

	num_args = count_args(list);
	tmp = list;
	i = 0;
	str = ft_calloc(num_args + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (num_args > 0)
	{
		if (tmp->input)
		{
			str[i++] = tmp->input;
			// delete node
			tmp = list;
		}
		// TODO add redirections to cmds node
	}
	return (t_cmdsnew(str, redir_in, redir_out));
}
