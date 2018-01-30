#include "../apue.h"
#include <fcntl.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char** argv) {
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0) {
        err_sys("creat error");
    }

    if (write(fd, buf1, 10) != 10) {
        err_sys("buf1 write error");
    }

    if (lseek(fd, 16384, SEEK_SET) == -1) {
        err_sys("lseek error");
    }
    // 文件中形成空洞
    // 空洞的值会被读为0
    // 空洞不会占用磁盘块
    if (write(fd, buf2, 10) != 10) {
        err_sys("buf2, write error");
    }

    return 0;
}
