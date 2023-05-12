#include "builtin.h"

static void	del_node(t_env **env,t_env *node)
{
	t_env	*temp;

	if (*env == node)
	{
		*env = node->next;
		free(node);
		return ;
	}
	temp = *env;
	while (temp->next && temp->next != node)
		temp = temp->next;
	if (temp->next == node)
	{
		temp->next = node->next;
		free(node);
	}
}

int ft_unset(t_builtin *node, t_env **env)
{
    t_env *temp;
    char *result;
    if (node->size == 1)
        return (ft_error("unset: not enough arguments"));
    temp = *env;
    while (temp)
    {
        if (!strncmp(temp->content, node->command[1], ft_strlen(node->command[1])))
        {
            del_node(env,temp);
            return (0);
        }
        temp = temp->next;
    }
    ft_env(env);
    return (0);
}