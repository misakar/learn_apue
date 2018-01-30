# 文件I/O

Unix Philosophy: **``everything is a file``**

## 基础API

### open

```C
#include <fcntl.h>

int open(const char* path, int oflag, ... /* mode_t mode */);
int openat(int fd, const char* path, int oflag, ... /* mode_t mode */);
```

+ [``check_TRUNC.c``](): 测试``O_TRUNC`` flag

### creat

open函数出现之前, 使用creat函数创建新文件

```C
#include <fcntl.h>

int creat(const char* path, mode_t mode);

// 等价于

open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
```

推荐使用open, 通过设置oflag可以灵活的实现文件创建后的读写操作.

### close

```C
#include <unistd.h>

int close (int fd);
```

关闭某个文件描述符. 当一个进程终止时, 内核会自动关闭它打开的所有文件.

### lseek

```C
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

whence的值:

+ ``SEEK_SET``: 文件开头
+ ``SEEK_CUR``: 当前文件位置
+ ``SEEK_END``: 文件末尾

+ [``check_offset.c``](): 测试文件描述符指向的设备能否设置偏移
+ [``file_hole.c``](): 文件空洞

### read and write

```C
#include <unistd.h>

ssize_t read(int fd, void* buf, size_t nbytes);
ssize_t write(int fd, const void* buf, size_t nbytes);
```

+ [``read_write_copy.c``](): 只使用read和write函数复制一个文件

``read ahead``: <br/>
当操作系统检测到程序正进行顺序读取时, 系统就试图读入比应用所要求的更多数据(放入高速缓存), 假想应用很快就会读这些数据.
