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
/*
int main(int argc, char **argv, char **envp)
{
    int i;

    i = 0;
    while(envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
}
*/

// int main()
// {
//     int i;

//     i = -1;
//     while(i++ < 5)
//         printf("%d\n", i); //012345
// }
