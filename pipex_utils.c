#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	s3 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s3)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned const char	*d1;
	unsigned const char	*d2;

	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	while (n != 0)
	{
		if (*d1 != *d2 || *d1 == '\0' || *d2 == '\0')
			return (*d1 - *d2);
		d1++;
		d2++;
		n--;
	}
	return (0);
}

char	*find_line(char **env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	**path_splitization(char **env)
{
	char	*line;

	line = find_line(env);
	line = line + 5;
	return (ft_split(line, ':'));
}

void	ft_error(int error)
{
	static char	*message[4] = {"     :wrong arguments (0)",
	"     :can't open the file (1)", "     :fail allocating memory (2)",
	"     :can't create new process (3)"};

	write(2, "Error\n", 6);
	write(2, message[error], ft_strlen(message[error]));
	write(2, "\n", 1);
	exit(0);
}
