#include "../apue.h"
#include <fcntl.h>

int main(int argc, char** argv) {
    char* filename = argv[1];
    /* test O_TRUNC */
    // 截断文件长度为0
    open(filename, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
    return 0;
}
