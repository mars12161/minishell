#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main()
{
	int	i;
	char *str = readline("minishell: ");

	i = 0;
	printf("from readline: %s\n", str);
	while(str[i])
	{
		printf("%c",str[i]);
		printf("signal: %d\n", in_charset(str[i]));
		i++;
	}
}
