#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"

/*
int	ft_readline(char **line)
{
	*line = readline("[minishell:]");
	if (!*line)
	{
		printf("exit\n");
		exit(1); //add something later, maybe free
	}
	if (ft_isspace(*line))
		return (1);
	if (strlen(*line) > 0)
		add_history(*line);
	return (0);
}
*/
static void new_node_type(t_shell *new_node)
{
	if (new_node->input[0] == '$')
		new_node->type = ENV;
	else if (new_node->input[0] == '|')
		new_node->type = PIPE;
	else if (new_node->input[0] == '\"')
		new_node->type = D_QUOTE;
	else if (new_node->input[0] == '\'')
		new_node->type = S_QUOTE;
	else if (new_node->input[0] == '\n')
		new_node->type = NEW_LINE; //not sure
	else if (new_node->input[0] == '<')
		new_node->type = REDIRECT_IN;
	else if (new_node->input[0] == '>')
		new_node->type = REDIRECT_OUT;
	else if (new_node->input[0] == '\\')
		new_node->type = ESC;
	else new_node->type = WORD;		
}

static void new_node_state(t_shell *new_node)
{
	if (new_node->type == D_QUOTE)
		new_node->state = IN_DQUOTE;
	else if (new_node->type == S_QUOTE)
		new_node->state = IN_SQUOTE;
	else new_node->state = OTHER;
}

static t_shell *new_node(char *str)
{
	t_shell *new_node;

	new_node = NULL;
	new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
	new_node->input = str;
    	new_node->len = ft_strlen(str);
    new_node_type(new_node);
    new_node_state(new_node);
	new_node->next = 0;
	return (new_node);
}

void	ft_lstadd_back(t_shell **lst, t_shell *new)
{
	t_shell	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
} //can delete later

t_shell *fill_shell(t_shell *shell)
{
	
	t_shell *temp;
	int	i;
	static char *str;
	char *out;
	static int	flag;

	//shell = NULL;
	if (flag == 0)
	{
		str = readline("minishell: ");
		flag = 1;
	}
	out = split_line(str);
	str = str + ft_strlen(out) + 1;
	//if (!str)
	//	error_free_exit(shell);
	temp = new_node(out); //or add here token/state
	free(out);
	if (!shell)
		shell = temp;
	else
			ft_lstadd_back(&shell, temp);
	return (shell);
}

/*
t_shell *lunch_lexer()
{
	static char *str;
	char *out;
	static int	flag;

	if (flag == 0)
	{
		str = readline("minishell: ");
		flag = 1;
	}
	out = split_line(str);
	fill_shell(out);
	str = str + ft_strlen(out) + 1;
	free(out);
	out = split_line(str);
	fill_shell(out);
	str = str + ft_strlen(out) + 1;
	free(out);
	return 
}
*/
void	print_stack(t_shell *s)
{
	t_shell	*temp;

	temp = s;
	printf("\n==SHELL==\n");
	if (s == NULL)
	{
		printf("SHELL empty!\n");
		return ;
	}
	while (temp)
	{
		printf("input: %s ", temp->input);
		printf("len: %i\n", temp->len);
		printf("type: %i\n", temp->type);
		printf("state: %i\n", temp->state);
		temp = temp->next;
	}
	printf("=========\n\n");
}
int	main()
{
	t_shell *shell;

	shell = NULL;
	shell = fill_shell(shell);
	shell = fill_shell(shell);
	print_stack(shell);
}
