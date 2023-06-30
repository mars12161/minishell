/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:47:56 by yli               #+#    #+#             */
/*   Updated: 2023/06/26 18:13:04 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_infile(t_parse *node);
int check_outfile(t_parse *node);
char    *str_ncpy(char *str, int n);
char	*ft_strjoin_path_cmd(char const *s1, char c, char const *s2);
char **ft_nsplit(char *str, int c);

int check_infile(t_parse *node)
{
    if (node->redirection_in == 0)
        return (0);
    else if (node->redirection_in == 1)
    {
        if (access(node->infilepath, F_OK))
        {
            ft_error("No such file or directory");
            return (-1);
        }
        return (open(node->infilepath, O_RDONLY));
    }
    return (-1);
}

int check_outfile(t_parse *node)
{
    if (node->redirection_out == 0)
        return (1);
    else if (node->redirection_out == 1)
        return (open(node->outfilepath, O_CREAT | O_WRONLY | O_TRUNC, 0644));
    else if (node->redirection_out == 2)
        return (open(node->outfilepath, O_CREAT | O_WRONLY | O_APPEND, 0644));
    return (-1);
}

char    *str_ncpy(char *str, int n)
{
    char    *result;
    int i;

    i = 0;
    result = malloc(sizeof(char) * (n + 1));
    if (!result)
        return (NULL);
    while (i < n)
        result[i++] = *str++;
    result[n] = 0;
    return (result);
}

char	*ft_strjoin_path_cmd(char const *s1, char c, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = c;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char **ft_nsplit(char *str, int c)
{
    char **result;
    int count;
    int i;
    int j;

    count = 0;
    count = check_dollar(str, c);
    result = malloc(sizeof(char *) * (count + 2));
    if (!result)
        return (NULL);
    result[count + 1] = NULL;
    i = 0;
    j = 0;
    while (i < count + 1)
    {
        while (str[j] != c)
            j++;
        result[i++] = str_ncpy(str, j);
        str = str + j + 1;
    }
    return (result);
} //2 can delete later
