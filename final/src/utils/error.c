/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:49:10 by yli               #+#    #+#             */
/*   Updated: 2023/07/05 23:15:24 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    ft_error(char *str);
void    ft_error_optimal(char *str, int exit);

void    ft_error(char *str)
{
	int	i;

	i = 0;
    while (str[i])
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	exit(1);
}

void    ft_error_optimal(char *str, int exit)
{
	int	i;

	i = 0;
    while (str[i])
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	globe.g_exit = exit;
}