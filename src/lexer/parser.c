/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:43:01 by yli               #+#    #+#             */
/*   Updated: 2023/06/05 19:43:02 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_shell
{
	char *input;
	int	len;
	enum e_token type;
	enum e_state state;
	struct s_shell *next;
}	t_shell;

typedef struct s_parse
{
    char 	*command;
    int 	size;
    int	redirection_in;
    int	redirection_out;
    char *infilepath;  //if redirection_in == 0, infilepath = NULL
    char *outfilepath; //if redirection_out == 0, outfilepath = NULL
    int pipe;
    int	fd[2];   //if pipe == 0, fd = NULL
}   t_parse;

typedef struct s_parse_arr
{
	t_parse **cmm;
	int	check;
	int	size;
}	t_parse_arr;

t_parse *parse_init(void)
{
	t_parse *node;

	node = malloc(sizeof(t_parse) * 1);
	node->command = malloc(sizeof(char) * 100);
	node->infilepath = malloc(sizeof(char) * 100);
	node->outfilepath = malloc(sizeof(char) * 100);
	if (!node || !node->command || !node->infilepath || !node->outfilepath)
		return (NULL);
	node->redirection_in = 0;
	node->redirection_out = 0;
	node->pipe = 0;
	return (node);
}

t_parse_arr *parse_array_create(t_shell *head)
{
	t_parse **cmm;
	t_parse_arr *cmm_arr;

	if (!head)
		return (NULL);
	cmm_arr = malloc(sizeof(t_parse_arr));
	if (!cmm_arr)
		return (NULL);
	cmm_arr->size = get_size_cmmarr(head); //todo
	cmm = create_cmm(head, &cmm_arr->size);
	if (!cmm)
		return (NULL);
	else
		cmm_arr->cmm = cmm;
	return (cmm_arr);
}

static	t_parse **create_cmm(t_shell *head, int *size)
{
	t_parse **cmm;
	t_shell *temp;
	int	i;

	i = 0;
	cmm = malloc(sizeof(t_parse) * *size);
	if (!cmm)
		return (NULL);
	temp = head;
	while (temp)
	{
		if (i < *size)
		{
			cmm[i] = parse_shell(temp);
			if (!cmm[i])
				return (NULL);
		}
		while (temp && temp->type != 5)
			temp = temp->next;
		if (temp)
			temp = temp->next;
		i++;
	}
	return (cmm);
}

void	parse_cmm(t_parse *cmm, t_shell *temp, t_env *env)
{
	if (exec_builtin(cmm, &env) == 1)
		excute_interagration(//wrong struct t_parse *parse, t_env **env);
	
}

static	t_parse	*parse_shell(t_shell *head)
{
	t_shell *temp;
	t_parse *cmm;
	int	i;

	i = 0;
	cmm = parse_init();
	temp = head;
	while (temp)
	{
		if (!i)
		{
			parse_cmm(cmm, temp); //todo
			i = 1;
		}
		if (temp->type == PIPE)
			break ;
		else
			parse_other(temp, cmd);
		temp = temp->next;
	}
	return (cmm);
}

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

static void	parse_redir_out(t_parse *cmm, t_shell *temp)
{
	int	fd;

	if (temp->type == REDIRECT_OUT)
	{
		if (temp->next->input)
		{
			fd = open(temp->next->input, O_CREAT | O_RDWR, 0644);
			if (fd == -1)
				perror("File could not be created");
			close(fd);
			if (cmm->redirection_out == 0)
				cmm->outfilepath = ft_strcat(cmm->outfilepath, temp->next->input);
			else
			{
				free(cmm->outfilepath);
				cmm->outfilepath = ft_strdup(temp->next->input);
			}
		}
		cmm->redirection_out = 1;
	}
}

static void	parse_delim(t_parse *cmm, t_env *env)
{
	char *str;
	char *path;
	char	*whole_str;
	
	whole_str = strdup("");
	while (1)
	{
		str = readline("heredoc>");
		if (!strcmp(str, "EOF"))
			break;
		if (*str == '$')
		{
			path = ft_expand(str, env);
			whole_str = ft_strjoin(whole_str, path);
			free(path);
		}
		else
			whole_str = ft_strjoin(whole_str, str);
		whole_str = ft_strjoin(whole_str, "\n");
		free(str);
	}
	write(cmm->redirection_out, whole_str, ft_strlen(whole_str));
	free(whole_str);
}

void	parse_other(t_parse *cmm, t_shell *temp, t_env *env)
{
	int	fd;

	if (temp->type == REDIRECT_IN)
		parse_redir_in(cmm, temp);
	else if (temp->type == REDIRECT_OUT)
		parse_redir_out(cmm, temp);
	else if (temp->type == APP_M)
	{
		fd = open(temp->next->content, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			perror("File could not be created");
		close (fd);
	}
	else if (temp->type == HEREDOC)
		parse_delim(cmm, env);
}

static void	parse_redir_in(t_parse *cmm, t_shell *temp)
{
	if (temp->content)
	{
		if (cmm->redirection_in == 0)
		{
			check_infile(temp->next->input);
			cmm->infile = ft_strcat(cmm->infilepath, temp->next->input);
		}
		else
		{
			free(cmm->infilepath);
			cmm->infilepath = ft_strdup(temp->next->input);
		}
	}
	cmm->redirection_in = 1;
}

void	check_infile(char *infilepath)
{
	int	fd;

	fd = open(infilepath, O_RDONLY);
	if (fd == -1)
		return ;
	close(fd);
}
