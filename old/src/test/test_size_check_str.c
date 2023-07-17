# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>


int	check_path_char(int c)
{
	if (c >= 65 && c <= 90)
		return (0);
	return (1);
}

int	check_path_str(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (check_path_char(str[i]) == 1)
			break ;
		i++;
	}
	return (i);
}

int main()
{
    char *str= "USER!ff";
    int i = check_path_str(str);

    printf("%d\n", i);
}