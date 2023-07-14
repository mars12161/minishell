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

int ft_character_after_dollar(char *str)
{
	int c;

	if (strlen(str) == 1)
		return (1);
	c = str[1];
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || (c >= 123 && c <= 133))
		return (1);
	return (0);
}

int main()
{
    char *str = "$";

    printf("%d\n", ft_character_after_dollar(str));
}