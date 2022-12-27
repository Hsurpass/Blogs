# C

## stdarg.h

### 可变参函数

variable_parameter_function.c

### 可变参宏

```c++
// 宏定义的参数允许用"...", 表示是可变参数，在宏替换的时候用__VA_ARGS__表示"..."位置的所有参数
#define test1(...) printf(__VA_ARGS__)
#define test2(fmt, ...) printf(fmt, __VA_ARGS__)

// 很多编译器扩展了可变参数的宏替换，这样的写法更容易记忆，
// 宏定义的参数后面可以带三个小数点，表示这里是可变参数，
// 宏替换的时候，直接写这个参数就表示这个位置是所有的可变参数了。
// 注：某些编译器需要用 ##args 表示 args... 位置所有的参数的宏替换。
#define test3(fmt...) printf(fmt)
#define test4(fmt, args...) printf(fmt, args)
```

variable_parameter_macro.c



## references:



# C++

## 关键字

### new/delete 和 malloc/free 区别：

1. new/delete是关键字，malloc/free是函数
2. new/delete会调用构造和析构函数。
3. 内存分配失败，new会抛异常bad_alloc

### static
1. 修饰全局变量:作用域和生命周期都在全局，不能跨文件使用
2. 修饰局部变量:作用域在函数内, 生命周期在全局。
3. 修饰函数:不能跨文件使用
4. 修饰类成员:类内定义，类外初始化，全部对象共享一个static成员变量
5. 修饰类成员函数: 只能访问static成员变量(没有this指针).

### const

1. const int *p : p所指向的值不可变
2. int* const p:  p这个地址不可变
3. const修饰成员函数，只能用const对象访问。
4. const可以作为函数重载的条件

### volatile

[volatile](<../ElegantTest/test_cpp/keyword/volatile/volatile.md>)

### explicit

只能用于修饰一个参数的构造函数，阻止隐式转换



## 模板

### 模板特化

template.cpp

### 嵌套从属类型需要加typename

template_nested_type.cpp

### 可变参数模板

当我们既不知道参数的数目又不知道参数的类型的时候，就可以使用可变参数模板。

默认参数都是传值的，如果参数是类，效率很低，所以改成传引用 `ARGS&... args` or `ARGS&&... args`

C++Primer 第5版 16.4

variadic_template.cpp

https://www.modb.pro/db/463275

### 非类型模板参数

```c++
template<typename T, int N> func(T (&arr)[N])
```

nonType_template_param.cpp



## references:

[C++基础与提高-王桂林-4rd.pdf](../wangguilin/-3- 这可能是你见过的最NB的C++课程/C++基础与提高-王桂林-4rd.pdf)

[C++基础与提高-王桂林-3rd.pdf](../wangguilin/-3- 这可能是你见过的最NB的C++课程/C++基础与提高-王桂林-3rd.pdf)

[EffectiveC++第3版中文版.pdf](../../1RecommendedBooks/Effective C++/EffectiveC++第3版中文版.pdf)

[C++ Primer（第5版）_带书签_高清完整版.pdf](../../1RecommendedBooks/C++Primer 第5版/C++ Primer（第5版）_带书签_高清完整版.pdf)

# STL

## 容器
### 序列式容器(Sequence Containers)

#### vector

 底层是数组，超过容量后会成倍增长，resize会调用构造函数，随机访问迭代器，取元素比较高效，在尾部插入元素比较高效，中间插入比较低效(会有元素的搬移)

#### deque

一个管理器和多个缓冲区，支持随机访问，首尾增删比较高效。

#### list
底层是双向链表，双向迭代器，不支持随机访问，插入删除元素比较高效。

### 容器适配器(Adapter)

#### stack

容器适配器，底层结构可以选用vector,deque, list 

#### queue
容器适配器，底层结构可以选用deque, list. vector没有pop_back

#### priority_queue: 底层可以使vector, 算法为二叉堆

### 关联式容器(Associative Containers)

#### set
红黑树, 自定义类型需要重载operator<()

