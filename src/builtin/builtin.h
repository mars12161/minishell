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
# define PATH_SIZE 4096

typedef struct s_builtin
{
    char **command;
    int size;
    struct s_builtin *next;
}   t_builtin;

typedef struct s_env
{
    char *content;
    struct s_env *next;
}   t_env;


void    ft_free(char **str);
int    exec_builtin(t_builtin *node, t_env **env);
int main();

int ft_pwd(void);

int ft_echo(t_builtin *node);

t_env *new_node_env(char *str);
void ft_add_tail_env(t_env **env, t_env *new_node);
t_env *init_env(char **envp, t_env *env);
int ft_env(t_env **env);

int ft_export(t_builtin *node, t_env **env);

size_t	ft_strlen(const char *str);
char	*ft_strtrim(char const *s1, char const *set);

int ft_cd(t_builtin *node, t_env **env);

int	ft_error(char *str);

int ft_unset(t_builtin *node, t_env **env);

#endif