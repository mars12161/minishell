#include "lexer.h"
/*
int		count_pipes(t_shell *list)
{
	t_shell	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_shell	*get_next_pipe(t_shell *list)
{
	t_shell	*tmp;

	tmp = list;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	return (tmp);
}
*/
static t_parse *get_parse_bottom(t_parse *node)
{
    while(node && node->next != NULL)
        node = node->next;
    return (node);
}
/*
static int		count_word1(t_shell *list)
{
	t_shell	*tmp;
	int 	i;

	i = 0;
	tmp = list;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static t_shell		*count_args1(t_shell *list)
{
	t_shell	*tmp;

	tmp = list;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	return (tmp);
}
*/

static int		count_word2(t_shell **list)
{
	t_shell	*tmp;
	int 	i;

	i = 0;
	tmp = *list;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static t_shell		*count_args2(t_shell *shell)
{
	while (shell && shell->type != PIPE)
		shell = shell->next;
	return (shell);
}

static t_parse *init_parse_node(t_shell *shell, int i)
{
	parse_node->command = (char **)malloc(sizeof(char *) * (i + 1));
	parse_node->command[i] = 0;
	if (!parse_node->command)
		return (NULL);
	node->redirection_in = 0;
	node->redirection_out = 0;
	node->infilepath = NULL;
	node->outfilepath = NULL;
	node->pipe = 0;
	node->fd[2] = NULL;
	node->previous = 0;
	node->next = 0;
	return (node);
}

static parse_new_node_redirection(t_parse *parse_node, t_shell **shell)
{
		if (*shell->type == REDIRECT_IN)
		{
			parse_node->redirection_in = 1;
			parse_node->infilepath = *shell->next->input;
		}
		else if (*shell->type == HEREDOC)
		{
			parse_node->redirection_in = 2;
			parse_node->infilepath = *shell->next->input;
		}
		else if (*shell->type == redirection_out)
		{
			parse_node->redirection_out = 1;
			parse_node->outfilepath = *shell->next->input;
		else if (*shell->type == APP_M)
		{
			parse_node->redirection_out = 2;
			parse_node->outfilepath = *shell->next->input;
		}
}

t_parse *parse_new_node(t_shell *shell)
{
	int	i;
	int	wc;
	t_shell *temp;

	i = 0;
	parse_node = (t_parse *)malloc(sizeof(t_parse));
	if (!parse_node)
		return (0);
	wc = count_word2(&shell);
	parse_node = init_parse_node(shell, wc);
	temp = shell;
	while (temp)
	{
		if (temp->type == WORD)
			parse_node->command[i++] = shell->input;
		parse->size = i;
		parse_new_node_redirection(parse_node, &temp);
		else if (temp->type == PIPE)
		{
			parse_node->pipe = 1;
			break ;
		}
		temp = temp->next;
	}
	return (parse_node);
}


static void ft_add_tail_parse(t_parse **parse, t_parse *parse_node)
{
    t_parse *bottom;

    if (!parse_node)
        return ;
    parse_node->next = 0;
    if (!*parse)
    {
		*parse = parse_node;
        return ;
    }
	bottom = get_parse_bottom(*shell);
    bottom->next = parse_node;
    parse_node->previous = bottom;
}

void	print_parse(t_parse *s)
{
	t_parse	*temp;

	temp = s;
	printf("\n==PARSE==\n");
	if (s == NULL)
	{
		printf("PARSE empty!\n");
		return ;
	}
	while (temp)
	{
		printf("command[0]: %s size: %i redirection_in: %i redirection_out: %i\n", temp->command[0], temp->size, temp->redirection_in, temp->redirection_out);
		temp = temp->next;
	}
	printf("=========\n\n");
}
