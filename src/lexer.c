#include "../includes/minishell.h"

static t_lexer *new_node(char *str)
{
	t_lexer *new_node;

	new_node = NULL;
	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->cmd = str;
	new_node->next = 0;
	return (new_node);
}

static t_lexer *new_node_integration(t_lexer *new_node)
{
	if (new_node->str[0] == 34)
		new_node->token = D_QUOTE;
	else if (new_node->str[0] == 36)
		new_node->token = NOMAL_VAR;
	else if (new_node->str[0] == 39)
		new_node->token = S_QUOTE;
	else if (new_node->str[0] == 60)
		new_node->token = REDIRECT_IN;
	else if (new_node->str[0] == 62)
		new_node->token = REDIRECT_OUT;
	else if (new_node->str[0] == 62)
		new_node->token = REDIRECT_OUT;
	else if (new_node->str[0] == 124)
		new_node->token = PIPE;
	else
		new_node->token = CMD;
	return (new_node);
}


static t_lexer	*get_lexer_bottom(t_lexer *lexer)
{
	while(lexer && lexer->next != NULL)
		lexer = lexer->next;
	return (lexer);
}

static void	lexer_add_bottom(t_lexer **lexer, t_lexer *new_node)
{
	t_lexer *bottom;

	if (!new_node)
		return ;
	if (!lexer)
	{
		*lexer = new_node;
		return ;
	}
	bottom = get_lexer_bottom(*lexer);
	bottom->next = new_node;
}

static t_lexer *fill_lexer(int argc, char **argv)
{
	t_lexer *lexer;
	t_lexer *temp;
	int	i;
	char	*str;
	

	lexer = NULL;
	if (argc == 1)
		error_free_exit(lexer);
	i = 1;
	while(i < argc)
	{
		str = argv[i];
		temp = new_node_integration(str);
		if (i == 1)
			lexer = temp;
		else
			lexer_add_bottom(&lexer, temp);
		i++;
	}
	return (lexer);
}
