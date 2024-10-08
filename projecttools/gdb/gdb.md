# GDB

gdb filename

gdb attach pid

gdb 调试带参数的程序：

```bash
gdb a.out
set args ...
show args
del args
#例：
gdb ./redis-cli
set args -h xxx -p xxx -a xxx  (不用加“”)
```



查看虚函数表：

```
info vtbl 类对象指针或引用
```

watch: `watch i`监控变量，当值发生变化时会停下来，并产生一个 watchpoint,类似vs中watch，停止监控和删除断点一样`del 1`。

display: 在break打断点之后使用display，就不用每次在断点停下来后再手动输入命令`p i`查看了。





### 调试多进程

- 调试父进程
  
- `set follow-fork-mode parent`(默认)
  
- 调试子进程

  - `set follow-fork-mode child`

- 设置调试模式：

  - set detach-on-fork [on|off], 默认是on(也就是你在调试父进程时候，子进程也在跑)。

    $\color{orange} {表示调试当前进程的时候，其他的进程继续运行，如果用off,调试当前进程的时候，其他的进程被gdb挂起。}$			

- 查看调试的进程

  - `info inferiors`

    $\color{orange} {想要查看调试的进程ID，必须先设置 `set detach-on-fork off` ,否则其他进程会一直跑干扰查看进程ID}$

- 切换当前调试的进程

  - `inferior 进程id`(此id非pid，是前面的NUM)

    $\color{orange}{要想调试过程中切换进程id,也必须先设置一下 `set detach-on-fork`}$

### 调试多线程

  - 查看线程
    
    - `info threads`
    
  - 将程序执行流锁定在当前线程, 禁止上下文切换
    
    - `set scheduler-locking on`
    
  - 不锁定任何线程，所有线程都执行
    
    - `set scheduler-locking off`
    
  - 组织其他线程在当前线程单步调试时抢占当前线程, 当next、continue、until、finish等其他线程才会执行
    
    - `set scheduler-locking step`：在两个线程函数分别打两个断点，执行next命令的时候会从当前线程跳到另一个线程的断点处，所谓step就是在线程间单步跳转，如果另一个线程没有断点，则会一直往下执行。
    
  - 显示当前线程scheduler-locking状态
    
    - `show scheduler-locking`
    
  - 切换线程
    
    - `thread id` 
    
  - 所有线程都执行命令
    
    语法：thread apply all [cmd]
    
    ```bash
    thread apply all next #所有线程执行next命令
    ```
    
  - 部分线程执行命令

    语法：thread apply <thread-id> <command>

    ```bash
    thread apply 1 2 3 next  # 在1 2 3线程上执行命令next命令
    thread apply 1 2 3 bt # 查看1 2 3线程堆栈
    ```



### 设置条件断点

```
break main.cpp:1766 if  lid==84207100863061979

```

 

