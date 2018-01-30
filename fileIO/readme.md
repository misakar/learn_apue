# 文件I/O

Unix Philosophy: **``everything is a file``**

## 基础API

### open

```C
#include <fcntl.h>

int open(const char* path, int oflag, ... /* mode_t mode */);
int openat(int fd, const char* path, int oflag, ... /* mode_t mode */);
```

+ [``check_TRUNC.c``](https://github.com/misakar/learn_apue/blob/master/fileIO/check_TRUNC.c): 测试``O_TRUNC`` flag

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

``whence的值:``

+ ``SEEK_SET``: 文件开头
+ ``SEEK_CUR``: 当前文件位置
+ ``SEEK_END``: 文件末尾


+ [``check_offset.c``](https://github.com/misakar/learn_apue/blob/master/fileIO/check_offset.c): 测试文件描述符指向的设备能否设置偏移
+ [``file_hole.c``](https://github.com/misakar/learn_apue/blob/master/fileIO/file_hole.c): 文件空洞

### read and write

```C
#include <unistd.h>

ssize_t read(int fd, void* buf, size_t nbytes);
ssize_t write(int fd, const void* buf, size_t nbytes);
```

+ [``read_write_copy.c``](https://github.com/misakar/learn_apue/blob/master/fileIO/read_write_copy.c): 只使用read和write函数复制一个文件

``read ahead``: <br/>
当操作系统检测到程序正进行顺序读取时, 系统就试图读入比应用所要求的更多数据(放入高速缓存), 假想应用很快就会读这些数据.

<hr/>

## 文件共享

``进程打开文件的数据结构``:

1. ``进程文件描述符表``
2. ``内核文件表``
3. ``v-node和i-node``
    + linux系统只有通用i-node(包括与文件无关的i-node)

![](https://notes.shichao.io/apue/figure_3.7_600.png)

``2个进程打开同一文件:``

![](https://notes.shichao.io/apue/figure_3.8_600.png)

v节点上的数据会被写入磁盘, 在打开文件时从磁盘读入内存, 涉及v节点改变的操作会进行磁盘IO. lseek仅仅改变文件偏移量(修改文件表项), 不进行任何IO操作. <br/>

## 原子操作

``要么不执行、要么执行完``

+ ``lseek + read/write`` => 原子操作: ``pread/pwrite``
+ ``open + creat`` => 原子操作: ``open(O_CREAT|O_EXCL)``

## dup/dup2

> 复制文件描述符

![](https://notes.shichao.io/apue/figure_3.9_600.png)

## sync/fsync/fdatasync

``同步内核文件高速缓存到硬盘``

+ ``void sync(void);``: 同步所有文件缓存到硬盘, 无需等待数据写入硬盘就返回
+ ``int fsync(int fd)``: 同步fd指向的文件的缓存到磁盘, 需等待数据完全写入硬盘后返回
+ ``int fdatasync(int fd)``: 相比于fsync, 只把文件数据写入硬盘而不更新文件状态

## fcntl

> 终于到fcntl了, 看这一章的目的就是为了解决libuv中的uv__cloexec_fcntl, lib2333!
