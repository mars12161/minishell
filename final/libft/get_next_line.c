/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 15:06:25 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/10 14:00:42 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*gnl_strjoin(char *s1, char *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_calloc(sizeof(char), 1);
	if (!s1 && !s2)
		return (NULL);
	ret = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i])
			ret[i] = s1[i];
	while (s2[j])
		ret[i++] = s2[j++];
	free(s1);
	return (ret);
}

static char	*ft_read_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	signal(SIGQUIT, SIG_IGN);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_makeremainder(int fd, char *remainder)
{
	char	*buff;
	int		bytes;

	buff = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(remainder, '\n') && bytes)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (!bytes)
			return (NULL);
		if (bytes == -1)
		{
			free(remainder);
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		remainder = gnl_strjoin(remainder, buff);
	}
	free(buff);
	return (remainder);
}

static char	*ft_newremainder(char *remainder)
{
	int		j;
	int		i;
	char	*ret;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	ret = ft_calloc(sizeof(char), ((ft_strlen(remainder) - i + 1)));
	if (!ret)
	{
		free(remainder);
		return (NULL);
	}
	j = 0;
	i++;
	while (remainder[i])
		ret[j++] = remainder[i++];
	ret[j] = '\0';
	free(remainder);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = ft_makeremainder(fd, remainder);
	if (!remainder)
		return (NULL);
	line = ft_read_line(remainder);
	remainder = ft_newremainder(remainder);
	return (line);
}
