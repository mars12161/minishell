/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:50:37 by yli               #+#    #+#             */
/*   Updated: 2023/07/09 13:27:14 by mschaub          ###   ########.fr       */
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
	if (temp->next->type == 3 && temp->next->next->type == 0)
		return (temp->next->next->input);
	if (temp->next->type == 3 && (temp->next->next->type == 10
			|| temp->next->next->type == 11))
		return (temp->next->next->input);
	if (temp->next->type == 10
		||temp->next->type == 11)
		return (temp->next->input);
	else
	{
		printf("syntax error near unexpected token `newline'");
		// free everything todo
		g_globe.g_exit = 2;
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

void	parse_redir_out_app(t_parse *cmm, t_shell *temp)
{
	int	fd;

	if (temp->input)
	{
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
	g_globe.in_heredoc = 1;
	while (!g_globe.stop_heredoc)
	{
		write(1, "heredoc>", 8);
		str = get_next_line(0);
		if (!str)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			break;
		}
		if (!strcmp(str, delimiter))
			break;
		str_expand_check = ft_parse_dollar_frame(str, env);
		whole_str = ft_strjoin(whole_str, str_expand_check);
		whole_str = ft_strjoin(whole_str, "\n");
	}
	g_globe.stop_heredoc = 0;
	g_globe.in_heredoc = 0;
	return (whole_str);
}

void	parse_delim(t_parse *cmm, t_env *env, t_shell *temp)
{
	char *delimiter;
	char *heredoc;

	delimiter = check_input(temp);
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
			check_infile(temp->next->input);
			cmm->infilepath = ft_strcat(cmm->infilepath, check_input(temp));
		}
		else
		{
			free(cmm->infilepath);
			cmm->infilepath = ft_strdup(check_input(temp));
		}
	}
	cmm->redirection_in = 1;
}
