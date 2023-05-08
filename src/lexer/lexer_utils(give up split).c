#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
static char *creat_str(char *s1, char *s2, int len)
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
    return (s1);
}

int ft_splittimes(char *str)
{
    int i;
    int wc;

    i = 0;
    wc = 0;
    while(str[i])
    {
        if ((str[i] == ' ' || str[i] == '\t') && str[i + 1] >= 33 && str[i + 1] <= 126)
            wc++;
        if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
            wc++;
        i++;
    }
    printf("wc: %d\n", wc);
    return (wc);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char **ft_split(char *str)
{
    char **result;
    int factor;
    int i;
    int flag1;
    int flag2;
    int k;

    factor = ft_splittimes(str);
    result = (char **)malloc(sizeof(char *) * (factor + 1));
    if (!result)
        return (0);
    result[factor] = 0;
    i = 0;
    flag1 = 0;
    flag2 = 0;
    k = 0;
    while(i <= ft_strlen(str))
    {
        printf("i: %d\n",i);
        if ((str[i] == ' ' || str[i] == '\t') && str[i + 1] >= 33 && str[i + 1] <= 126)
            flag1 = i + 1;
        printf("flag1: %d\n", flag1);
        if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
            flag2 = i + 1;
        printf("flag2: %d\n", flag2);
        if (flag1 < flag2)
        {
            result[k] = malloc(sizeof(char) * (flag2 - flag1 + 1));
            result[k] = creat_str(result[k], &str[flag1], (flag2 - flag1));
            flag1 = 0;
            //printf("in flag1 > flag2: result[%d]:%s", k, result[k]);
            k++;
        }
        if (flag1 > flag2)
        {
            result[k] = malloc(sizeof(char) * (flag1 - flag2 + 1));
            result[k] = creat_str(result[k], &str[flag2], (flag1 - flag2));
            flag2 = 0;
            //printf("in flag1 > flag2: result[%d]:%s", k, result[k]);
            k++;
        }
        i++;
    }
    return (result);
}
int main()
{
    char *str = "echo '34";
    char    **result = ft_split(str);

    printf("result[0]:%s\n", result[0]);
    printf("result[1]:%s\n", result[1]);
    printf("result[2]:%s\n", result[2]);
    printf("result[3]:%s\n", result[3]);
    printf("result[4]:%s\n", result[4]);
    printf("result[5]:%s\n", result[5]);
}




void    ft_free(char **str)
{
    int i;
    if (!*str)
        return ;
    i = 0;
    while(str[i])
    {
        if (str[i] != NULL)
        {
            free(str[i]);
            i++;
        }
        *str =NULL;
    }
    free(str);
}