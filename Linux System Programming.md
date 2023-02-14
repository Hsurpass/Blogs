# 目录

[TOC]



# Linux System Programming

大多数系统调用成功返回0,失败返回-1。

## 基本的文件IO

Linux的文件类型：普通文件(-)，目录文件(d)，管道文件(p)，链接文件(l)，字符设备文件(c)，套接字文件(s)

每个进程都有一个进程控制块PCB，以task_struct结构体来保存。task_struct中有个文件描述符表file_struct, 用来保存进程中的所有文件描述符。一个进程默认打开三个文件描述符：标准输入、输出、错误。(0,1,2)

![1.2.PCB_processcontrolblock进程控制块](image/1.2.PCB_processcontrolblock%E8%BF%9B%E7%A8%8B%E6%8E%A7%E5%88%B6%E5%9D%97.png)

### 文件访问的系统调用

在使用与文件相关的系统调用前，应该包含`fcntl.h和unistd.h`两个头文件。

#### 文件的创建、打开和关闭，读与写

fd=open(),fd=create(),close(fd)

```c++
ssize_t read(int fd, void *buf, size_t count);	// 成功返回读到的字节数，失败返回-1.
//文件是没有'\0'的概念的；字符串才有。如果读的是字符串，末尾是不会加'\0'的。
// read被EINTR中断，文件指针不会移动，所以需要重新读数据。

ssize_t write(int fd, const void* buf, size_t count);// 成功返回实际写入的字节数，失败返-1.
```

#### 文件的读写位置

```c++
off_t lseek(int fd, off_t offest, int whence);//移动文件指针到指定位置
// fd: 文件描述符
//offset：移动的偏移量，单位为字节数
//whence: 文件指针移动偏移量的解释，有三个选项，如下：
//宏名称 		含义
//SEEK_SET: 从文件头开始计算，文件指针移动到offset个字节位置。
//SEEK_CUR: 从文件指针当前位置开始计算，向后移动offset个字节的位置。
//SEEK_END: 文件指针移动到文件结尾
//example:
	file_size = lseek(fd_lseek, 0, SEEK_END);	// 移动文件指针到末尾
	off_t ret = lseek(fd, 0xFFFFFFFFl, SEEK_SET);	// 移动文件指针到这么多字节处
```

#### 修改文件的属性

```c++
int fcntl(int fd, int cmd);
int fcntl(int fd, int cmd, long arg);// fcntl(fd, F_GETFL, 0) fcntl(fd, F_SETFL, 0)
```

#### dup/dup2

==重定向文件描述符fd指向另一个文件结构体file_struct。==

```c++
int dup(int oldfd); //复制一个文件描述符指向oldfd的file结构体
int dup2(int oldfd, int newfd); //复制newfd文件描述符指向oldfd的file结构体,newfd如果已经被使用，则先关闭。
```

file_struct中有引用计数，会记录有多少个引用计数指向它，引用计数为0时释放。

![2.8dup_dup2](image/2.8dup_dup2.png)



如果两次open同一个文件，会得到两个文件描述符，它们分别指向不同的文件结构体，各自有自己的filestatus和读写位置；但两个file_struct指向同一个vnode, vnode又指向同一个inode。

![2.9多次open同一文件_and_dup同一文件](image/2.9%E5%A4%9A%E6%AC%A1open%E5%90%8C%E4%B8%80%E6%96%87%E4%BB%B6_and_dup%E5%90%8C%E4%B8%80%E6%96%87%E4%BB%B6.png)



## 进程Process

进程：最小的资源分配单位。

每个进程都有一个进程控制块PCB，task_struct。

### 进程的环境变量

每个进程都有一个环境变量表，它是在进程生成时从父进程拷贝过来的。

![image-20230214161701146](image/image-20230214161701146.png)

### 创建进程

fork: 在父进程返回子进程的pid，在子进程返回0，失败返回-1

除了pid不一样以外，其他基本都一样，包括文件描述符的指向，所以fork之后，父子进程共享同一个file_struct。

### 终止进程以及进程返回值

```c++
void exit(int status);	// 终止当前进程，发送一个SIGCHLD信号通知父进程，并把进程状态返回给父进程。
```

### 回收进程

子进程终止的时候必须由父进程回收PCB，没有回收则子进程处于僵尸状态(==僵尸进程==)。

如果父进程在子进程终止之前退出，那么该子进程由init进程回收。这时子进程被称作==孤儿进程==。



### 孤儿进程

### 僵尸进程

### 守护进程



### 进程间通信

#### 信号

#### 管道

无名管道

​	pipe,半双工通信

​	存在于内存中，只能在父子进程或兄弟进程间通信

有名管道

​	有名的文件，可以在不同的进程间通信。

#### 消息队列

#### 信号量(命名信号量)

进程间的同步

#### 共享内存 posix mmap

两个或多个进程读写同一块内存

共享内存是最快的IPC

#### socket

#### eventfd



## Thread

- 线程:最小的程序执行单位

### 线程的创建，使用和回收

### 多线程的同步互斥

#### 	atomic

​	(多线程对一个变量进行++操作，使用atomic比使用mutex的效率高), gcc提供的同步函数

#### 	锁:

##### 		互斥锁

###### 			死锁

			1. 
			1. 

1. ​		一把锁，自己锁自己(递归调用)

2. 两把锁，两个线程调用锁的顺序相反， 解决c++11 std::  一起锁，一起释放

    pstack lock_wait查看调用栈是否有死锁现象。

##### 递归锁

##### 检错锁

读写锁 读共享，写独占，写锁优先级高(默认是读优先，需要改属性)， boost::shared_mutex内部实现就是读写锁

##### 自旋锁

##### 文件锁

#### 条件变量

(生产者消费者模型)  和mutex一起使用， 内部有加锁，解锁的操作，所以要使用unique_lock, lockguard没有lock(),unlock()成员函数，但是lockguard的开销最少。

#### 信号量(匿名信号量)

二值信号量可以模拟互斥锁 (生产者消费者模型)

### 线程的局部存储 

#### __thread

只能使用POD类型

#### pthread_key_t

非POD类型可以使用

### 线程池 (生产线程，消费线程)

  **条件变量+互斥锁能解决大部分的线程同步问题**



### 内存池



## references:

[linux系统编程.pdf](../wangguilin/-6- linux系统编程与网络编程/linux系统编程.pdf)

[C_C++多线程编程精髓.md](./fanli/C_C++多线程编程精髓.md)



