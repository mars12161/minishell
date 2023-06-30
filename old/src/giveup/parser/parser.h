/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:03:23 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/16 15:56:19 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../includes/minishell.h"
# include "../lexer/lexer.h"

/* Linked list to store all commands
 * before a pipe in a node
 */

/* Redirections in:
 * 0 - no redirection
 * 1 - REDIRECT_IN
 * 2 - HEREDOC
 * */

/* Redirections out:
 * 0 - no redirection
 * 1 - REDIRECT_OUT
 * 2 - APP_M
 * */

/* Int Pipe
 * 0 - No Pipe
 * 1 - Pipe
 * */

typedef struct s_cmds
{
	char			**cmd;
	int 			size;
	int 			redirection_in;
	int 			redirection_out;
	char 			*infilepath;
	char 			*outfilepath;
	int				pipe;
	int				fd[2];
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

/* Functions */
/* parser_utils.c */

int			count_pipes(t_shell *list);
int 		count_args(t_shell *list);
t_shell		*get_next_pipe(t_shell *list);


/* t_cmds_utils.c */
t_cmds		*t_cmdsnew(char **str, int redirection_in, int redirection_out);
void 		t_cmds_addback(t_cmds **lst, t_cmds *new);
void 		t_cmds_rmfirst(t_cmds **lst);
void 		free_cmds(t_cmds **lst);


/* parser.c */
t_cmds		*init_cmds(t_shell *list);
void 		print_cmds(t_cmds **lst);

#endif
