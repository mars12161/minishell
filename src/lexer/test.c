
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int ft_strlen_1(char *s)
{
    int n;

    n = 0;
    while(*s)
    {
        s++;
        n++;
    }
    return (n);
}

int ft_strlen_2(char *s)
{
    int n;

    n = 0;
    while(s[n])
        n++;
    return (n);
}

char ft_test(char *s)
{
    char *out;

    while(*s >= 33 && *s <= 126)
    {
        out += *s;
        s++;
    }
    return (out);
}


int main ()
{
    char *str = "aaaagd  cc!!";
    printf("%d\n", ft_strlen_2(str));
    printf("%s\n", ft_test(str));
}