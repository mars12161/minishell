/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_5_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:49 by yli               #+#    #+#             */
/*   Updated: 2023/07/17 10:05:38 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exit(t_parse *node);

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

static int	ft_check_num_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_parse *node)
{
	if (node->wline_count == 2)
	{
		g_exit = ft_atoi_exit(node->whole_line[1]);
		printf("exit\n");
		if (ft_check_num_in_str(node->whole_line[1]))
			ft_error_optimal("numeric argument required", 2);
		return (-1);
	}
	else if (node->wline_count >= 3)
	{
		ft_error_optimal("too many arguments", 1);
		return (g_exit);
	}
	printf("exit\n");
	return (-1);
}
