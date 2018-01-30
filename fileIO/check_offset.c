#include "../apue.h"

int main(int argc, char** argv) {
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
        /* 文件描述符所指向的对象不能设置偏移量(比如管道、FIFO、网络套接字) */
        fprintf(stderr, "cannot seek\n");
    }
    else {
        printf("seek ok\n");
    }

    return 0;
}
