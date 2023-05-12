typedef struct s_parse
{
    char 	**command;
    int 	size;
    int	redirection_in;
    int	redirection_out;
    char *infilepath;  //if redirection_in == 0, infilepath = NULL
    char *outfilepath; //if redirection_out == 0, outfilepath = NULL
    int pipe;
    int	fd[2];   //if pipe == 0, fd = NULL
    struct s_parse *next;
}   t_parse;

void excute_interagration(t_parse *parse, t_env **env)
{
    while (parse)
    {
        if (exec_builtin(parse, env) == 1)
            ft_execute(parse, env);
        else if (exec_builtin(parse, env) == -1)
            return (-1);
        parse = parse->next;
    }
}

char    **ft_get_path(t_parse *parse, t_env **env)
{
    char **path;
    t_env *temp;

    temp = *env;
    while(temp)
    {
        if (!strncmp(temp->content, "PATH=", 5))
        {
            path = ft_split(envp[i] + 5, ':');
            return (path);
        }
        temp = temp->next;
    }
    ft_error("did not find the path\n");
    return (NULL);
}

char	*ft_strjoin_path_cmd(char *s1, char c, char *s2)
{
	char	*str;
	int	i;
	int	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = c;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	**ft_check_cmd(char *cmd)
{
	char	**command;

	if (cmd == 0)
		ft_perror("0");
	else if (cmd[0] == '\0')
		ft_perror("0");
	command = ft_split(cmd, ' ');
	if (command == 0)
		ft_perror("1");
	return (command);
}

void	ft_executer(char *cmd, char **envp)
{
	char	**command;
	char	**path;
	char	*path_cmd;
	int		i;

	command = ft_check_cmd(cmd);
	path = split_path(envp);
	if (path[0] == NULL)
		ft_perror("2");
	i = 0;
	while (path[i])
	{
		path_cmd = ft_strjoin_path_cmd(path[i], '/', command[0]);
		if (access(path_cmd, F_OK) != -1)
		{
			if (execve(path_cmd, command, NULL) == -1)
				ft_perror("3");
		}
		free (path_cmd);
		i++;
	}
	check_free_all(command);
	check_free_all(path);
	ft_perror("4");
}


int ft_unset(t_builtin *node, t_env **env)
{
    t_env *temp;
    char *result;
    if (node->size == 1)
        return (ft_error("unset: not enough arguments"));
    temp = *env;
    while (temp)
    {
        if (!strncmp(temp->content, node->command[1], ft_strlen(node->command[1])))
        {
            del_node(env,temp);
            return (0);
        }
        temp = temp->next;
    }
    //ft_env(env);
    return (0);
}

char	**split_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH=", 5))
		{
			path = ft_split(envp[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_path_cmd(char const *s1, char c, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = c;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}