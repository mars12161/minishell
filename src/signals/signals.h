/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:17:36 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/16 16:19:46 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include "../../includes/minishell.h"
#include <signal.h>

typedef struct	s_sig
{
	int		sigint;
	int 	sigquit;
	pid_t 	pid;
}	t_sig;

void	sigint_handler(int signal);

#endif
