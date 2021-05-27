#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_env
{
	char			**splitted;
	char			**env;
	pid_t			pid;
	int				status;
}					t_env;

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	**path_splitization(char **env);
char	*find_line(char **env);
int		execute_command(t_env set, char *command, int input, int output);
char	*create_path(char *path, char *command);
void	set_fd(int input, int output);
void	do_child_things(t_env set, char **args);
void	ft_error(int error);
void	ft_free(char **dst);

#endif