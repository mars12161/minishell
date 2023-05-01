#include "../includes/minishell.h"

char	*ft_strchr(const char*str, int c) //from libft, delete later
{
	while (*str != (char)c && *str)
		str++;
	if ((char)c !='\0' && *str == '\0')
		return (NULL);
	return ((char *)str);
}

void	free_exit_lexer(t_lexer **lexer)
{
	t_lexer	temp;

	if (!lexer || !*lexer)
		return ;
	while(*lexer)
	{
		temp = (*lexer)->next;
		free(*lexer);
		*lexer = temp;
	}
	*lexer = NULL;
}

void	error_free_exit(t_lexer *lexer)
{
	free_exit_lexer(&lexer);
	write(2, "Error\n", 6);
	exit(1);
}
