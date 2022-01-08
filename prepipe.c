#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_info
{
	int		pipefd[2];
	int		argc;
	char	**argv;	
	char	**envp;
	pid_t	pid;
}	t_info;

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
		read(info.pipefd[0], buf, sizeof(buf));
		//dup2(info.pipefd[])
		printf("[%s\n]", buf);
		printf("[parent:%s, %s]", info.argv[1], info.argv[2]);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	info.argv = argv;
	info.envp = envp;


	if (pipe(info.pipefd) < 0)
	{
		perror("pipe");
		exit(-1);
	}
	start_process(info);
	exit(0);
}
