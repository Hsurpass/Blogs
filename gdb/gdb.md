# **GDB**

查看虚函数表：

```
info vtbl xxx
```







### 调试多进程

- 调试父进程
  
- `set follow-fork-mode parent`(默认)
  
- 调试子进程

  - `set follow-fork-mode child`

- 设置调试模式：

  - set detach-on-fork [on|off], 默认是on(也就是你在调试父进程时候，子进程也在跑)。

    $\color{red} {表示调试当前进程的时候，其他的进程继续运行，如果用off,调试当前进程的时候，其他的进程被gdb挂起。}$			

- 查看调试的进程

  - `info inferiors`

    $\color{red} {想要查看调试的进程ID，必须先设置 `set detach-on-fork off` ,否则其他进程会一直跑干扰查看进程ID}$

- 切换当前调试的进程

  - `inferior 进程id`(此id非pid，是前面的NUM)

    $\color{red}{要想调试过程中切换进程id,也必须先设置一下 `set detach-on-on-fork`}$

### 调试多线程