/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:50:37 by yli               #+#    #+#             */
/*   Updated: 2023/06/20 17:50:38 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir_out(t_parse *cmm, t_shell *temp);
void	parse_redir_out_APP(t_parse *cmm, t_shell *temp);
void	parse_delim(t_parse *cmm, t_env *env, t_shell *temp);
void	parse_redir_in(t_parse *cmm, t_shell *temp);

static	char *check_input(t_shell *temp)
{
	if (temp->next->type == SPA && temp->next->next->type == WORD)
		return (temp->next->next->input);
	if (temp->next->type == WORD)
		return (temp->next->input);
	else
	{
		printf("syntax error near unexpected token `newline'"); // free everything todo
		//g_exit = 2; todo
		return (NULL);
	}
}
void	parse_redir_out(t_parse *cmm, t_shell *temp)
{
	int	fd;

	if (temp->type == REDIRECT_OUT)
	{
		if (temp->input)
		{
			fd = open(temp->next->input, O_CREAT | O_RDWR, 0644);
			if (fd == -1)
				perror("File could not be created");
			close(fd);
			if (cmm->redirection_out == 0)
				cmm->outfilepath = ft_strdup(check_input(temp)); //no ft_strcat
			else
			{
				free(cmm->outfilepath);
				cmm->outfilepath = ft_strdup(check_input(temp));
			}
		}
		cmm->redirection_out = 1;
	}
}

void	parse_redir_out_APP(t_parse *cmm, t_shell *temp)
{
	int	fd;

	if (temp->input)
	{
		//printf("out: %s\n", temp->next->next->input);
		fd = open(temp->next->input, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			perror("File could not be created");
		close(fd);
		if (cmm->redirection_out == 0)
			cmm->outfilepath = ft_strdup(check_input(temp)); //no ft_strcat
		else
		{
			free(cmm->outfilepath);
			cmm->outfilepath = ft_strdup(check_input(temp));
		}
	}
	cmm->redirection_out = 2;
}

void	parse_delim(t_parse *cmm, t_env *env, t_shell *temp)
{
	char *str;
	char *path;
	char	*whole_str;
	
	whole_str = strdup("");
	while (1)
	{
		str = readline("heredoc>");
		if (!strcmp(str, check_input(temp)))
		{
			printf("hello here\n");
			break ;
		}
			
		if (*str == '$')
		{
			path = ft_expand(str, &env);
			whole_str = ft_strjoin(whole_str, path);
			free(path);
		}
		else
			whole_str = ft_strjoin(whole_str, str);
		whole_str = ft_strjoin(whole_str, "\n");
		free(str);
	}
	write(cmm->redirection_out, whole_str, ft_strlen(whole_str)); //or do it in the execute
	free(whole_str);
}

void	parse_redir_in(t_parse *cmm, t_shell *temp)
{
	if (temp->input)
	{
		//printf("in: %s\n", temp->next->next->input);
		if (cmm->redirection_in == 0)
		{
			check_infile(temp->next->input);
			cmm->infilepath = strcat(cmm->infilepath, check_input(temp)); //do not have ft_strcat
		}
		else
		{
			free(cmm->infilepath);
			cmm->infilepath = ft_strdup(check_input(temp));
		}
	}
	cmm->redirection_in = 1;
}