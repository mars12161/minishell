#ifndef MINISHELL
# define MINISHELL

# include "libft.h"
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

# define BUFFER_SIZE 4000
# define STDIN 0
# define STDOUT 1
# define STDERR 2
