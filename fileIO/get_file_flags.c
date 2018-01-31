#include "../apue.h"
#include <fcntl.h>

int main(int argc, char** argv) {
    int val;

    if (argc != 2) {
        // 参数个数
        // 第0个参数表示文件名
        err_quit("usage: ./a.out <file descriptor>");
    }

    // 拿到当前文件的所有flags
    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
        err_sys("fcntl error for fd %d", atoi(argv[1]));
    }

    // 使用屏蔽字O_ACCMODE获取文件访问方式位
    // O_ACCMODE: 3
    switch (val & O_ACCMODE) {
        // O_RDONLY, O_WRONLY, O_RDWR是相互排斥的(文件状态只能取其一)
        case O_RDONLY:
            printf("read only");
            break;

        case O_WRONLY:
            printf("write only");
            break;

        case O_RDWR:
            printf("read write");
            break;

        default:
            err_dump("unknown access mode");
    }

    // 剩下的文件状态可以同时拥有
    if (val & O_APPEND) {
        printf(", append");
    }
    if (val & O_NONBLOCK) {
        printf(", nonblocking");
    }
    if (val & O_SYNC) {
        printf(", synchronous writes");
    }

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (val & O_FSYNC) {
        printf(", synchronous writes");
    }
#endif

    printf("\n");
    return 0;
}
