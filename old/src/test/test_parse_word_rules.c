# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "../../libft/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < (size -1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*ret;

	len = ft_strlen(s);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, len + 1);
	return (ret);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}

int ft_count_size_lexer(char *str, int c) //where
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret = (char *)malloc(
			sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ret[j++] = s2[i];
		i++;
	}
	ret[j] = 0;
	return (ret);
}

static char *ft_parse_word_rules_strjoin(char *sub1, char *sub2, t_env **env)
{
    char *subresult1;
    char *subresult2;
    char *result;

    subresult1 = ft_parse_dollar_frame(sub1, *env);
    subresult2 = ft_parse_dollar_frame(sub2, *env);
    if (!subresult1 && subresult2)
        return (subresult2);
    if (!subresult2 && subresult1)
        return (subresult1);
    if (!subresult1 && !subresult2)
        return (NULL);
    result = ft_strjoin(subresult1, subresult2);
    ft_free_3str(subresult1, subresult2, NULL);
    return (result);
}

static char *ft_parse_word_rules_substr(char *str, int signal, int size, t_env **env)
{
    char *sub1;
    char *sub2;
    char *sub3;
    int i;

    sub1 = ft_substr(str, 0, size);
    printf("sub1: %s\n", sub1);
    str += size;
    printf("str: %s\n", str);
    i = ft_count_size_lexer(str, signal);
    sub2 = ft_substr(str, 1, i);
    printf("sub2: %s\n", sub2);
    if (i == ft_strlen(str))
        return (ft_parse_word_rules_strjoin(sub1, sub2, env));
    else
    {
        sub3 = ft_substr(str, i, ft_strlen(str) - i);
        return (ft_strjoin(ft_parse_word_rules_strjoin(sub1, sub2, env), sub3));
    }
    return (NULL);
}

char *ft_parse_word_rules(char *str, t_env **env)
{
    int i;
    int j;
    char *result;

    i = ft_count_size_lexer(str, 34);
    j = ft_count_size_lexer(str, 39);
    if (i < j) //meet '' first
    {
        result = ft_parse_word_rules_substr(str, 34, i, env);
        printf("result in parse word rules0: %s\n", result);
    }
    else if (j < i) //meet ' first
    {
        result = ft_parse_word_rules_substr(str, 39, j, env);
        printf("result in parse word rules0: %s\n", result);
    }
    else if (i == j && i == ft_strlen(str))
        return (ft_parse_dollar_frame(str, *env));
    i = ft_count_size_lexer(result, 34);
    j = ft_count_size_lexer(result, 39);
    if (i != j)
        resturn (ft_parse_word_rules(result, env));
}