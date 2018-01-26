#include "../apue.h"

int main(void) {
    int n;
    int fd[2]; // 管道的读写两端
    pid_t pid;
    char line[MAXLINE];

    // pipe: 创建管道(目前还是单进程管道)
    if (pipe(fd) < 0) {
        err_sys("pipe error");
    }
    // fork: 创建父进程和子进程间的管道
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    }
    else if (pid > 0) {
        // parent process
        close(fd[0]); // 关闭父进程的读端
        write(fd[1], "hello world\n", 12); // write to child through PIPE
    }
    else {
        // child process
        close(fd[1]); // 关闭子进程的写端
        // 从内核缓冲区中读取数据, 并
        // 拷贝到用户定义缓冲区line
        n = read(fd[0], line, MAXLINE);
        // 子进程写入到标准输出
        write(STDOUT_FILENO, line, n);
    }
    exit(0);
}
