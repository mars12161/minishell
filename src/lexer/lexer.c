#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
int	main()
{
	char *str = readline("minishell: ");
	int	i = 0;
	char *out = split_line(str);
	//printf("from readline: %s\n", str);
	//printf("%s\n", out);
	while(out)
	{
		out = split_line(str);
		printf("%s",out);
		str = ft_strcpy(str, ft_strlen(out) + 1, 1);
	}
	//printf("%s",split_line(str));
	//printf("%s",split_line(str));
}
*/

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

void	lunch_lexer()
{
	
}

static void new_node_type(t_shell *new_node)
{
	if (new_node->input == '$')
		new_node->type = ENV;
	else if (new_node->input == '|')
		new_node->type = PIPE;
	else if (new_node->input == '\"')
		new_node->type = D_QUOTE;
	else if (new_node->input == '\'')
		new_node->type = S_QUOTE;
	else if (new_node->input == '\n')
		new_node->type = NEW_LINE; //not sure
	else if (new_node->input == '<')
		new_node->type = REDIRECT_IN;
	else if (new_node->input == '>')
		new_node->type = REDIRECT_OUT;
	else if (new_node->input == '\\')
		new_node->type = ESC;
	else new_node->type = WORD;		
}

static void new_node_state(t_shell *new_node)
{
	if (new_node->type == D_QUOTE)
		new_node->state = D_QUOTE;
	else if (new_node->type == S_QUOTE)
		new_node->state = S_QUOTE;
	else new_node->state = OTHER;
}

static t_shell *new_node(char *str, enum e_token)
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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

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

static t_shell *fill_shell(char *str)
{
	t_shell *shell;
	t_shell *temp;
	int	i;
	char	*str;

	shell = NULL;
	if (!str)
		error_free_exit(shell);
	i = 1;
	while(i < argc)
	{
		str = argv[i];
		temp = new_node(str);
		if (i == 1)
			shell = temp;
		else
			ft_lstadd_back(&shell, temp);
		i++;
	}
	return (shell);
}

