#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    pid_t childpid;
    int retval;
    int status;

    childpid = fork();

    if (childpid >= 0) {
        if (childpid == 0) {  // 子进程
            printf("CHILD: I am the child process! \n");
            printf("CHILD: Here's my PID: %d\n", getpid());       // 获取当前PID
            printf("CHILD: My parent's PID is: %d\n", getppid());  // 获取父进程PID
            printf("CHILD: The value of fork return is: %d\n", childpid);
            printf("CHILD: Sleep for 1 second...\n");
            sleep(1);
            printf("CHILD: Enter an exit value (0~255): ");
            scanf("%d", &retval);
            printf("CHILD: Google! \n");
            exit(retval);
        } else {  // 父进程
            printf("Parent: I am the parent process! \n");
            printf("Parent: Here's my PID: %d\n", getpid());        // 获取当前PID
            printf("Parent: The value of my child's PID is: %d\n", childpid);
            printf("Parent: I will now wait for my child to exit.\n");
            wait(&status);  // 等待并收回子进程
            printf("Parent: Child's exit code is: %d\n", WEXITSTATUS(status));
            printf("Parent: Google! \n");
            exit(0);
        }
    } else {  // fork失败
        perror("fork error!");
        exit(0);
    }

    return 0;
}