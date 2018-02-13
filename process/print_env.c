#include "../apue.h"

extern char** environ;  // environment pointer

int main(int argc, char** argv /*, char** envp POSIX不推荐使用*/) {
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s ", environ[i]);
    }
    printf("\n");
    return 0;
}
