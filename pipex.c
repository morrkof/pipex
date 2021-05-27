#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

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
	if (!(s3 = (char *)malloc(sizeof(char) * (len + 1))))
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

static char	*ft_strjoin2(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!(result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	free(s1);
	s1 = NULL;
	return (result);
}

int			get_next_line(int fd, char **line)
{
	char	*buf;
	int		result;

	result = 1;
	if (!line)
		return (-1);
	if ((buf = malloc(2)) == NULL)
		return (-1);
	if ((*line = malloc(1)) == NULL)
		return (-1);
	**line = '\0';
	*buf = '\0';
	while (*buf != '\n' && result)
	{
		result = read(fd, buf, 1);
		buf[1] = '\0';
		if (*buf != '\n' && result)
			*line = ft_strjoin2(*line, buf);
	}
	free(buf);
	return (result);
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

static void		ft_free(char **dst)
{
	int i;

	i = 0;
	while (dst[i] != NULL)
		free(dst[i++]);
	free(dst);
}

static char		*ft_subp(char const *s, size_t *beg, size_t len, char **dst)
{
	char	*s1;
	size_t	i;

	if (!(s1 = (char *)malloc(sizeof(char) * (len + 1))))
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

char			**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	beg;
	size_t	end;
	size_t	ptr;

	beg = 0;
	end = 0;
	ptr = 0;
	if (s == NULL)
		return (NULL);
	if (!(dst = (char **)malloc((ft_words(s, c) + 1) * sizeof(char*))))
		return (NULL);
	while (s[end] != '\0')
	{
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == '\0'))
		{
			while (s[beg] == c && s[beg] != '\0')
				beg++;
			if (!(dst[ptr++] = ft_subp(s, &beg, (end - beg + 1), dst)))
				return (NULL);
		}
		end++;
	}
	dst[ptr] = NULL;
	return (dst);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned const char *d1;
	unsigned const char *d2;

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

char *find_path(char **env)
{
	int i = 0;
	while (env != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return env[i];
		i++;
	}
	return NULL;
}

void	ft_error(int error)
{
	static	char *message[8] = {"     :wrong arguments (0)",
	"     :can't open the file (1)", "     :failed to create window (2)",
	"     :invalid map (3)", "     :invalid resolution (4)",
	"     :invalid color (5)", "     :invalid texture (6)",
	"     :memory allocation error (7)"};

	write(2, "Error\n", 6);
	write(2, message[error], ft_strlen(message[error]));
	write(2, "\n", 1);
	exit(0);
}


int main(int argc, char **argv, char **env)
{
	if (argc != 5)
		ft_error(0);
	int fd_in;
	int fd_out;
	int fd_buffer;
	pid_t	pid;
	char **path;
	char *fullpath = find_path(env);
	char *fullest_path = malloc(ft_strlen(fullpath) + 1 - 5);
	int i = 0;
	int j = 5;
	while (fullpath[j])
	{
		fullest_path[i] = fullpath[j];
		i++;
		j++;
	}
	fullest_path[i] = '\0';
	char **paths = ft_split(fullest_path, ':');

	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	fd_buffer = open(".buffer", O_CREAT | O_TRUNC | O_RDWR, 0644);

	path = ft_split(argv[2], ' ');
	
	pid = fork();
	dup2(fd_in, 0);
	dup2(fd_buffer, 1);
	if (pid < 0) return -1;
	else if (pid == 0)
	{
		i = 0;
		while (paths[i] != NULL)
		{
			if (!execve(ft_strjoin(ft_strjoin(paths[i], "/"), path[0]), path, env))
			{
				exit(0);
			}
			i++;
		}
	}

	path = ft_split(argv[3], ' ');
	close(fd_buffer);
	fd_buffer = open(".buffer", O_RDWR, 0644);
	pid = fork();
	dup2(fd_buffer, 0);
	dup2(fd_out, 1);
	if (pid < 0) return -1;
	else if (pid == 0)
	{
		i = 0;
		while (paths[i] != NULL)
		{
			if (!execve(ft_strjoin(ft_strjoin(paths[i], "/"), path[0]), path, env))
			{
				exit(0);
			}
			i++;
		}
	}

}