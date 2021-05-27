#include "pipex.h"

int execute_command(char **paths, char *command, int input, int output, char **env)
{
	int status;
	char **path;
	pid_t	pid;
	int i = 0;
	path = ft_split(command, ' ');
	dup2(input, 0);
	close(input);
	dup2(output, 1);
	close(output);
	pid = fork();
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
	else
		waitpid(pid, &status, 0);
	return 0;
}

int main(int argc, char **argv, char **env)
{
	if (argc != 5)
		ft_error(0);
	int fd_in;
	int fd_out;
	int pipefd[2];
	// pid_t	pid;
	// int status;
	// char **path;
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
	pipe(pipefd);
	execute_command(paths, argv[2], fd_in, pipefd[1], env);
	execute_command(paths, argv[3], pipefd[0], fd_out, env);


	// path = ft_split(argv[2], ' ');
	// dup2(fd_in, 0);
	// close(fd_in);
	// dup2(pipefd[1], 1);
	// close(pipefd[1]);
	// pid = fork();
	// if (pid < 0) return -1;
	// else if (pid == 0)
	// {
	// 	i = 0;
	// 	while (paths[i] != NULL)
	// 	{
	// 		if (!execve(ft_strjoin(ft_strjoin(paths[i], "/"), path[0]), path, env))
	// 		{
	// 			exit(0);
	// 		}
	// 		i++;
	// 	}
	// }
	// else
	// 	waitpid(pid, &status, 0);
	
	// path = ft_split(argv[3], ' ');
	// dup2(pipefd[0], 0);
	// close(pipefd[0]);
	// dup2(fd_out, 1);
	// close(fd_out);
	// pid = fork();
	// if (pid < 0) return -1;
	// else if (pid == 0)
	// {
	// 	i = 0;
	// 	while (paths[i] != NULL)
	// 	{
	// 		if (!execve(ft_strjoin(ft_strjoin(paths[i], "/"), path[0]), path, env))
	// 		{
	// 			exit(0);
	// 		}
	// 		i++;
	// 	}
	// }
	// else
	// 	waitpid(pid, &status, 0);
}