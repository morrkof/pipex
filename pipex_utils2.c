#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_words(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		if (s[j] != c && (s[j + 1] == c || s[j + 1] == '\0'))
			i++;
		j++;
	}
	return (i);
}

void	ft_free(char **dst)
{
	int	i;

	i = 0;
	while (dst[i] != NULL)
		free(dst[i++]);
	free(dst);
}

static char	*ft_subp(char const *s, size_t *beg, size_t len, char **dst)
{
	char	*s1;
	size_t	i;

	s1 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s1)
	{
		ft_free(dst);
		return (NULL);
	}
	i = 0;
	while (i < len && s[i + *beg] != '\0')
	{
		s1[i] = s[i + *beg];
		i++;
	}
	s1[i] = '\0';
	*beg = *beg + i;
	return (s1);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	beg;
	size_t	end;
	size_t	ptr;

	beg = 0;
	end = 0;
	ptr = 0;
	dst = (char **)malloc((ft_words(s, c) + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	while (s[end] != '\0')
	{
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == '\0'))
		{
			while (s[beg] == c && s[beg] != '\0')
				beg++;
			dst[ptr++] = ft_subp(s, &beg, (end - beg + 1), dst);
		}
		end++;
	}
	dst[ptr] = NULL;
	return (dst);
}
