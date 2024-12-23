#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	ft_split_count(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static void	ft_set(char const *s, char **dest, char c, int count)
{
	int		i;
	int		j;

	i = 0;
	while (*s != '\0' && i != count)
	{
		j = 0;
		while (*s == c)
			s++;
		while ((*s != '\0') && (*s != c))
		{
			dest[i][j] = *s;
			s++;
			j++;
		}
		dest[i][j] = '\0';
		i++;
	}
	dest[i] = NULL;
}

void	ft_split_free(char **dest)
{
    if (dest == NULL)
      return;
    int i = 0;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**dest;

	if (s == NULL)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_split_count(s, c) + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < (ft_split_count(s, c)))
	{
		dest[i] = (char *)malloc(strlen(s) + 1);
		if (dest[i] == NULL)
		{
			ft_split_free(dest);
			return (NULL);
		}
		i++;
	}
	ft_set(s, dest, c, ft_split_count(s, c));
	return (dest);
}