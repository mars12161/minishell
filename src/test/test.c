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

static int ft_count_size(char *str)
{
    int i;

    i = 1;
    while(str[i])
    {
        if (str[i] == 36)
            return (i);
        i++;
    }
    return (0);
}

// int main()
// {
//     char *str = "$USER $USER";
//     int i = ft_count_size(str);

//     printf("%d\n", i);
// }

// $USER$USER 5
// $USER $USER 6

