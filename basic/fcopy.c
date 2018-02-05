#include "../apue.h"

#define BUFSIZE 4096

int main(int argc, char** argv) {
    int n;
    char buf[BUFSIZE];

    // 区别stdin: extern FILE*
    // unbuffered-IO
    while ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            err_sys("write error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }

    return 0;
}
