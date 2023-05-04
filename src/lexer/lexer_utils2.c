#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
/*
int	ft_strlen(char *str)
{
	int n = 0;

	while (*str)
	{
		n++;
		str++;		
	}
	return (n);
}

static int	strchar(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == ' ')
			return (i);
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	return (-2);
}

char	*ft_strdup(char *str)
{
	int n = 0;
	int len = ft_strlen(str);
	char *dup = (char*)malloc(sizeof(*dup) * len + 1);
	
	dup[len] = 0;
	
	while (str[n])
	{
		dup[n] = str[n];
		n++;	
	}
	return (dup);
}

char	*ft_strcpy(char *str, int i, int flag)
{
	int	size;
	char	*out;

	size = 0;
	if (flag == 0)
	{
		out = (char *)malloc(sizeof(char *) * i);
		if (!out)
			return (0);
		while(size < i - 1)
		{
			out[size] = str[size];
			size++;
		}
	}
	else
	{
		out = (char *)malloc(sizeof(char *) * (ft_strlen(str) - i + 1));
		if (!out)
			return (0);
		while(str[i])
		{
			out[size] = str[i];
			size++;
			i++;	
		}
	}
	out[size] = 0;
	return (out);
}



static char *split_line(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (0); // donothing return minishell
	j = strchar(str);
	//printf("j: %d\n", j);
	while(str[i])
	{
		if (j > 0)
			return (ft_strcpy(str, j + 1, 0));
		if (j == -1)
			return (ft_strdup(str));
		i++;
	}
	return (0);
}
*/

char    *creat_str(char *s1, char *s2, int len)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(s2[j] && j < len)
    {
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = '\0';
    return s1;
}

char    **ft_split(char *str)
{
    int i;
    int start;
    int end;
    int wc;
    int k;
    char **result;

    i = 0;
    wc = 0;
    while(str[i])
    {
        while(str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
            wc++;
        i++;
    }
    //printf("wc: %d\n", wc);
    result = (char **)malloc(sizeof(char *) * (wc + 1));
    if (!result)
        return 0;
    result[i] = 0;
    i = 0;
    k = 0;
    while(str[i])
    {
        while(str[i] == ' ' || str[i] == '\t')
            i++;
        start = i;
        //printf("start: %d\n", start);
        while(str[i] >= 33 && str[i] <= 126)
            i++;
        end = i;
        //printf("end: %d\n", end);
        if(start < end)
        {
            result[k] = malloc(sizeof(char) * (end - start));
            if (!result[k])
                return 0;
            result[k] = creat_str(result[k], &str[start], (end - start));
            k++;
        }
    }
    return result;
}
/*
int	main()
{
	char *str = readline("minishell: ");
	int	i = 0;
	char *out = split_line(str);
	//printf("from readline: %s\n", str);
	//printf("%s\n", out);
	while(out)
	{
		out = split_line(str);
		printf("%s",out);
		str = ft_strcpy(str, ft_strlen(out) + 1, 1);
	}
	//printf("%s",split_line(str));
	//printf("%s",split_line(str));
}
*/

static t_shell *new_node(char *str, enum e_token)
{
	t_shell *new_node;

	new_node = NULL;
	new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
	new_node->input = str;
    	new_node->len = ft_strlen(str);
	new_node->next = 0;
	return (new_node);
}

static t_shell *


