#include "minishell.h"

void	reset_std(t_shell *shell)
{
	dup2(shell->in, STDIN);
	dup2(shell->out, STDOUT);
}

void	ft_close(int fd)
{
	if (fd > 0)
		close (fd);
}

void	close_fds(t_stell *shell)
{
	ft_close(shell->fdin);
	ft_close(shell->fdout);
	ft_close(shell->pipein);
	ft_close(shell->pipeout);
}

void	init_fds(t_shell *shell)
{
	shell->fdin = 0;
	shell->fdout = 0;
	shell->pipein = 0;
	shell->pipeout = 0;
	shell->pid = 0;
}
