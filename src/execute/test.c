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
# include <readline/readline.h>

static	size_t	count_str(char const *s, char const c)
{
	size_t	i;
	size_t	strcount;

	i = 0;
	strcount = 0;
	if (s[0] != '\0' && s[0] != c)
		strcount++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
			strcount++;
		i++;
	}
	return (strcount);
}

static	size_t	count_char(char const *s, char const c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static	char	*newstr(char const *s, char c)
{
	size_t	i;
	size_t	charcount;
	char	*str;

	i = 0;
	charcount = count_char(s, c);
	str = (char *)malloc(sizeof(char) * (charcount +1));
	if (str == NULL)
		return (NULL);
	while (i < charcount)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	p;
	size_t	strcount;
	char	**ch;

	i = 0;
	p = 0;
	if (s == NULL)
		return (NULL);
	strcount = count_str(s, c);
	ch = (char **)malloc(sizeof(char *) * (strcount + 1));
	if (ch == NULL)
		return (NULL);
	while (i < strcount)
	{
		while (s[p] != '\0' && s[p] == c)
			p++;
		ch[i] = newstr(s + p, c);
		while (s[p] != '\0' && s[p] != c)
			p++;
		i++;
	}
	ch[i] = NULL;
	return (ch);
}

int	ft_error(char *str)
{
	int	i;

	i = 0;
    while (str[i])
		i++;
	write(2, str, i);
	write(2, "\n", 1);
    return (-1);
}

char	**ft_check_cmd(char *cmd)
{
	char	**command;

	if (cmd == 0)
		ft_error("empty command");
	else if (cmd[0] == '\0')
		ft_error("empty command");
	command = ft_split(cmd, ' ');
	if (command == 0)
		ft_error("empty command");
	return (command);
}

int main()
{
    char *cmd = "";
    char **command = ft_check_cmd(cmd);

    printf("%s\n", command[0]);
    printf("%s\n", command[1]);
    printf("%d\n", ft_check_cmd(char *cmd));
}