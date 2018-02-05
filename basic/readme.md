# UNIX基础知识

## Buffered VS Unbuffered IO

```
        +-------------------+-------------------+
        | Process A         | Process B         |
        +-------------------+-------------------+
        | C runtime library | C runtime library | C RTL buffers
        +-------------------+-------------------+
        |               OS caches               | Operating system buffers
        +---------------------------------------+
        |      Disk controller hardware cache   | Disk hardware buffers
        +---------------------------------------+
        |                   Disk                |
        +---------------------------------------+
```

+ ``open``, ``read``, ``write``, ``lseek``, ``close`` supports unbuffered IO

## Standard IO


