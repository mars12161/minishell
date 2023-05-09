#include "lexer.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
} // from libft.a

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < (size -1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
char	*ft_strdup(const char *s)
{
	int		len;
	char	*ret;

	len = ft_strlen((char *)s);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, len + 1);
	return (ret);
} //from libft.a

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (NULL);
	//if (start >= (unsigned int)ft_strlen(s))
	//	len = 0;
	//if (ft_strlen(s + start) < len)
	//	len = ft_strlen(s + start);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
} //from libft.a