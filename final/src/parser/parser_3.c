/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:54:09 by yli               #+#    #+#             */
/*   Updated: 2023/06/30 08:41:32 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	check_infile(char *infilepath);
int	args_count(t_shell *head);
void    ft_free_str(char **str);
int	get_size_cmmarr(t_shell *head);

void	check_infile(char *infilepath)
{
	int	fd;

	fd = open(infilepath, O_RDONLY);
	if (fd == -1)
		return ;
	close(fd);
}

int	args_count(t_shell *head)
{
	int	i;

	i = 0;
	while(head && head->type != PIPE)
	{
		if (head->type == WORD)
			i++;
		head = head->next;
	}
	return (i);
}

int	get_size_cmmarr(t_shell *head)
{
	t_shell *temp;
	int	size;

	size = 1;
	temp = head;
	while(temp)
	{
		if (temp->type == PIPE && temp->next)
			size++;
		temp = temp->next;
	}
	return (size);
}
