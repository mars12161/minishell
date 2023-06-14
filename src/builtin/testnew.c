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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i++];
	}
	i = 0;
	free((void *)s1);
	while (s2[i])
	{
		str[j++] = s2[i++];
	}
	str[j] = 0;
	return (str);
}
int	main(void) {
	char *str;
	char	*whole_str;
	int i = 3;
	whole_str = strdup("");
	
	while (1)
	{
		str = readline("heredoc>");
		if (!strcmp(str, "EOF"))
			break;
		whole_str = ft_strjoin(whole_str, str);
		whole_str = ft_strjoin(whole_str, "\n");
		free(str);
	}
	printf("%s", whole_str); //todo
	free(whole_str);
}
