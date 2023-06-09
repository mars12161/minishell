/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:17:08 by yli               #+#    #+#             */
/*   Updated: 2023/06/21 18:17:09 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_parse *node, t_env **env);

int ft_env(t_parse *node, t_env **env)
{
    t_env *temp;
    int fd;

    fd = ft_redirection_out(node);
    temp = *env;
    while (temp)
    {
        ft_putstr_fd(temp->content, fd);
        ft_putstr_fd("\n", fd);
        temp = temp->next;
    }
    return (0);
}