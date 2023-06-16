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

t_shell *fill_shell(t_shell *shell)
{
	char *str;
	int	i = 0;

	str = readline("[minishell:]");
	//printf("in fill_shell0: %s\n", str);
	while (*str == ' ')
		str++;
	//printf("in fill_shell1: %s\n", str);
	while (*str)
	{
		//printf("in loop: i: %d\n", i);
		//printf("*str: %c\n", *str);
		if (*str == ' ')
		{
			str = new_node_SPACE(str, &shell, 32);
			printf("SPACE\n");
		}
		else if (*str == '$')
		{
			str = new_node_DW(str, &shell, 36);
			printf("DOLLAR\n");
		}
		else if (*str == '|')
		{
			str = new_node_PIPE(str, &shell, 124);
			printf("PIPE\n");
		}
		else if (*str == '\"')
		{
			printf("DQ\n");
			str = new_node_DSQ(str, &shell, 34);
		}
		else if (*str == '\'')
		{
			printf("SQ\n");
			str = new_node_DSQ(str, &shell, 39);
		}
		else if (*str == '\n')
		{
			printf("NL\n");
			str = new_node_NL_ESC(str, &shell, 10);
		}
		else if (*str == '<')
		{
			printf("REDI OR HEREDOC\n");
			str = new_node_RED(str, &shell, 60);
		}
		else if (*str == '>')
		{
			printf("REDO OR APP_M\n");
			str = new_node_RED(str, &shell, 62);
		}
		else if (*str == '\\')
		{
			printf("ESC\n");
			str = new_node_NL_ESC(str, &shell, 92);
		}
		else
		{
			printf("WORD\n");
			str = new_node_DW(str, &shell, 500);
		}
		//printf("helloend\n");
	}
	//ft_free(result);
	return (shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell *shell;
	t_parse *parse;
	t_env	*env;
	t_parse_arr *cmmarr;

	(void)argc;
	(void)argv;
	shell = NULL;
	parse = NULL;
	env = NULL;
    env = init_env(envp, env);
	shell = fill_shell(shell);
	print_shell(shell);
	parse = parse_shell(shell, env);

	cmmarr = parse_array_create(shell, env);
	//printf("main0\n");
	print_parse(parse);
	print_parse_arr(cmmarr);
}