#### map
rb operator[]需要有默认的构造函数, 查找复杂度O(logn)

####  multimap

#### multiset
rb

### 无序容器(Unordered Containers)
#### unordered_map
hash表, 自定义类型需要重载operator==()，并提供hash-func

#### unordered_set
hash表

#### unordered_multimap
hash表

#### unordered_multiset
hash表



## 迭代器

迭代器失效

## 算法

### lambda表达式

#### 闭包



## references:

[-4- 用好STL才是王道](../wangguilin/-4- 用好STL才是王道/)

[STL-王桂林-3nd.pdf](../wangguilin/-4- 用好STL才是王道/STL-王桂林-3nd.pdf)

[C++-STL使用例子大全.pdf](../wangguilin/-4- 用好STL才是王道/C++-STL使用例子大全.pdf)

# C++11

## KeyWord
### auto

### decltype

### initializer_list

可以接受多个参数，但必须是同一类型



## Smart Pointer
### auto_ptr
复制和复制都会改变所有权
### unique_ptr
不能copy，assign
### share_ptr
引用计数
### weak_ptr
监视share_ptr, 不会增加引用计数，lock()函数提升为shared_ptr,引用计数加1. 
  weak_ptr可以解决share_ptr循环引用造成的内存泄漏问题。

# Algorithm

## 数据结构
### 数组
### 链表
### 栈
### 队列
### 树 
#### 二叉树
#### 二叉搜索树
左子树都比根节点小，右子树都比根节点大。
#### 平衡搜索二叉树
(解决二插搜索树退化成链表的问题)
  1. 左子树都比根节点小，右子树都比根节点大。
  2. 左右子树高度差不超过1

#### AVL-tree:
  平衡因子：导致不平衡的最小子树的根节点

  ```
        5       5               5       5
       /         \             /         \
      3           8           3           8
     /             \           \         /
    1              10           4       7
  1.左旋：以某个节点的右子树为根节点的右子树插入节点导致不平衡     
  2.右旋: 以某个节点的左子树为根节点的左子树插入节点导致不平衡
  3.左右旋: 以某个节点的左子树为根节点的右子树插入节点导致不平衡
  4.右左旋: 以某个节点的右子树为根节点的左子树插入节点导致不平衡
  ```

#### rbtree
    rb-tree特性:
      
      1.每个节点或者是红色，或者是黑色。
      2.根节点是黑色。
      3.叶子结点是黑色。
      4.如果一个节点是红色，那么他的左右孩子为黑色。
      5.从一个节点到该节点的子孙节点的所有路径上包含$\color{red} {相同数目的黑节点}$。

### 二叉堆

### hash

## 算法

### sort

#### bubble sort



### search

#### linear search

#### binary search

### graph theory



## references:

[数据结构与算法(CC++实现)视频教程](../wangguilin/-3.5- 数据结构与算法(CC++实现)视频教程)

[数据结构与算法-王桂林-2nd .pdf](../wangguilin/-3.5- 数据结构与算法(CC++实现)视频教程/数据结构与算法-王桂林-2nd .pdf)

# Design Patterns
## 单例 singleton pattern
### 饿汉式
### 懒汉式
### pthread_once muduo

## 观察者 observer pattern
## 工厂模式 factor pattern
## 装饰模式 decorator pattern

## references:

[设计模式_王桂林_3rd .pdf](../wangguilin/-4.5- 设计模式/设计模式_王桂林_3rd .pdf)



# Linux Basic

[Linux 系统编程-基础篇12_05.pdf](../wangguilin/-5- linux基础课程/Linux 系统编程-基础篇12_05.pdf)

[linux](../ElegantTest/linux)

[command.md](../ElegantTest/linux/command.md)

[gcc_g++.md](../ElegantTest/linux/gcc_g++.md)

[ubuntu换源.md](../ElegantTest/linux/ubuntu换源.md)

# Linux System Programming
## Process
- 进程:最小的资源分配单位
### 进程间通信
#### 信号
#### 管道
(有名管道pipe,管道只能单工通信)

