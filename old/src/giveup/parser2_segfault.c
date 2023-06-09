#include "lexer.h"

static t_parse *get_parse_bottom(t_parse *node)
{
    while(node && node->next != NULL)
        node = node->next;
    return (node);
}

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
} // before pipe how many words **shell

static t_shell	*count_word_node(t_shell **list)
{
	t_shell	*temp;
	int 	i;

	i = 0;
	temp = *list;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == WORD)
			i++;
		temp = temp->next;
	}
	return (temp);
} // before pipe how many words return *shell

static t_shell		*count_args2(t_shell *shell)
{
	while (shell && shell->type != PIPE)
		shell = shell->next;
	return (shell);
} // better than count_args1

static t_parse *init_parse_node(int i)
{
	t_parse *parse_node;

	parse_node = (t_parse *)malloc(sizeof(t_parse));
	if (!parse_node)
		return (NULL);
	parse_node->command = (char **)malloc(sizeof(char *) * (i + 1));
	parse_node->command[i] = 0;
	if (!parse_node->command)
		return (NULL);
	parse_node->redirection_in = 0;
	parse_node->redirection_out = 0;
	parse_node->infilepath = NULL;
	parse_node->outfilepath = NULL;
	parse_node->pipe = 0;
	//parse_node->fd[] = NULL;
	parse_node->previous = 0;
	parse_node->next = 0;
	return (parse_node);
}

static t_shell *find_next_word(t_shell *shell)
{
	while(shell)
	{
		if (shell->type == WORD)
			break ;
		shell = shell->next;
	}
	return (shell);
}

static t_shell *parse_new_node_redirection(t_parse *parse_node, t_shell **shell)
{
	t_shell *temp;

	temp = *shell;
		if (temp->type == REDIRECT_IN)
		{
			parse_node->redirection_in = 1;
			parse_node->infilepath = find_next_word(temp)->input;
		}
		else if (temp->type == HEREDOC)
		{
			parse_node->redirection_in = 2;
			parse_node->infilepath = find_next_word(temp)->input;
		}
		else if (temp->type == REDIRECT_OUT)
		{
			parse_node->redirection_out = 1;
			parse_node->outfilepath = find_next_word(temp)->input;
		}
		else if (temp->type == APP_M)
		{
			parse_node->redirection_out = 2;
			parse_node->outfilepath = find_next_word(temp)->input;
		}
	//temp = temp->next;
	//printf("in parse_new_node_redirection\n");
	return (temp);
}
/*
t_parse *parse_new_node(t_shell *shell)
{
	int	i;
	int	wc;
	t_shell *temp;
	t_parse *parse_node;

	i = 0;
	parse_node = (t_parse *)malloc(sizeof(t_parse));
	if (!parse_node)
		return (0);
	wc = count_word2(&shell);
	parse_node = init_parse_node(parse_node, wc);
	temp = shell;
	while (temp)
	{
		if (temp->type == WORD)
			parse_node->command[i++] = shell->input;
		parse_node->size = i;
		if (temp->type == 7 || temp->type == 8 || temp->type == 10 || temp->type == 11)
			parse_new_node_redirection(parse_node, &temp);
		if (temp->type == PIPE)
		{
			parse_node->pipe = 1;
			break ;
		}
		temp = temp->next;
	}
	return (parse_node);
}
*/
static t_shell	*parse_new_node_word(t_shell *shell, t_parse *parse_node, int i)
{
	parse_node->command[i] = shell->input;
	shell = shell->next;
	return (shell);
}

static t_shell *parse_new_node(t_shell **shell, t_parse *parse_node)
{
	int	i;
	//int	wc;
	t_shell *temp;

	i = 0;
	//wc = count_word2(&shell);
	temp = *shell;
	while (temp)
	{
		if (temp->type == WORD)
		{
			temp = parse_new_node_word(temp, parse_node, i);
			i++;
		}
		if (temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT || temp->type == HEREDOC || temp->type == APP_M)
			temp = parse_new_node_redirection(parse_node, &temp);
		if (temp->type == PIPE)
		{
			parse_node->pipe = 1;
			temp = temp->next;
			break ;
		}
		temp = temp->next;
	}
	return (temp);
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
	bottom = get_parse_bottom(*parse);
    bottom->next = parse_node;
    parse_node->previous = bottom;
}

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
} // before pipe how many words *shell

void parse_integration(t_shell **shell, t_parse **parse)
{
	t_shell *temp;
	t_parse *parse_node;
	int i;

	temp = *shell;
	printf("first in parse_integration\n");
	while(temp)
	{
		i = count_word1(temp);
		printf("1 i: %d\n", i);
		parse_node = init_parse_node(i);
		temp = parse_new_node(&temp, parse_node);
		parse_node->size = i;
		printf("2\n");
		ft_add_tail_parse(parse, parse_node);
		temp = temp->next;
		printf("3\n");
	}
}

void	print_parse(t_parse *s)
{
	t_parse	*temp;

	temp = s;
	printf("in print_parse\n");
	printf("\n==PARSE==\n");
	if (s == NULL)
	{
		printf("PARSE empty!\n");
		return ;
	}
	while (temp)
	{
		printf("c[0]: %s ", temp->command[0]);
		printf("c[1]: %s size: %i ", temp->command[1], temp->size);
		//printf("command[2]: %s size: %i", temp->command[2], temp->size);
		printf("re_in: %i re_out: %i", temp->redirection_in, temp->redirection_out);
		printf("inpath: %s outpath: %s pipe : %d\n", temp->infilepath, temp->outfilepath, temp->pipe);
		temp = temp->next;
	}
	printf("=========\n\n");
}
