/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:21:54 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/07 12:47:49 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static void	new_node_type(t_shell *new_node)
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
		new_node->type = ESCAPE;
	else
		new_node->type = WORD;
}

static void new_node_state(t_shell *new_node)
{
	if (new_node->type == D_QUOTE)
		new_node->state = IN_DQUOTE;
	else if (new_node->type == S_QUOTE)
		new_node->state = IN_SQUOTE;
	else
		new_node->state = OTHER;
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
} // from libft.a

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

static t_shell *new_node(char *str)
{
	t_shell *new_node;

	new_node = NULL;
	new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
	new_node->input = ft_strdup((const char *)str);
	new_node->len = ft_strlen(str);
	new_node_type(new_node);
	new_node_state(new_node);
	new_node->next = 0;
	return (new_node);
}

static void	ft_lstadd_back_shell(t_shell **lst, t_shell *new)
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
}

t_shell *fill_shell(t_shell *shell)
{
	t_shell *temp;
	char *str;
	char	**result;
	char *input;
	int	i;

	i = 0;
	str = readline("minishell: ");
	result = ft_split(str);
	while (i < ft_spacetimes(str))
	{
		input = result[i];
		temp = new_node(input);
		if (!shell)
			shell = temp;
		else
				ft_lstadd_back_shell(&shell, temp);
		i++;
	};
	ft_free(result);
	return (shell);
}

/*
static void	ft_in_quote(t_shell **shell)
{
	t_shell *temp;
	int	flag;

	temp = *shell;
	flag = 0;
	while(temp)
	{
		if (temp->type == D_QUOTE)
		{
			(temp->next->state = IN_DQUOTE);
			flag = 1;
		}
	}
}
*/

void	print_shell(t_shell *s)
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
		printf("input: %s len: %i type: %i state: %i\n", temp->input, temp->len, temp->type, temp->state);
		temp = temp->next;
	}
	printf("=========\n\n");
}

int	main()
{
	t_shell *shell;

	shell = NULL;
	shell = fill_shell(shell);
	print_shell(shell);
}