#### 消息队列
#### 信号量(命名信号量)
#### 共享内存 posix mmap
#### socket
#### eventfd

## Thread
- 线程:最小的程序执行单位
### 线程的创建，使用和回收
### 多线程的同步互斥
#### atomic

(多线程对一个变量进行++操作，使用atomic比使用mutex的效率高), gcc提供的同步函数

#### 锁:
##### 互斥锁
###### 死锁
1. 一把锁，自己锁自己(递归调用)

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

## references:

[linux系统编程.pdf](../wangguilin/-6- linux系统编程与网络编程/linux系统编程.pdf)

[C_C++多线程编程精髓.md](./fanli/C_C++多线程编程精髓.md)

# Linux Network Programming
  ### 如何判断大小端

```c++
  union bl
  {
      int data; // 0x12345678
      char byte;    // 0x78 -->低字节放在低地址：小端
      // uint8_t byte;
  };
```

- 2.

## references:

[linux网络基础.pdf](../wangguilin/-6- linux系统编程与网络编程/linux网络基础.pdf)

# HTTP

- cookie和session：
  cookie保存在客户端，session保存在服务端，当访问量增多session会影响服务器的的性能
  cookie不安全



# Boost

## asio



# Script Language

## Python

[md](../ElegantTest/test_python/md)

[notes.md](../ElegantTest/test_python/md/notes.md)

[pip.md](../ElegantTest/test_python/md/pip.md)

[编码.md](../ElegantTest/test_python/md/编码.md)



## Shell

[shell编程.pdf](../wangguilin/-5- linux基础课程/shell编程.pdf)

## JavaScript && Typescript

## Lua

# GDB

[Linux GDB调试指南.md](./fanli/Linux GDB调试指南.md)

[gdb.md](../ElegantTest/test_gdb/gdb.md)

## CGDB

[cgdb.md](../ElegantTest/test_gdb/cgdb.md)

[cgdb-manual-in-chinese](../../4openSourceCode/cgdb-manual-in-chinese)

# Cmake 

[cmake.md](../ElegantTest/test_cmake/md/cmake.md)

[Cmake入门到精通笔记(全).pdf](./pdf/cmake/Cmake入门到精通笔记(全).pdf)

[从零开始详细介绍CMake.pdf](./pdf/cmake/从零开始详细介绍CMake.pdf)

# Makefile

[LinuxMakefile.pdf](../wangguilin/-5- linux基础课程/LinuxMakefile.pdf)

# Git

[git.md](../ElegantTest/git/git.md)

[cherry_pick.md](../ElegantTest/git/cherry_pick.md)

# Muduo

[study.md](../../4openSourceCode/muduo/md/study.md)

[muduo-manual-20120626.pdf](./pdf/muduo-manual/muduo-manual-20120626.pdf)

[《Linux多线程服务端编程：使用muduo C++网络库》.(陈硕).[PDF]@ckook.pdf](../../1RecommendedBooks/Linux多线程服务端编程/《Linux多线程服务端编程：使用muduo C++网络库》.(陈硕).[PDF]@ckook.pdf)

# Redis

[redis.md](../ElegantTest/redis/redis.md)

# Mongodb





# Nginx



# Nodejs



# Protobuf



# Others

## build environment

[buildEnvironment.md](./1buildEnvironment/buildEnvironment.md)

## markdown

[markdown](./markdown)

[MarkDown.md](./markdown/MarkDown.md)

[mermaid的[流程图][类图][时序图]的使用范例.md](./markdown/mermaid的[流程图][类图][时序图]的使用范例.md)

## microsoft

[microsoft](./microsoft)

[win_command.md](./microsoft/win_command.md)

[windows快捷键.md](./microsoft/windows快捷键.md)

[wsl.md](./microsoft/wsl.md)

[下载vscode历史版本.md](./microsoft/下载vscode历史版本.md)

## science surfing internet

[science surfing internet](./science surfing internet)

[science_surfing_internet.md](./science surfing internet/science_surfing_internet.md)

