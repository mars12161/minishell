
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

int ft_count_size_lexer(char *str, int c, int start) //where
{
    while(str[start])
    {
        if (str[start] == c)
            return (start);
        start++;
    }
    return (start);
}

int ft_i_start_from_sq(char *str, int pre);
int ft_i_start_from_word(char *str, int pre);
int ft_i_start_from_dq(char *str, int pre);

static int ft_check_quote_in_word(char *str)
{
    int i;
    int j;
    int k;

    i = ft_count_size_lexer(str, 34, 0);
    j = ft_count_size_lexer(str, 39, 0);
    k = (int)ft_strlen(str);
    // printf("%d\n", ft_count_size_lexer(str, 34, 0));
    // printf("%d\n", ft_count_size_lexer(str, 39, 0));
    // printf("%d\n", (int)ft_strlen(str));
    if (i == j && i == k && j == k)
        return (0); //not find
    else
        return (1);
}

int ft_check_quote_before_space(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == 34 || str[i] == 39)
            return (-1);
        if (str[i] >= 33 && str[i] <= 126)
            j++;
        if (str[i] >= 33 && str[i] <= 126 && str[i + 1] == 32)
            break ;
        i++;
    }
    return (j);
}

int ft_i_start_from_word(char *str, int pre)
{
    int i;
    int j;

    printf("pre word: %d\n", pre);
    if (ft_check_quote_before_space(str) != -1)
        return (ft_check_quote_before_space(str) + pre);
    if (!ft_check_quote_in_word(str))
    {
        i = ft_count_size_lexer(str, 32, 0);
        return (i + pre);
    }
    else if (str[0] == 34)
        return (ft_i_start_from_dq(str, pre));
    else if (str[0] == 39)
        return (ft_i_start_from_sq(str, pre));
    else
    {
        i = ft_count_size_lexer(str, 34, 0);
        j = ft_count_size_lexer(str, 39, 0);
        if (i < j)
        {
            pre += i;
            str += i;
            printf("return from dq str: %s\n", str);
            return (ft_i_start_from_dq(str, pre));
        }
        else
        {
            pre += j;
            str += j;
            return (ft_i_start_from_sq(str, pre));
        }
    }
    return (0);

}

int ft_i_start_from_sq(char *str, int pre)
{
    int i;

    i = ft_count_size_lexer(str, 39, 1);
    printf("sq i : %d ", i);
    printf("pre : %d ", pre);
    printf("strlen : %s %d\n", str, (int)ft_strlen(str));
    
    if (i == ft_strlen(str) - 1 || i == ft_strlen(str) - 2 || i == ft_strlen(str) && str[pre] == 39)
        return (ft_strlen(str) + pre);
    if (str[i + 1] == 39)
    {
        pre += i + 1;
        str += i + 1;
        return (ft_i_start_from_dq(str, pre));
    }
    else
    {
        pre += i + 1;
        str += i + 1;
        return ft_i_start_from_word(str, pre);
    }
    return (-1);
}


int ft_i_start_from_dq(char *str, int pre)
{
    int i;

    i = ft_count_size_lexer(str, 34, 1);
    printf("dq i : %d ", i);
    printf("pre : %d ", pre);
    printf("strlen : %s %d\n", str, (int)ft_strlen(str));
    
    if (i == ft_strlen(str) - 1 || i == ft_strlen(str) - 2 || i == ft_strlen(str) && str[pre] == 34)
    {
        printf("out from here0\n");
        return (ft_strlen(str) + pre);
    }
    if (str[i + 1] == 32)
        return (pre + i + 1);
    if (str[i + 1] == 34)
    {
        pre += i + 1;
        str += i + 1;
        printf("out from here1\n");
        return (ft_i_start_from_dq(str, pre));
    }
    else
    {
        pre += i + 1;
        str += i + 1;
        printf("out from here2 %s %d\n", str, pre);
        return ft_i_start_from_word(str, pre);
    }  
    return (-1);
}

int main()
{
    char *str =  readline("[test:]");
    int i;
    char *result;

    if (str[0] == 34)
    {
        printf("i from dq\n");
        i = ft_i_start_from_dq(str, 0);
    }
    else if (str[0] == 39)
    {
        printf("i from sq\n");
        i = ft_i_start_from_sq(str, 0);
    }
    else
    {
        printf("i from word\n");
        i = ft_i_start_from_word(str, 0);
    }
    printf("main %d\n", i);
    printf("main %s\n", ft_substr(str, 0, i));
    printf("main str: %s\n", str);
}