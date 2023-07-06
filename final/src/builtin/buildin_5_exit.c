/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_5_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:49 by yli               #+#    #+#             */
/*   Updated: 2023/07/06 22:54:18 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exit(t_parse *node);

/* TODO Free everything */

static int	ft_atoi_exit(const char *str)
{
	int	i;
	int	neg;
	int	retval;

	i = 0;
	neg = 1;
	retval = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg = neg * (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			retval = (retval * 10) + (str[i] - '0');
		else
			return (2);
		i++;
	}
	return (retval * neg);
}

int	ft_exit(t_parse *node)
{
	if (node->wline_count == 2)
	{
		globe.g_exit = ft_atoi_exit(node->whole_line[1]);
		printf("exit\n");
		exit (globe.g_exit);
	}
	else if (node->wline_count >= 3)
	{
		ft_error_optimal("too many arguments", 1);
		return (globe.g_exit);
	}
	printf("exit\n");
	exit(0);
}
