/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 22:02:41 by yli               #+#    #+#             */
/*   Updated: 2023/07/14 13:03:08 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parse	*parse_init(void);
char	**ft_shell_whole_line(t_shell *head);
int		ft_count_args(char **str);
void	parse_redir_in(t_parse *cmm, t_shell *temp);

t_parse	*parse_init(void)
{
	t_parse	*node;

	node = malloc(sizeof(t_parse) * 1);
	//node->command = malloc(sizeof(char) * 100);
	node->infilepath = malloc(sizeof(char) * 1000);
	node->outfilepath = malloc(sizeof(char) * 100);
	if (!node || !node->infilepath || !node->outfilepath)
		return (NULL);
	node->redirection_in = 0;
	node->redirection_out = 0;
	node->pipe = 0;
	return (node);
}

char	**ft_shell_whole_line(t_shell *head)
{
	int		i;
	int		n;
	char	**wline;

	if (head == NULL)
		return (NULL);
	i = args_count(head);
	n = 0;
	wline = malloc(sizeof(*wline) * (i + 1));
	if (!wline)
		return (NULL);
	wline[i] = NULL;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
		{
			wline[n] = ft_strdup(head->input);
			n++;
		}
		head = head->next;
	}
	if (head && head->type == PIPE)
		head = head->next;
	return (wline);
}

int	ft_count_args(char **str)
{
	int	count;

	count = 0;
	while (*str != NULL)
	{
		count++;
		str++;
	}
	return (count);
}

/*
void	parse_redir_in(t_parse *cmm, t_shell *temp)
{
	if (temp->input)
	{
		if (cmm->redirection_in == 0)
		{
			check_infile(temp->next->input);
			cmm->infilepath = ft_strcat(cmm->infilepath, check_input(temp));
			//do not have ft_strcat
		}
		else
		{
			free(cmm->infilepath);
			cmm->infilepath = ft_strdup(check_input(temp));
		}
	}
	cmm->redirection_in = 1;
}*/
