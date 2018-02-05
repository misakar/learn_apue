#include "../apue.h"

int main(void) {
    int c;

    while (( c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
            err_sys("output error");
        }
    }

    // The function ferror() tests the error indicator for the stream pointed to by stream,
    // returning  nonzero if it is set.  The error indicator can be reset only by the clear‐
    // err() function.
    if (ferror(stdin)) {
        err_sys("input error");
    }

    return 0;
}
