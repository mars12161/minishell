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
#include "lexer.h"

static t_parse *parse_init(void)
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

static int	get_size_cmmarr(t_shell *head)
{
	t_shell *temp;
	int	size;

	size = 1;
	temp = head;
	while(temp)
	{
		if (temp->type == PIPE && temp->next)
			size++;
		temp = temp->next;
	}
	return (size);
}


static int	args_count(t_shell *head)
{
	int	i;

	i = 0;
	while(head && head->type != PIPE)
	{
		if (head->type == WORD)
			i++;
		head = head->next;
	}
	return (i);
}

char	**ft_shell_whole_line(t_shell *head)
{
	int	i;
	int	n;
	char	**wline;

	if (head == NULL)
		return (NULL);
	i = args_count(head);
	n = 0;
	wline = malloc(sizeof(*wline) * (i + 1));
	if (!wline)
		return (NULL);
	wline[i] = NULL;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
		{
			wline[n] = ft_strdup(head->input);
			n++;
		}
		head = head->next;
	}
	if (head && head->type == PIPE)
		head = head->next;
	return (wline);
}


static void	parse_cmm(t_parse *cmm, t_shell *head)
{
	char **wline;

	wline = ft_shell_whole_line(head);
	cmm->whole_line = wline;
	cmm->command = wline[0];
	cmm->wline = 1;
}



static	t_parse **create_cmm(t_shell *head, int *size, t_env *env)
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
			cmm[i] = parse_shell(temp, env);
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

t_parse_arr *parse_array_create(t_shell *head,t_env *env)
{
	t_parse **cmm;
	t_parse_arr *cmm_arr;

	if (!head)
		return (NULL);
	cmm_arr = malloc(sizeof(t_parse_arr));
	if (!cmm_arr)
		return (NULL);
	cmm_arr->size = get_size_cmmarr(head);
	//printf("cmm_arr->size: %d\n", cmm_arr->size);
	cmm = create_cmm(head, &cmm_arr->size, env);
	if (!cmm)
		return (NULL);
	else
		cmm_arr->cmm = cmm;
	return (cmm_arr);
}


// void	parse_cmm(t_parse *cmm, t_shell *temp, t_env *env)
// {
// 	if (exec_builtin(cmm, &env) == 1)
// 		excute_interagration(//wrong struct t_parse *parse, t_env **env);
	
// }

static void    ft_free_str(char **str)
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
		if (temp->input)
		{
			printf("out: %s\n", temp->next->next->input);
			fd = open(temp->next->input, O_CREAT | O_RDWR, 0644);
			if (fd == -1)
				perror("File could not be created");
			close(fd);
			if (cmm->redirection_out == 0)
				cmm->outfilepath = ft_strdup(temp->next->next->input); //no ft_strcat
			else
			{
				free(cmm->outfilepath);
				cmm->outfilepath = ft_strdup(temp->next->next->input);
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
			path = ft_expand(str, &env);
			whole_str = ft_strjoin(whole_str, path);
			free(path);
		}
		else
			whole_str = ft_strjoin(whole_str, str);
		whole_str = ft_strjoin(whole_str, "\n");
		free(str);
	}
	write(cmm->redirection_out, whole_str, ft_strlen(whole_str)); //or do it in the execute
	free(whole_str);
}

static void	check_infile(char *infilepath)
{
	int	fd;

	fd = open(infilepath, O_RDONLY);
	if (fd == -1)
		return ;
	close(fd);
}

static void	parse_redir_in(t_parse *cmm, t_shell *temp)
{
	if (temp->input)
	{
		printf("in: %s\n", temp->next->next->input);
		if (cmm->redirection_in == 0)
		{
			check_infile(temp->next->input);
			cmm->infilepath = strcat(cmm->infilepath, temp->next->next->input); //do not have ft_strcat
		}
		else
		{
			free(cmm->infilepath);
			cmm->infilepath = ft_strdup(temp->next->next->input);
		}
	}
	cmm->redirection_in = 1;
}

static void	parse_other(t_shell *temp, t_parse *cmm, t_env *env)
{
	int	fd;

	if (temp->type == REDIRECT_IN)
		parse_redir_in(cmm, temp);
	else if (temp->type == REDIRECT_OUT)
		parse_redir_out(cmm, temp);
	else if (temp->type == APP_M)
	{
		fd = open(temp->next->input, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			perror("File could not be created");
		close (fd);
	}
	else if (temp->type == HEREDOC)
		parse_delim(cmm, env);
}


t_parse	*parse_shell(t_shell *head, t_env *env)
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
			parse_cmm(cmm, temp);
			i = 1;
		}
		if (temp->type == PIPE)
			break ;
		else
			parse_other(temp, cmm, env);
		temp = temp->next;
	}
	return (cmm);
}