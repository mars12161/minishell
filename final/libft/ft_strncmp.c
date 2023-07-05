/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:20:44 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/05 17:11:21 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


// #include <stdio.h>
// #include <string.h>

// // int main()
// // {
// // 	int i = ft_strncmp("test\200", "test\0", 6);
// // 	int j = strncmp("test\200", "test\0", 6);
// // 	printf("%i\n%i\n", i, j);
// // }

// int	main()
// {
// 	char *str1 = "PATH=/nfs/homes/yli/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
// 	char *str2 = "PATH=6";
// 	int	i = ft_strncmp(str1, str2, 5);
// 	printf("%d\n", i);
// }