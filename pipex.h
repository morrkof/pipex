#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char *find_path(char **env);
void	ft_error(int error);

#endif