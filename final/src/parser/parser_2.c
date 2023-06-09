/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:50:37 by yli               #+#    #+#             */
/*   Updated: 2023/07/13 14:44:04 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*check_input(t_shell *temp);
void	parse_redir_out(t_parse *cmm, t_shell *temp);
void	parse_redir_out_app(t_parse *cmm, t_shell *temp);
char	*read_heredoc(t_env *env, char *delimiter);
void	parse_delim(t_parse *cmm, t_env *env, t_shell *temp);

char	*check_input(t_shell *temp)
{
	if (temp->next)
	{
		if (temp->next->type == 3 && temp->next->next->type == 0)
			return (temp->next->next->input);
		if (temp->next->type == 3 && (temp->next->next->type == 10
									  || temp->next->next->type == 11))
			return (temp->next->next->input);
		if (temp->next->type == 10
			|| temp->next->type == 11)
			return (temp->next->input);
	}
	else
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
		// free everything todo
		g_exit = 2;
		return (NULL);
	}
	return (NULL);
}

void	parse_redir_out(t_parse *cmm, t_shell *temp)
{
	int	fd;

	if (temp->type == REDIRECT_OUT)
	{
		if (!temp->next)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
			g_exit = 2;
			return ;
		}
		if (temp->input)
		{
			fd = open(temp->next->input, O_CREAT | O_RDWR, 0644);
			if (fd == -1)
				perror("File could not be created");
			close(fd);
			if (cmm->redirection_out == 0)
				cmm->outfilepath = ft_strdup(check_input(temp));
			else
			{
				free(cmm->outfilepath);
				cmm->outfilepath = ft_strdup(check_input(temp));
			}
		}
		cmm->redirection_out = 1;
	}
}

void	parse_redir_out_app(t_parse *cmm, t_shell *temp)
{
	int	fd;

	if (temp->input)
	{
		if (!temp->next)
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
			g_exit = 2;
			return ;
		}
		fd = open(temp->next->input, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			perror("File could not be created");
		close(fd);
		if (cmm->redirection_out == 0)
			cmm->outfilepath = ft_strdup(check_input(temp));
		else
		{
			free(cmm->outfilepath);
			cmm->outfilepath = ft_strdup(check_input(temp));
		}
	}
	cmm->redirection_out = 2;
}

char	*read_heredoc(t_env *env, char *delimiter)
{
	char	*str;
	char	*str_expand_check;
	char	*whole_str;

	whole_str = ft_strdup("");
	signal(SIGINT, sigint_heredoc);
	str = "";
	g_exit = 0;
	while (ft_strcmp(str, delimiter) && g_exit == 0)
	{
		str = readline("heredoc>");
		if (!str)
			break;
		if (!ft_strcmp(str, delimiter) || g_exit == 130)
			break;
		str_expand_check = ft_parse_dollar_frame(str, env);
		whole_str = ft_strjoin(whole_str, str_expand_check);
		whole_str = ft_strjoin(whole_str, "\n");
	}
	return (whole_str);
}

void	parse_delim(t_parse *cmm, t_env *env, t_shell *temp)
{
	char *delimiter;
	char *heredoc;

	delimiter = check_input(temp);
	if (!delimiter)
		return ;
	if (temp->input)
	{
		if (!cmm->redirection_in)
		{
			heredoc = read_heredoc(env, delimiter);
			if (!heredoc)
				return ;
			cmm->infilepath = ft_strcat(cmm->infilepath, heredoc);
		}
		else
		{
			free(cmm->infilepath);
			heredoc = read_heredoc(env, delimiter);
			if (!heredoc)
				return ;
			cmm->infilepath = ft_strcat(cmm->infilepath, heredoc);
		}
		free(heredoc);
		cmm->redirection_in = 2;
	}
}

void	parse_redir_in(t_parse *cmm, t_shell *temp)
{
	if (temp->input)
	{
		if (cmm->redirection_in == 0)
		{
			if (!temp->next)
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
				g_exit = 2;
				return ;
			}
			else
			{
				check_infile(temp->next->input);
				cmm->infilepath = ft_strcat(cmm->infilepath, check_input(temp));
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
