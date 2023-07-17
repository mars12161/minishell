/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_2_echo2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:14:42 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/17 10:20:41 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo_help(t_parse *node, int fd)
{
	if (node->wline_count == 1)
	{
		if (fd != 1)
			close(fd);
		return (0);
	}
	return (0);
}
