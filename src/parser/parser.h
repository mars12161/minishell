/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:03:23 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/06 16:50:03 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../includes/minishell.h"

typedef struct s_cmds
{
	char			**cmd;
	struct s_cmds	*next;
}	t_cmds;

/* Functions */

int	parser(t_shell *list);

#endif
