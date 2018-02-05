#include "../apue.h"
#include <dirent.h>

int main(int argc, char** argv) {
    DIR* dp; // a pointer to the directory stream
    struct dirent* dirp;

    if (argc != 2) {
        err_quit("usage: ./a.out <directory name>");
    }
    // The  opendir() function opens a directory stream corresponding to the directory name,
    // and returns a pointer to the directory stream.  The stream is positioned at the first
    // entry in the directory.
    if ((dp = opendir(argv[1])) == NULL) {
        err_sys("can't open %s", argv[1]);
    }

    // The  readdir() function returns a pointer to a dirent structure representing the next
    // directory entry in the directory stream pointed to  by  dirp.   It  returns  NULL  on
    // reaching the end of the directory stream or if an error occurred.

    // In the glibc implementation, the dirent structure is defined as follows:

    // struct dirent {
    //     ino_t          d_ino;       /* Inode number */
    //     off_t          d_off;       /* Not an offset; see below */
    //     unsigned short d_reclen;    /* Length of this record */
    //     unsigned char  d_type;      /* Type of file; not supported by all filesystem types */
    //     char           d_name[256]; /* Null-terminated filename */
    // };

    // The  only  fields in the dirent structure that are mandated by POSIX.1 are d_name and
    // d_ino.  The other fields are unstandardized, and not  present  on  all  systems; 
    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }

    // close directory stream
    closedir(dp);
    return 0;
}
