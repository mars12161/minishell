/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_multi_env_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 00:43:23 by yli               #+#    #+#             */
/*   Updated: 2023/07/21 15:50:49 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			check_dollar(char *str, int c);
int			ft_count_size(char *str, int c);
char		*ft_check_strjoin(char *s1, char *s2);
int			check_path_char(int c);

int	check_dollar(char *str, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_count_size(char *str, int c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

static char	*ft_strjoin_parse(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i++];
	}
	str[j] = 0;
	return (str);
}

char	*ft_check_strjoin(char *s1, char *s2)
{
	char	*str;

	str = NULL;
	if (s1 == NULL && s2 != NULL)
	{
		str = ft_strdup(s2);
		return (str);
	}
	if (s2 == NULL && s1 != NULL)
	{
		str = ft_strdup(s1);
		return (str);
	}
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 != NULL && s2 != NULL)
		str = ft_strjoin_parse(s1, s2);
	return (str);
}

int	check_path_char(int c)
{
	if (c >= 65 && c <= 90)
		return (0);
	return (1);
}
