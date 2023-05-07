/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:03:23 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/07 13:33:58 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../includes/minishell.h"
# include "../lexer/lexer.h"

typedef struct s_cmds
{
	char			**cmd;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

/* Functions */
/* parser_utils.c */
int		count_args(t_shell *list);
int		count_pipes(t_shell *list);
t_shell	*get_next_pipe(t_shell *list);

/* parser_utils2.c */
t_cmds	*new_cmds(char **str);
t_cmds	*init_cmd(t_shell *list);

/* parser.c */
int		parser(t_shell *list);

#endif
