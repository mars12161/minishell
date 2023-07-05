/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:33:26 by yli               #+#    #+#             */
/*   Updated: 2023/07/05 21:59:47 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		printf("input: %s len: %i type: %i\n", temp->input, temp->len, temp->type);
		temp = temp->next;
	}
	printf("=========\n\n");
}

void	print_parse(t_parse	*head)
{
	printf("\n==PARSE==\n");
	if (head == NULL)
	{
		printf("PARSE empty!\n");
		return ;
	}
	else
	{
		printf("command: %s\n", head->command);
		printf("whole_line[0]: %s\n", head->whole_line[0]);
		printf("whole_line[1]: %s\n", head->whole_line[1]);
		printf("whole_line[2]: %s\n", head->whole_line[2]);
		// printf("whole_line[3]: %s\n", head->whole_line[3]);
		printf("wline: %d\n", head->wline_count);
		printf("redirection_in: %d\n", head->redirection_in);
		printf("redirection_out: %d\n", head->redirection_out);
		printf("infilepath: %s\n", head->infilepath);
		printf("outfilepath: %s\n", head->outfilepath);
		printf("pipe: %d\n", head->pipe);
	}
	printf("=========\n\n");
}

void	print_parse_arr(t_parse_arr	*head)
{
	printf("\n==PARSE_ARR==\n");
	if (head == NULL)
	{
		printf("PARSE_ARR empty!\n");
		return ;
	}
	else
	{
		//printf("command: %s\n", head->command[0]);
		//printf("check: %d\n", head->check);
		printf("size: %d\n", head->size);
	}
	printf("=========\n\n");
}



