/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:16:55 by yli               #+#    #+#             */
/*   Updated: 2023/06/21 18:16:57 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_parse *node);

int ft_pwd(t_parse *node)
{
    static char pwd[PATH_SIZE];
    int fd;

    fd = ft_redirection_out(node);
    if (getcwd(pwd, PATH_SIZE))
    {
        ft_putstr_fd(pwd, fd);
        return (0);
    }
    else
        return (-1);
}