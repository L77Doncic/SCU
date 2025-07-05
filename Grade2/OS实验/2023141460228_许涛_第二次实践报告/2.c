#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork失败\n");
        exit(1);
    } else if (pid == 0) {
        // 子进程调用 exec 执行 ls 命令
        execlp("ls", "ls", NULL);
        // 若 exec 失败，输出错误信息
        perror("execlp失败");
        exit(1);
    } else {
        // 父进程等待子进程结束
        wait(NULL);
        printf("父进程退出。\n");
    }
    return 0;
}