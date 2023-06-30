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




typedef struct s_env
{
    char *content;
    struct s_env *next;
}   t_env;

char *ft_parse_dollar_frame(char *str, t_env *env);

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
} /// from libft.a

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < (size -1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
char	*ft_strdup(const char *s)
{
	int		len;
	char	*ret;

	len = ft_strlen((char *)s);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, len + 1);
	return (ret);
} //from libft.a

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (NULL);
	//if (start >= (unsigned int)ft_strlen(s))
	//	len = 0;
	//if (ft_strlen(s + start) < len)
	//	len = ft_strlen(s + start);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
} //from libft.a

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i++];
	}
	i = 0;
	free((void *)s1);
	while (s2[i])
	{
		str[j++] = s2[i++];
	}
	str[j] = 0;
	return ((char *)str);
}

int	ft_setcheck(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (0);
	i = 0;
	start = 0;
	end = ft_strlen((char *)s1);
	while (s1[start] && ft_setcheck(s1[start], set))
		start++;
	while (end > start && ft_setcheck(s1 [end -1], set))
		end --;
	str = ((char *)malloc(sizeof(char) * (end - start + 1)));
	if (!str)
		return (0);
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}


void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


t_env *new_node_env(char *str)
{
    t_env *new_node;
    int i;

    i = 0;
    new_node = NULL;
    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->content = str;
    new_node->next = 0;
    return (new_node);
}

void ft_add_tail_env(t_env **env, t_env *new_node)
{
    t_env *temp;

    if (!new_node)
        return ;
    if (!*env)
    {
	*env = new_node;
        return ;
    }
    temp = *env;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
}

t_env *init_env(char **envp, t_env *env)
{
    int     i;

    i = 0;
    while(envp[i])
    {
        ft_add_tail_env(&env,new_node_env(envp[i]));
        i++;
    }
    return (env);
}

int ft_env(t_env **env)
{
    t_env *temp;

    temp = *env;
    while (temp)
    {
        printf("%s\n", temp->content);
        temp = temp->next;
    }
    return (0);
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

void ft_free_3str(char *str1, char *str2, char *str3)
{
    
    ft_free_str(&str1);
    ft_free_str(&str2);
    ft_free_str(&str3);
}


static int check_dollar(char *str, int c) //how many
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

static int ft_count_size(char *str, int c) //where
{
    int i;

    i = 1;
    while(str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (0);
}

char	*ft_strjoin_parse(char *s1, char *s2) //start from path
{
	char	*str;
	size_t	i;
	size_t	j;

    if (s1 == NULL)
    {
        str = ft_strdup(s2);
        return (str);
    }
    if (s2 == NULL)
    {
        str = ft_strdup(s1);
        return (str);
    }
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i++];
	}
	str[j] = 0;
	return (str);
}

char    *ft_expand(char *str, t_env **env)
{
    t_env   *temp;
    char    *path;
    char    *result;

    temp = *env;
    while(temp)
    {
        
        if (!strncmp(temp->content, str, ft_strlen(str)))
        {
            path = ft_strtrim(temp->content, str);
            if (*path != '=')
                return (NULL);
            //printf("path: %s\n", path);
            result = ft_strtrim(path, "=");
            return (result);
        }
        temp = temp->next;
    }
    return (NULL);
}

static char *ft_parse_dollar_core_utils(char *str, t_env *env, int c) // split by c
{
    char *str2;
    char *str3;
    char *path;
    char *result;

    //printf("4: in ft_parse_dollar_core_utils1 start\n");
    str2 = ft_substr((char const *)str, 1, ft_count_size(str, c) - 1);
    path = ft_expand(str2, &env);
    str3 = ft_substr((char const *)str, ft_count_size(str, c), ft_strlen((char *)str));
    result = ft_strjoin_parse(path, str3);
    free(str2);
    free(str3);
    free(path);
    // printf(" result: %s\n", result);
    // printf("4: in ft_parse_dollar_core_utils finish \n\n\n");
    return (result);
}

static char *check_expand_path_space(char *str, t_env *env) // parse path with space
{
    int space;
    int dollar;
    char *result;

    //printf("3: in check_expand_path_space1 start\n");
    space = ft_count_size(str, 32);
    dollar = ft_count_size(str, 36);
    result = NULL; 
    if (!space && !dollar) // one $ no space "$USER"
    {
        str += 1;
        result = ft_expand(str, &env);
    }
    else if (!dollar && space) // "$USER   "
        result = ft_parse_dollar_core_utils(str, env, 32);
    else if (space < dollar)// more $ more space && "$USER   $USER"
        result = ft_parse_dollar_core_utils(str, env, 32);
    else //more $ more space && "$USER$USER agc"
        result = ft_parse_dollar_core_utils(str, env, 36);
    //printf("3: in check_expand_path_space2 finish\n\n\n");
    return (result);   
}

static char *ft_parse_dollar_core(char *str, t_env *env)
{
    char *str1;
    char *str2;
    char *path;
    char *result;

    if (*str == '$')
        result = check_expand_path_space(str, env);
    else
    {
        str1 = ft_substr((char const *)str, 0, ft_count_size(str, 36));
        //printf(" str1: %s\n", str1);
        str2 = ft_substr((char const *)str, ft_count_size(str, 36), ft_strlen((char *)(str)) - ft_count_size(str, 36));
        //printf(" str2: %s\n", str2);
        path = check_expand_path_space(str2, env);
        //printf(" path: %s\n", path);
        result = ft_strjoin_parse(str1, path);
        free(str1);
        free(str2);
        free(path);
    }
    return (result);
}

char *ft_parse_dollar_frame(char *str, t_env *env)
{
    char *result;
    //char *result2;

    //printf("1: in ft_parse_dollar_frame start \n");
    //result = NULL;
    //result2 = NULL;
    if (!check_dollar(str, 36)) //"abc  "
        return (str);
    else if (check_dollar(str, 36)) // "abc $USER" "abc $USER   " "abc $USER $USER  " "abc $USER def" "$USER$USER" "$USER  $USER" "$USER$USER dgc"
        result = ft_parse_dollar_core(str, env);
    if (check_dollar(result, 36))
        result = ft_parse_dollar_frame(result, env);
    // printf(" final_result: %s\n", result);
    // printf("1: in ft_parse_dollar_frame end \n\n");
    return(result);
}
//worked now

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env;
//     char *result;
//     char *str = "abc $USER $USE $USER dd";

// 	(void)argc;
// 	(void)argv;
// 	env = NULL;
//     env = init_env(envp, env);
//     result = ft_parse_dollar_frame(str, env);
//     printf("result in main: %s\n", result);
//     free(result);
// } 