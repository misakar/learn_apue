#include "../apue.h"

#define BUFFSIZE 4096

int main(int argc, char** argv) {
    int n;
    char buf[BUFFSIZE];

    // 从标准输入读文件名
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        // 将拷贝写入到标准输出
        if (write(STDOUT_FILENO, buf, n) != n) {
            err_sys("write error");
        }
    }
    if (n == -1) {
        err_sys("read error");
    }

    return 0;
}
