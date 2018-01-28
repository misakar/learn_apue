#include "../apue.h"

static int pfd1[2], pfd2[2]; // 管道端口文件描述符数组

void TELL_WAIT(void) {
    /***
     * 进程间同步初始化
     */
    // 创建2个管道
    if (pipe(pfd1) < 0 || pipe(pfd2) < 0) {
        err_sys("pipe error");
    }
}

void TELL_PARENT(pid_t pid) {
    /***
     * 子进程唤醒父进程
     */
    if (write(pfd2[1], "c", 1) != 1) {
        err_sys("write error");
    }
}

void WAIT_CHILD() {
    /***
     * 父进程等待子进程通知
     */
    char c;
    if (read(pfd2[0], &c, 1) != 1) {
        err_sys("read error");
    }

    if (c != 'c') {
        err_quit("WAIT_CHILD: incorrect data");
    }
}

void TELL_CHILD(pid_t pid) {
    /***
     * 父进程唤醒子进程
     */
    if (write(pfd1[1], "p", 1) != 1) {
        err_sys("write error");
    }
}

void WAIT_PARENT() {
    /***
     * 子进程等待父进程通知
     */
    char c;
    if (read(pfd1[0], &c, 1) != 1) {
        err_sys("read error");
    }

    if (c != 'p') {
        err_quit("WAIT_PARENT: incorrect data");
    }
}
