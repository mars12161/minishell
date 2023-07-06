
#include "../../inc/minishell.h"

int	ft_pwd(t_parse *node);

int	ft_pwd(t_parse *node)
{
	static char	pwd[PATH_SIZE];
	int			fd;

	fd = ft_redirection_out(node);
	if (node->wline_count > 1)
	{
		ft_error_optimal("pwd: too many args", 1);
		return (1);
	}
	else if (getcwd(pwd, PATH_SIZE))
	{
		ft_putstr_fd(pwd, fd);
		write(fd, "\n", 1);
		if (fd != 1)
			close (fd);
		return (0);
	}
	else
	{
		if (fd != 1)
			close (fd);
		globe.g_exit = 0;
		return (-1);
	}

}
