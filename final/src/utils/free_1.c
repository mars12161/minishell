/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:42:56 by yli               #+#    #+#             */
/*   Updated: 2023/07/24 11:59:43 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		free_shell(t_shell **shell);
void		free_env(t_env **env);
void		free_all_in_loop(t_shell **shell, t_parse_arr *cmmarr, char *str);

void	free_shell(t_shell **shell)
{
	t_shell	*temp;

	if (!*shell || !shell)
		return ;
	while (*shell)
	{
		temp = (*shell)->next;
		if ((*shell)->input)
			free((*shell)->input);
		free(*shell);
		*shell = temp;
	}
	*shell = NULL;
}

static void	free_parse(t_parse *node)
{
	if (node == NULL)
		return ;
	ft_free_str(node->whole_line);
	if (node->redirection_in)
		free(node->infilepath);
	if (node->redirection_out)
		free(node->outfilepath);
	free(node);
}

static void	free_cmmarr(t_parse_arr *cmmarr)
{
	int	i;

	i = 0;
	if (!cmmarr)
		return ;
	while (i <= cmmarr->size)
	{
		if (cmmarr->cmm[i])
			free_parse(cmmarr->cmm[i]);
		i++;
	}
	free(cmmarr->cmm);
	free(cmmarr);
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*env = NULL;
}

void	free_all_in_loop(t_shell **shell, t_parse_arr *cmmarr, char *str)
{
	free_shell(shell);
	free_cmmarr(cmmarr);
	if (str)
		free(str);
}
