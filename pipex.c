#include "pipex.h"

char	*create_path(char *path, char *command)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(path, "/");
	result = ft_strjoin(tmp, command);
	free (tmp);
	return (result);
}

void	set_fd(int input, int output)
{
	dup2(input, 0);
	close(input);
	dup2(output, 1);
	close(output);
}

void	do_child_things(t_env set, char **args)
{
	int		i;
	char	*path;

	i = 0;
	while (set.splitted[i] != NULL)
	{
		path = create_path(set.splitted[i], args[0]);
		if (!execve(path, args, set.env))
		{
			free(path);
			exit(0);
		}
		free(path);
		i++;
	}
}

int	execute_command(t_env set, char *command, int input, int output)
{
	char	**args;

	args = ft_split(command, ' ');
	set_fd(input, output);
	set.pid = fork();
	if (set.pid < 0)
		ft_error(3);
	else if (set.pid == 0)
		do_child_things(set, args);
	else
		waitpid(set.pid, &(set.status), 0);
	ft_free(args);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_env	set;
	int		fd_in;
	int		fd_out;
	int		pipefd[2];

	if (argc != 5)
		ft_error(0);
	set.env = env;
	set.splitted = path_splitization(env);
	if (!set.splitted)
		ft_error(2);
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_in < 0 || fd_out < 0)
		ft_error(1);
	pipe(pipefd);
	execute_command(set, argv[2], fd_in, pipefd[1]);
	execute_command(set, argv[3], pipefd[0], fd_out);
	ft_free(set.splitted);
}
