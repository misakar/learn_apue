#include "../apue.h"
#include <sys/wait.h>

// 使用/bin/more/作为默认分页输出程序
#define DEF_PAGER "/bin/more/"

int main(int argc, char** argv) {
    int n;
    int fds[2]; // 管道的读写端
    pid_t pid;
    char* pager; // 分页程序
    char* argv0;
    char buf[MAXLINE]; // 用户缓冲区
    FILE* fp;

    if (argc != 2) {
        err_quit("usage: ./a.out <pathname>");
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        err_sys("can't open %s", argv[1]);
    }
    // pipe:创建管道(目前还是单进程管道)
    if (pipe(fds) < 0) {
        err_sys("pipe error");
    }
    // fork:创建父子进程间的管道
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    }
    else if (pid > 0) {
        // parent
        close(fds[0]); // 关闭父进程的读端
        /***
         *          char *fgets(char *s, int size, FILE *stream);
         *
         * fgets()  reads  in  at  most  one less than size characters from stream 
         * and stores them into the buffer pointed to by s. 
         * Reading stops after an EOF or a newline. If a newline is read, it is stored into the buffer. 
         * A terminating null byte ('\0') is stored after the last character in the buffer.
         */ 
        // 将文件数据读到buf
        while (fgets(buf, MAXLINE, fp) != NULL) {
            n = strlen(buf);
            // 将buf中的数据写入管道
            if (write(fds[1], buf, n) != n) {
                err_sys("write pipe error");
            }
        }
        // The function ferror() tests the error indicator for the stream pointed to by fp,
        // returning nonzero if it is set.
        // The error indicator can be reset only by the clearerr() function.                                   
        if (ferror(fp)) {
            // error indicator set error flag
            err_sys("fgets error");
        }

        close(fds[1]); // 文件数据写完成, 关闭写端

        // 避免产生僵尸进程(僵尸好可爱)
        if (waitpid(pid, NULL, 0) < 0) {
            err_sys("waitpid error");
        }
        exit(0);
    }
    else {
        // child: 调用分页程序显示文件数据(写标准输入)
        close(fds[1]); // 关闭子进程的写端
        if (fds[0] != STDIN_FILENO) {
            // The dup() system call creates a copy of the file descriptor oldfd,
            // using the lowest-numbered unused file descriptor for the new descriptor.
            //
            // int dup2(int oldfd, int newfd);
            //
            //   The dup2() system call performs the same task as dup(),
            //   but instead of using the lowest-numbered unused file descriptor,
            //   it uses the file descriptor number specified in newfd.
            //   If the file descriptor newfd was previously open, it is silently closed before being reused.
            if (dup2(fds[0], STDIN_FILENO) != STDIN_FILENO) {
                err_sys("dup2 error");
            }
            close(fds[0]);  // 使用拷贝到STDIN_FILENO的fp就行了
        }
        pager = DEF_PAGER;
        // char *strrchr(const char *s, int c); 
        //   The strrchr() function returns a pointer to the last occurrence of the character c in the string s. 
        if ((argv0 = strrchr(pager, '/')) != NULL) {
            argv0++;  // 绝对路径处理, 跳过最右的'/'; 类似web里的URL重定向
        }
        else {
            argv0 = pager;
        }
        // exec: 调用分页输出程序
        // int execl(const char *path, const char *arg, ...
        //                /* (char  *) NULL */);
        if (execlp(pager, argv0, (char*)NULL) < 0) {
            err_sys("execlp error");  // error ?
        }
    }

    return 0;
}
