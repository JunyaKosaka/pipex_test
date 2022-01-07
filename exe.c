#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


//int main(int argc, char **argv, char **envp)
int main(int argc, char **argv, char **envp)
{
	pid_t pid = -10;
//	system("echo $$");

	printf("hello_%d\n", pid);
	system("echo $$");
	pid = fork();
	printf("=============\n");
	printf("15%d\n", pid);
	if (pid == 0)
	{
		printf("ch%d\n", pid);
		printf("child\n");
		execve(argv[1], &argv[1], envp);
	}
	else
	{
		printf("pa%d\n", pid);
		printf("parent\n");
	}
	return (0);
}
