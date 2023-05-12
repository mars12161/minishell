

void	free_stack(t_stack **stack)
{
	t_stack	*temp;

	if (!*stack || !stack)
		return ;
	while (*stack)
	{
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
	}
	*stack = NULL;
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (*str != NULL)
		{
			free(str[i]);
			i++;
		}
		*str = NULL;
	}
	free (str);
}