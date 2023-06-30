/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:17:30 by yli               #+#    #+#             */
/*   Updated: 2023/06/30 08:42:00 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_free_3str(char *str1, char *str2, char *str3);

void ft_free_3str(char *str1, char *str2, char *str3)
{
    
    free(str1);
    free(str2);
    free(str3);
}