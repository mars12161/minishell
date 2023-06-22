/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:17:30 by yli               #+#    #+#             */
/*   Updated: 2023/06/22 16:17:34 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_3str(char *str1, char *str2, char *str3);

void ft_free_3str(char *str1, char *str2, char *str3)
{
    
    ft_free_str(&str1);
    ft_free_str(&str2);
    ft_free_str(&str3);
}