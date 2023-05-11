#ifndef BUILTIN_H
# define BUILTIN_H

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
# include PATH_SIZE 4096

typedef struct s_builtin
{
    char **command;
    int size;
    struct s_builtin *next;
}   t_builtin;


void    ft_echo(t_builtin *node);

void    ft_free(char **str);
int main();

#endif