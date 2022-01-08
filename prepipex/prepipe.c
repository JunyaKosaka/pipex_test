#include "pipex.h"

int	start_process(t_info info)
{
	int	wstatus;

	printf("%d:%d\n", info.pipefd[0], info.pipefd[1]);
	info.pid = fork();

	if (info.pid == 0)
	{
		printf("[child:%s, %s]", info.argv[1], info.argv[2]);
		close(info.pipefd[0]);
		dup2(info.pipefd[1], 1);
		execve(info.argv[1], &info.argv[1], info.envp);
	}
	else
	{
		waitpid(info.pid, &wstatus, WUNTRACED);
		close(info.pipefd[1]);
		char buf[100000];
		dup2(info.pipefd[0], 0);
		read(info.pipefd[0], buf, sizeof(buf));
		//dup2(info.pipefd[])
		printf("[%s\n]", buf);
		printf("[parent:%s, %s]", info.argv[1], info.argv[2]);
	}
	return (0);
}

void	check_args(t_info info)
{
		if (is_valid_file(info) == false)
				exit(1);
		printf("running\n");
		if (is_valid_cmds(info) == false)
				exit(1);
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	info.argv = argv;
	info.envp = envp;

	//check_args(info);
	if (pipe(info.pipefd) < 0)
	{
		perror("pipe");
		exit(-1);
	}
	start_process(info);
	exit(0);
}
