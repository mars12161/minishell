#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
//#include "lexer.h"

char *creat_str(char *s1, char *s2, int len)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(s2[j] && j <len)
    {
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = '\0';
    return (s1);
}

int ft_spacetimes(char *str)
{
    int i;
    int wc;

    i = 0;
    wc = 0;
    while(str[i])
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
            wc++;
        i++;
    }
    return (wc);
}

char **ft_split(char *str)
{
    char **result;
    int i;
    int factor;
    int k;

    factor = ft_spacetimes(str);
    result = (char **)malloc(sizeof(char *) * (factor + 1));
    if (!result)
        return (0);
    result[factor] = 0;
    factor = 0;
    i = 0;
    k = 0;
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        factor = i;
        while (str[i] >= 33 && str[i] <= 126)
            i++;
        if (factor < i)
        {
            result[k] = malloc(sizeof(char) * (i - factor));
            if (!result[k])
                return (0);
            result[k] = creat_str(result[k], &str[factor], (i - factor));
            k++;
        }
    }
    return (result);
}

int main()
{
    char *in = "abc de    fff 13#"
    char    **result = ft_split(in);

    printf("%s", result[0]);
    printf("%s", result[1]);
    printf("%s", result[2]);
    printf("%s", result[3]);
    printf("%s", result[4]);
}