void new_node_SPACE(char *str, t_shell *shell)
{
    t_shell *new_node;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    while (*str == ' ')
    {
        new_node->input = *str;
        str++;
    }
    new_node->len = ft_strlen(str);
    new_node_type(new_node);
	new_node_state(new_node);
    ft_add_tail(&shell, new_node);
}

void    new_node(char *str, t_shell *shell) // for $ and WORD
{
    t_shell *new_node;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    while(*str >= 33 && *str <= 126)
    {
        new_node->input = *str;
        str++;
    }
    new_node->len = ft_strlen(str);
    new_node_type(new_node);
	new_node_state(new_node);
    ft_add_tail(&shell, new_node);
}