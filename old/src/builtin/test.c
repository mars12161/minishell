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
# include <readline/readline.h>
/*
int main()
{
    char *str = "agcd";

    str += 1;
    printf("%s\n", str);
}
*/

/*
int ft_check_each_n(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int ft_check_n(char *str)
{
    int i;

    i = 0;
    if (str[0] == '-')
    {
        str += 1;
        if (ft_check_each_n(str))
            return (1);
        else 
            return (0);
    }
    else
        return (0);
}

int main()
{
    char *str = "-nnbnnn";

    printf("%d\n", ft_check_n(str));
}
*/
/*
int main()
{
    const char *name = "PATH";
    const char *env_p = getenv(name);
    if (env_p)
        printf("1. %s\n 2. %s\n ", name, env_p);
}///nfs/homes/yli/bin:/nfs/homes/yli/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
*/
/*
int main()
{
    const char *name = "PATH";
    int i = chdir(name);
    if (i == 0)
        printf("%s ", name);
}
*/
/*
int main()
{
    char pwd[4096];

    if (getcwd(pwd, 4096))
    {
        printf("%s", pwd);
        return (0);
    }
    else
        return (-1);
}
*/
/*
int main()
{
    char *str = "echo  -n 45";
    char **result;
    t_builtin *node;

    result = ft_split(str);
    node = new_node(result);
    //printf("in main:%s", str);
    ft_echo(node);
}
*/ //for echo

int   main (int argc, char **argv, char **envp)
{
    int     i;

    i = 0;
    while(envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
}
