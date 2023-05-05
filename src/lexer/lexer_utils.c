#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"

int	ft_strlen(char *str);
char *split_line(char *str);

int	ft_strlen(char *str)
{
	int n = 0;

	while (*str)
	{
		n++;
		str++;		
	}
	return (n);
}// use from libft.a

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

static char	*ft_strdup(char *str)
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
}// use from libft.a

static char	*ft_strcpy(char *str, int i, int flag)
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

char *split_line(char *str)
{
	if (!str)
		return (0); // donothing return minishell
	if (strchar(str) > 0)
		return (ft_strcpy(str, strchar(str) + 1, 0));
	else if (strchar(str) == -1)
		return (ft_strdup(str));
	return (0); //j == -2
}

