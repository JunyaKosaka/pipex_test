#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t spawnChild(const char* program, char** arg_list)
{
    pid_t ch_pid = fork();
    if (ch_pid > 0) {
        printf("spawn child with pid - %d\n", ch_pid);
        return ch_pid;
    } else {
        execvp(program, arg_list);
		printf("hello,error\n");
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    const char *args[] = { "/bin/ls", NULL, NULL };

    pid_t child;
    int wstatus;

    child = spawnChild("/bin/ls", args);

    if (waitpid(child, &wstatus, WUNTRACED | WCONTINUED) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
	printf("exit_success\n");
    exit(EXIT_SUCCESS);
}
