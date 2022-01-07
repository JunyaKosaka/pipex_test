#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(-1);
    }

    pid = fork();
    printf("pid is %5d, pipefd %d %d\n", pid, pipefd[0], pipefd[1]);
    if (pid == 0)
    {
        // 子プロセス
        // write(pipefd[1], "from child\n", 12);
        dup2(pipefd[1], 1);
        printf("from child %d\n", pid);
        close(pipefd[0]); //エラー処理省略
        close(pipefd[1]); //エラー処理省略
        // write(pipefd[1], "27 row\n", 7);
        exit(0);
    }
    else
    {
        // 親
        int wstatus;
        waitpid(pid, &wstatus, WUNTRACED);
        // write(pipefd[0], "aaa\n", 4);
        dup2(pipefd[0], 0);
        close(pipefd[1]); //エラー処理省略
        close(pipefd[0]); //エラー処理省略
        char *arg[] = {"/usr/bin/wc", NULL};
        // char **envp = {NULL};
        execve("/usr/bin/wc", arg, envp);
        // write(pipefd[0], "bb\n", 4);
        // パイプからの読み込み
    }
    char buf[128];
    // read(pipefd[0], buf, sizeof(buf)); //エラー処理省略
    // printf("parent %d %s\n", pid, buf);
    printf("45 row\n");
    // if (pipe(pipefd) < 0) {
    //     perror("pipe");
    //     exit(-1);
    // }
    // printf("pipefd %d %d\n", pipefd[0], pipefd[1]);

    close(pipefd[1]); //エラー処理省略
    close(pipefd[0]); //エラー処理省略
    // // パイプへの書き込み
    // char *s = "test";
    // write(pipefd[1], s, strlen(s)); //エラー処理省略
    // printf("buf=[%s]\n", buf);

    return 0;
}
