#include "../../cub3D.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p != '\0')
	{
		if (*p == (char )c)
			return (p);
		p++;
	}
	if ((char )c == '\0')
		return (p);
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		i;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_substr(char *s, unsigned int index, size_t bytes)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (index > ft_strlen(s))
		return (ft_strdup(""));
	if (bytes > ft_strlen(s) - index)
		bytes = ft_strlen(s) - index;
	str = malloc(bytes + 1);
	if (!str)
		return (NULL);
	while (bytes--)
	{
		str[i++] = s[index++];
	}
	str[i] = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
