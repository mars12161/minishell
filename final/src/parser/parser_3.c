/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:54:09 by yli               #+#    #+#             */
/*   Updated: 2023/07/21 14:07:57 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_infile(char *infilepath);
int		args_count(t_shell *head);
int		get_size_cmmarr(t_shell *head);
void	parse_redir_in(t_parse *cmm, t_shell *temp);

void	check_infile(char *infilepath)
{
	int	fd;

	fd = open(infilepath, O_RDONLY);
	if (fd == -1)
		return ;
	close(fd);
}

int	args_count(t_shell *head)
{
	int	i;

	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
			i++;
		head = head->next;
	}
	return (i);
}

int	get_size_cmmarr(t_shell *head)
{
	t_shell	*temp;
	int		size;

	size = 1;
	temp = head;
	while (temp)
	{
		if (temp->type == PIPE && temp->next)
			size++;
		temp = temp->next;
	}
	return (size);
}

void	parse_redir_in(t_parse *cmm, t_shell *temp)
{
	if (temp->input)
	{
		if (cmm->redirection_in == 0)
		{
			if (!temp->next)
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n",
					STDERR_FILENO);
				g_exit = 2;
				return ;
			}
			else
			{
				check_infile(temp->next->input);
				cmm->infilepath = ft_strdup(check_input(temp));
			}
		}
		else
		{
			free(cmm->infilepath);
			cmm->infilepath = ft_strdup(check_input(temp));
		}
	}
	cmm->redirection_in = 1;
}
