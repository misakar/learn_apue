# 进程

## 进程生命周期

内核使程序执行的唯一方法是调用一个exec函数; 进程自愿终止的唯一方法是显示或隐式的调用``_exit``或``_Exit``. 进程也可非自愿的被一个信号终止.

    exit(main(argc, argv))

## 进程退出

![](https://pic002.cnblogs.com/img/liangxing0728/201008/2010082017493036.jpg)

+ [atexit注册进程退出处理函数(exit handler)]()

## 命令行参数

## 环境表

    extern char** environ

## C程序的存储空间布局

![](https://pic002.cnblogs.com/img/liangxing0728/201008/2010082017501680.jpg)
堆位于bss和栈之间, 栈由高地址向低地址扩展, 堆反之, 两者间有大量内存空间可以被利用.
![apue_process1](https://user-images.githubusercontent.com/10671733/36149031-1eb621ac-10f9-11e8-9aef-573f2df3e9b7.png)

```shell
$ size a.out

text    data     bss     dec     hex filename
1794     592      16    2402     962 a.out
```

## 存储空间分配

## 环境变量

环境表初始存放在进程地址空间顶部, 位于内核映像和栈之间, 大小固定. 当添加新的环境变量时, 需要malloc/realloc将environ表拷贝到堆上.<br/>
环境变量表最后一个表项为空指针A

## setjmp和longjmp

参看[这篇文章](http://www.misakar.me/coroutine_in_c/)关于setjmp和longjmp实现协程的部分.

+ [setjmp/longjmp实现错误处理]()
+ [寄存器环境恢复对各类型变量的影响]()
