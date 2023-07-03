/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:43:01 by yli               #+#    #+#             */
/*   Updated: 2023/07/03 16:35:31 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_parse *parse_init(void)
{
	t_parse *node;

	node = malloc(sizeof(t_parse) * 1);
	node->command = malloc(sizeof(char) * 100);
	node->infilepath = malloc(sizeof(char) * 1000);
	node->outfilepath = malloc(sizeof(char) * 100);
	if (!node || !node->command || !node->infilepath || !node->outfilepath)
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

static int ft_count_args(char **str)
{
    int count = 0;

    while (*str != NULL)
	{
        count++;
        str++;
    }
    return (count);
}

static void	parse_cmm(t_parse *cmm, t_shell *head)
{
	char **wline;

	wline = ft_shell_whole_line(head);
	cmm->whole_line = wline;
	cmm->command = wline[0];
	cmm->wline_count = ft_count_args(wline);
}

static	t_parse **create_cmm(t_shell *head, int *size, t_env *env)
{
	t_parse **cmm;
	t_shell *temp;
	int	i;

	i = 0;
	cmm = ft_calloc(*size, sizeof(t_parse));
	temp = head;
	while (temp)
	{
		if (i < *size)
		{
			cmm[i] = parse_shell(temp, env);
			if (!cmm[i])
				return (NULL);
		}
		while (temp && temp->type != 5)
			temp = temp->next;
		if (temp)
			temp = temp->next;
		i++;
	}
	return (cmm);
}

t_parse_arr *parse_array_create(t_shell *head,t_env *env)
{
	t_parse **cmm;
	t_parse_arr *cmm_arr;

	if (!head)
		return (NULL);
	cmm_arr = malloc(sizeof(t_parse_arr));
	if (!cmm_arr)
		return (NULL);
	cmm_arr->size = get_size_cmmarr(head);
	cmm = create_cmm(head, &cmm_arr->size, env);
	if (!cmm)
		return (NULL);
	else
		cmm_arr->cmm = cmm;
	return (cmm_arr);
}

static void	parse_other(t_shell *temp, t_parse *cmm, t_env *env)
{
	if (temp->type == REDIRECT_IN)
		parse_redir_in(cmm, temp);
	else if (temp->type == REDIRECT_OUT)
		parse_redir_out(cmm, temp);
	else if (temp->type == APP_M)
		parse_redir_out_app(cmm, temp);
	else if (temp->type == HEREDOC)
		parse_delim(cmm, env, temp);
}


t_parse	*parse_shell(t_shell *head, t_env *env)
{
	t_shell *temp;
	t_parse *cmm;
	int	i;

	i = 0;
	cmm = parse_init();
	temp = head;
	while (temp)
	{
		if (!i)
		{
			parse_cmm(cmm, temp);
			i = 1;
		}
		if (temp->type == PIPE)
			break ;
		else
			parse_other(temp, cmm, env);
		temp = temp->next;
	}
	return (cmm);
}