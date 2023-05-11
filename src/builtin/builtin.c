#include "builtin.h"

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

static int ft_spacetimes(char *str)
{
    int i;
    int wc;

    i = 0;
    wc = 0;
    while(str[i])
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
            wc++;
        i++;
    }
    return (wc);
}

static char **ft_split(char *str)
{
    char **result;
    int i;
    int factor;
    int k;

    factor = ft_spacetimes(str);
    result = (char **)malloc(sizeof(char *) * (factor + 1));
    if (!result)
        return (NULL);
    result[factor] = 0;
    factor = 0;
    i = 0;
    k = 0;
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        factor = i;
        while (str[i] >= 33 && str[i] <= 126)
            i++;
        if (factor < i)
        {
            result[k] = malloc(sizeof(char) * (i - factor + 1));
            if (!result[k])
                return (0);
            result[k] = creat_str(result[k], &str[factor], (i - factor));
            k++;
        }
    }
    return (result);
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

static t_builtin *new_node(char **str)
{
    t_builtin *new_node;
    int i;

    i = 0;
    new_node = NULL;
    new_node = (t_builtin *)malloc(sizeof(t_builtin));
    if (!new_node)
        return (NULL);
    new_node->command = str;
    while (str[i])
        i++;
    new_node->size = i;
    new_node->next = 0;
    return (new_node);
}

static int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
} //from libft.a

int	ft_error(char *str)
{
	int	i;

	i = 0;
    while (str[i])
		i++;
	write(2, str, i);
	write(2, "\n", 1);
    return (-1);
}

int    exec_builtin(t_builtin *node, t_env **env)
{
    if (!ft_strncmp(node->command[0], "echo", 4))
        return (ft_echo(node));
    else if (!ft_strncmp(node->command[0], "cd", 2))
        return (ft_cd(node, env));
    else if (!ft_strncmp(node->command[0], "pwd", 3))
        return (ft_pwd());
    else if (!ft_strncmp(node->command[0], "env", 3))
        return (ft_env(env));
    else if (!ft_strncmp(node->command[0], "export", 5))
        return (ft_export(node, env));
    else if (!ft_strncmp(node->command[0], "unset", 5))
        return (ft_unset(node, env));
    else
        return (-1);
}

int main(int argc, char **argv, char **envp)
{
    char *str = "unset HOME";
    char **result;
    t_builtin *node;
    t_env *env;

    result = ft_split(str);
    node = new_node(result);
    env = NULL;
    env = init_env(envp, env);
    exec_builtin(node, &env);
}