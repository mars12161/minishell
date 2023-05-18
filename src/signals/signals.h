/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:17:36 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/18 14:12:01 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

//#include "../../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

/* Functions */

void	sigint_handler(int signal);
void 	sigint_heredoc(int signal);
int 	change_attr(bool ctrl_chr);

#endif
