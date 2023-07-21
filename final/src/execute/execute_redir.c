/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:50:25 by yli               #+#    #+#             */
/*   Updated: 2023/07/21 15:48:26 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redir_child(t_parse *node);
void	redir_parent(t_parse_arr *cmmarr);

static void	execute_infile_dup2(t_parse *node)
{
	int	fd_in;

	if (node->redirection_in == 1)
	{
		fd_in = open(node->infilepath, O_RDONLY);
		if (fd_in == -1)
			ft_error("open infile failed");
	}
	else
	{
		fd_in = open("heredoc.txt", O_CREAT | O_RDWR, 0644);
		if (fd_in == -1)
			ft_error("heredoc can't be created");
		write(fd_in, node->infilepath, ft_strlen(node->infilepath));
		close(fd_in);
		fd_in = open("heredoc.txt", O_RDONLY);
		if (fd_in == -1)
			ft_error("open heredoc failed");
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_error("dup2 failed");
	close(fd_in);
	unlink("heredoc.txt");
}

static void	execute_outfile_dup2(t_parse *node)
{
	int	fd_out;

	fd_out = 0;
	if (node->redirection_out == 1)
		fd_out = open(node->outfilepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->redirection_out == 2)
		fd_out = open(node->outfilepath, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd_out == -1)
		ft_error("open outfile failed");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_error("dup2 failed");
	close(fd_out);
}

void	redir_child(t_parse *node)
{
	if (node->redirection_in)
		execute_infile_dup2(node);
	if (node->redirection_out)
		execute_outfile_dup2(node);
}

void	redir_parent(t_parse_arr *cmmarr)
{
	t_parse	*cmm;

	cmm = cmmarr->cmm[cmmarr->size - 1];
	if (cmm->redirection_in)
		execute_infile_dup2(cmm);
	if (cmm->redirection_out)
		execute_outfile_dup2(cmm);
}
