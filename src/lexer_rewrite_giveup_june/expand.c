#include "lexer.h"

char    *ft_expand(char *str, t_env **env)
{
    t_env   *temp;
    char    *path;
    char    *result;

    temp = *env;
    while(temp)
    {
        if (!strncmp(temp->content, str + 1, ft_strlen(str)))
        {
            path = ft_strtrim(temp->content, str);
            result = ft_strtrim(path, "=");
            ft_free_str(&path);
            return (result);
        }
        temp = temp->next;
    }
    return (NULL);
}

void    ft_free_str(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (*str != NULL)
        {
            free(str[i]);
            i++;
        }
        *str = NULL;
    }
    free (str);
}