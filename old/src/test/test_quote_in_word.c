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

char	*ft_substr(char const *s, unsigned int start, size_t len);

int check_dollar(char *str, int c) //how many
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

int ft_count_size(char *str, int c) //where
{
    int i;

    i = 1;
    while(str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (0);
}

	// while (str[i])
	// {
	// 	if (str[i] >= 33 && str[i] <= 126)
	// 		j++;
	// 	if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' '
	// 			|| str[i + 1] == '\t'))
	// 		break ;
	// 	i++;
	// }
char *ft_quote_in_str_1(char *str)
{
    int i;
    int j;
    char *result;

    //int size;

    i = ft_count_size(str, 39);
    j = ft_count_size(str, 34);
    //size = 0;
    if (j != 0 && i != 0 && j < i || (j != 0 && i == 0))
    {
        j += 1;
        while(str[j])
        {
            if (str[j] == 39 && str[j + 1] == 32)
                break ;
            else if (str[j] == 32)
                break ;
            //size++;
            j++;
        }
    }
    result = ft_substr((char const *)str, 0, j);
    return (result);
}

char *ft_check_quote_in_str(char *str)
{
    char *word;
    int i;
    int j;

    i = 0;
    j = 0;
	while (str[i])
	{
		if (str[i] >= 33 && str[i] <= 126)
			j++;
		if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' '
				|| str[i + 1] == '\t'))
			break ;
		i++;
	}
    word = ft_substr((char const *)str, 0, j);
    if (ft_count_size(word, 39) || ft_count_size(word, 34))
    {
        free(word);
        return (ft_quote_in_str_1(str));
    }
    return (word);
}



int main()
{
    char *str2;
    char    *str = "abc"cd"";

    str2 =  ft_check_quote_in_str(str);
    printf("%s\n", str2);
}