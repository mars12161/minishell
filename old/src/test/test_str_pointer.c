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

// int main()
// {
//     char *str = "abc";
//     char *cpy;

//     cpy = str;
//     printf("%s\n", str);
//     printf("%s\n", str + 1);
//     printf("%s\n", cpy);
//     printf("%s\n", cpy + 1);
//     printf("%s\n", cpy - 1);
//     printf("%s\n", str);
//     printf("%s\n", cpy);
// }

int main()
{
    int i;
    char *str = "abc";

    i = 0;
    printf("%d\n",(int)strlen(str));

}