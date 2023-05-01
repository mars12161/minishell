#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;

	//(void)argc;
	//(void)argv;
	shell.in = dup(STDIN);
	shell.out = dup(STDOUT);
	shell.exit = 0;
	shell.result = 0; //
	shell.no_exec = 0;
	init_fds(&shell);
	//something for envp
	//
	//maybe have a if check hier
	while(!shell.exit)
	{
		execute(//);	
	}
	free_env(mini.envp);
	free_env(//);
	return (mini.result);
}

