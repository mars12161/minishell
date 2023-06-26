/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:55 by yli               #+#    #+#             */
/*   Updated: 2023/06/23 09:03:44 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_pwd(t_parse *node);

int ft_pwd(t_parse *node)
{
    static char pwd[PATH_SIZE];
    int fd;

    fd = ft_redirection_out(node);
    if (getcwd(pwd, PATH_SIZE))
    {
        ft_putstr_fd(pwd, fd);
		write(fd, "\n", 1);
        return (0);
    }
    else
        return (-1);
}