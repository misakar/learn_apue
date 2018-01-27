# PIPE

``管道(PIPE)``是Unix系统进行``进程间通信(IPC)``的重要手段, 管道的发明极大提升了Unix系统的易用性. 

+ [**``AT&T Archives: The UNIX Operating System``**](https://www.youtube.com/watch?v=tc4ROCJYbm0)
+ [**``Stream HandBook``**](https://github.com/substack/stream-handbook)

不过管道也有缺陷: Unix标准管道是``半双工的``, 即数据只能单向传递, 虽然现在不少``*nix``系统支持全双工管道, 但是不具有移植性; 此外管道作为一种数据传输的手段虽然是异步的, 但是需要依靠进程, 比较"昂贵".

<hr/>

## 管道的创建

+ [**``create_pipe.c``**](https://github.com/misakar/learn_apue/blob/master/pipe/create_pipe.c)

管道是进程间通信, 一般是``fork系统调用后创建父子进程间的管道``.

```

        -------------
        |           |
        |  process  |
        |           |
        -------------
             |-----------
             |     fork   \
             v             \ 
        -------------         \   ------------
        |           |  waitpid \  |          |
        |   parent  | --------->  |  child   |
        |           |_ __ __ __ __|          |
        |write:fd[1] _->_->_->_->_ read:fd[0]|
        |           |    pipe     |          |
        -------------             ------------
```
## 管道的应用

+ [**``more_pipe.c``**](https://github.com/misakar/learn_apue/blob/master/pipe/more_pipe.c): 文件分页显示