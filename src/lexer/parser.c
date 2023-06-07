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
			cmm[i] = parse_shell(temp);//todo
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
		if (temp->type == 5)
			break ;
		else if (temp->type == 10)
			parse_delim(somethinghere); //todo
		else
			parse_other(temp, cmd); //todo
		temp = temp->next;
	}
	return (cmm);
}

static void	parse_delim(t_shell *temp, t_parse *cmm)
{
	something todo
}

void	parse_other(t_parse *cmm, t_shell *temp)
{
	int	fd;

	if (temp->type == 7)
		parse_redir_in(temp, cmm); //todo
	else if (temp->type == 8)
		parse_redir_out(temp, cmm);
	else if (temp->type == 11) //append
		todosomething
}

