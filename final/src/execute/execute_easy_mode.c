/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_easy_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:11:35 by yli               #+#    #+#             */
/*   Updated: 2023/06/30 17:40:00 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_easy_mode(t_parse_arr *cmmarr, t_env *env);

int	execute_easy_mode(t_parse_arr *cmmarr, t_env *env)
{
    char **envp;

    redir_child(cmmarr->cmm[0]);
    envp = ft_env_str(&env);
    printf("envp: %s\n", envp[0]);
    printf("envp: %s\n", envp[1]);
    ft_executer(cmmarr->cmm[0]->whole_line, envp);
    return (0);
}

