#include "../apue.h"

static void charatatime(char*);

int main(int argc, char** argv) {
    pid_t pid;

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    }
    // race condition
    else if (pid > 0) {
        // parent
        charatatime("output from parent\n");
        TELL_CHILD(pid);
    }
    else {
        // child
        WAIT_PARENT();
        charatatime("output from child\n");
    }
    return 0;
}

static void charatatime(char* str) {
    /***
     * 没有做任何进程同步
     */
    char* ptr;
    int c;

    setbuf(stdout, NULL);
    for (ptr = str; *ptr != '\0'; ptr++) {
        putc(*ptr, stdout);
    }
}
