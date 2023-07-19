/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 22:02:41 by yli               #+#    #+#             */
/*   Updated: 2023/07/19 22:39:28 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parse	*parse_init(void);
char	**ft_shell_whole_line(t_shell *head);
int		ft_count_args(char **str);

t_parse	*parse_init(void)
{
	t_parse	*node;

	node = malloc(sizeof(t_parse) * 1);
	node->infilepath = NULL;
	node->outfilepath = NULL;
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
