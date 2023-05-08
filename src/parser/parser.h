/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:03:23 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/08 15:40:49 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../includes/minishell.h"
# include "../lexer/lexer.h"

/* Linked list to store all commands
 * before a pipe in a node
 */
typedef struct s_cmds
{
	char			**cmd;
	t_shell			*redirections;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

/* Struct to store linked list
 * from lexer and a linked list
 * with all redirections */
typedef struct s_parser
{
	t_shell			*list;
	t_shell			*redirections;
}	t_parser;


/* Functions */
/* parser_utils.c */
t_parser	init_parser(t_shell *list);
int			count_args(t_shell *list);
int			count_pipes(t_shell *list);
t_shell		*get_next_pipe(t_shell *list);

/* parser_utils2.c */
t_cmds		*new_cmds(char **str, t_shell *redirections);
t_cmds		*init_cmd(t_shell *list);

/* parser_utils2.c */

/* parser.c */
int		parser(t_shell *list);

#endif
