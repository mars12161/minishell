/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:17:30 by yli               #+#    #+#             */
/*   Updated: 2023/07/05 19:25:17 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_free_3str(char *str1, char *str2, char *str3);
void    ft_free_str(char **str);

void ft_free_3str(char *str1, char *str2, char *str3)
{
    
    free(str1);
    free(str2);
    free(str3);
}

void    ft_free_str(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != NULL)
        {
            free(str[i]);
            i++;
        }
        // str[i] = NULL;
    }
    free (str);
}
