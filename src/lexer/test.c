
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main ()
{
    char *str = "    space!!   ";
    int i = 0;
    int space = 0;

    while (str[i])
    {
        if (str[i] == ' ')
            space++;
        if (str[i] == 32 && str[i + 1] != 32)
            break ;
        i++;
    }
    str += 4;
    printf("space: %d\n", space);
    printf("i: %d\n", i);
    printf("%s\n", str);
}