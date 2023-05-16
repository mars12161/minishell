/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:15:35 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/16 13:53:57 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	ft_sighandler(int signal)
{
	if (signal == EOF)
		printf("CTRL + D: EOF\n");
	if (signal == SIGINT)
		printf("CTRL + C: SIGINT\n");
	if (signal == SIGQUIT)
		printf("CTRL + \\: SIGQUIT\n");
}