![image-20220820092138087](image/image-20220820092138087.png)

![image-20220820092216252](image/image-20220820092216252.png)

![image-20220820092542526](image/image-20220820092542526.png)

reference:

https://blog.csdn.net/qq_41868108/article/details/105905682

https://blog.csdn.net/yolo_yyh/article/details/118367979

https://www.likecs.com/show-203883515.html?sc=1500

https://blog.csdn.net/weixin_43705457/article/details/104405603



# base 库

## Date.h

  ```
int julianDayNumber_;
  ```

 algorithm and explanation see:

  http://www.faqs.org/faqs/calendars/faq/part2/

  http://blog.csdn.net/Solstice

## TimeZone.h

  ```c++
struct TimeZone::Data
{
  vector<detail::Transition> transitions;
  vector<detail::Localtime> localtimes;
  vector<string> names;
  string abbreviation;
};

std::shared_ptr<Data> data_;
  ```



## Timestamp.h

### static_assert

### boost::less_than_comparable

只要实现operator<() const 就可自动实现<=,>,>=

less_than_comparable.cpp

### boost::equality_comparable

只要实现operator==() const ,就能自动实现operator !=()const

less_than_comparable.cpp

### gmtime_r



## Atomic.h

C/C++ 中数值操作，如自加 (n++) 自减 (n- -) 及赋值 (n=2) 操作都不是原子操作。

### gcc提供的常用原子性操作

```c++
// 原子自增操作，将value更新到*ptr，并返回操作之前*ptr的值
type __sync_fetch_and_add(type* ptr, type value)
    
// 原子比较和交换(设置)操作
// 比较*ptr与oldval的值，如果两者相等，则将newval更新到*ptr并返回操作之前*ptr的值
type __sync_val_compare_and_swap(type* ptr, type oldval, type newval)
// 比较*ptr与oldval的值，如果两者相等，则将newval更新到*ptr并返回true
bool __sync_bool_compare_and_swap(type* ptr, type oldval, type newval)
    
// 原子赋值操作，将*ptr设置为value,对*ptr加锁, 并返回*ptr操作之前的值.
type __sync_lock_test_and_set(type* ptr, type value) 

// 使用这些原子性操作，编译的时候需要加-march=cpu-type
// cpu-type就是cpu体系结构:(如:native, i386, pentium等) 
```

references: [Gcc内置原子操作__sync_系列函数简述及例程](https://zhuanlan.zhihu.com/p/32303037)

### volatile

[volatile](../../../3github/ElegantTest/test_cpp/keyword/volatile/volatile.md)



## Exception.h

### backtrace

栈回溯，保存各个栈帧的地址

### backtrace_symbols

根据地址，转成相应的函数符号。

backtrace_symbols 内部会调用malloc, 返回的指针需要由调用者释放。

![image-20221217105317559](image/image-20221217105317559.png)

### abi::__cxa_demangle

把函数符号转换成函数名

## Logging.h

### Logger类

Logger类时序图:

![image-20221218161609009](image/image-20221218161609009.png)

首先创建一个Logger对象，然后调用stream()方法，返回一个LogStream的对象，再调用LogStream的重载运算符operator <<()输出日志，这是比较宏观的。
		实际上的实现会更加细一点，在Logger类的内部有嵌套Impl类来负责实际的实现， Logger类就是负责一些日志的级别，是外层的一个日志类；而Impl类是借助LogStream类来输出日志的，LogStream对象重载<<运算符来输出日志。
		事实上，日志类是先输出到缓冲区**FixedBuffer**，然后再输出到标准输出或文件， 通过g_output函数来指定输出到哪里，借助g_flush函数刷新。因为g_output也是只能输出到指定设备/文件 的缓冲区，g_flush函数刷新一下才能真正到指定位置。

下面是类的调用流程:

![image-20221218161734176](image/image-20221218161734176.png)

以下是muduo日志库的默认消息格式:

![image-20221220120515899](image/image-20221220120515899.png)









### Impl类

类内私有类

### SourceFile类

类内共有类





# Reactor线程模型

## 1.单线程Reactor

**单线程reactor(one loop per thread)----->事件的监听，IO的读写，业务计算都在同一个线程处理。**

没有事件触发的时候，线程等待在select/poll/epoll等函数上，事件到达后进行读IO，解码，计算，编码，写IO等一系列操作。==这种模式适用于IO密集的应用，不太适合CPU密集的应用。==

![img](image/20210630194953729.png)

实际项目应用中，这种模型应该并不常用。

代码目录：muduo/examples/sudoku/server_basic.cc

Server_basic.cc是一个并发服务器，可以同时服务多个客户端连接，但是是单线程的。

其中最关键的是onMessage()函数，主要用来从缓冲区读取数据，并调用processRequest()去处理请求，其中全部的IO和计算任务都在同一个线程中进行。

## 2.单Reactor+线程池

**单线程reactor + threadpool ----> 事件的监听，IO的读写放在reactor线程处理，业务计算放到线程池。**

主线程负责监听事件，读写IO，线程池中的线程负责业务计算。这种模式适用于计算任务彼此独立，而且IO压力不大的场景，有乱序返回的可能，==客户端要根据id来匹配响应。==

![img](image/20210630195038604.png)

代码目录：muduo/examples/sudoku/server_threadpool.cc

与方案1的区别是多了ThreadPool对象，线程池大小由numThreads_指定，然后processRequest()中计算的部分由ThreadPool去执行。这种方案有乱序返回的可能，所以要根据id来匹配响应。

## 3.多Reactor(主从Reactor)

**主reactor线程(accept线程) + 子reactor线程：主reactor线程负责监听新连接的到来，然后把新连接分发给子reactor线程， 子reactor线程负责监听事件，读写IO以及业务计算。**

$\color{red} {muduo采用轮询方式选择sub Reactor}$），$\color{green} {该连接的所有操作都在那个sub Reactor所处的线程中完成。}$优点是能保证请求的顺序性，程序的总体处理能力不会随着连接增加而下降，适应性强，所以是muduo的默认多线程模型。

![img](image/20210630195106708.png)

代码目录：muduo/examples/sudoku/server_multiloop.cc

这种模式下只需要设置`server_.setThreadNum(numThreads_)`即可。TcpServer在这种模式下用Acceptor的EventLoop接受新连接，然后用EventLoop pool里的EventLoop去处理新连接IO。

## 4.主从Reactor + 线程池

主reactor线程(accept线程) + 子reactor线程 + threadPool:  **主reactor线程负责监听新连接的到来，然后把新连接分发给子reactor线程， 子reactor线程负责监听事件，读写IO, 业务计算在线程池中处理)**

既有多个Reactor来处理IO，也使用线程池来处理计算，这种模式适合既有突发IO，又有突发计算的应用。

![img](image/20210630195138947.png)

如何确定使用多少个EventLoop呢？

根据ZeroMQ手册的建议，按照每千兆比特每秒的吞吐量配一个event loop的比例来设置event loop的数目（即muduo::TcpServer::setThreadNum()的数量），所以在编写运行于千兆以太网上的网络程序时，用一个event loop就足以应付网络IO。==如果TCP连接有优先级之分，那使用一个event loop不太合适，最好是把高优先级的连接用单独的event loop来处理。==





https://zhuanlan.zhihu.com/p/85101271/

https://blog.csdn.net/qq_36533978/article/details/107975165?spm=1001.2014.3001.5501

https://www.cnblogs.com/fortunely/p/16127237.html#%E5%AE%9A%E6%97%B6%E4%BB%BB%E5%8A%A1

https://www.cnblogs.com/ailumiyana/p/10087539.html

https://www.cyhone.com/articles/analysis-of-muduo/



### 经典的服务器设计模式Reactor模式

大多数人学习Linux网络编程的起点可能都是从《UNP》开始的，书中描述的服务端程序架构基本上是一个大的while循环，程序阻塞在accept或poll函数上，等待被监控的socket描述符上出现预期的事件。事件到达后，accept或poll函数的阻塞解除，程序向下执行，根据socket描述符上出现的事件，执行read、write或错误处理。 
整体架构如下图所示： 

![image-20220928154233855](image/image-20220928154233855.png)

而muduo的整体风格受到netty的影响，整个架构依照Reactor模式，基本与如下图所示相符：

![image-20220928154736039](image/image-20220928154736039.png)



![image-20220928154853828](image/image-20220928154853828.png)







我们接下来分析下，这四个步骤在muduo中都是何时进行的：

首先在TcpServer对象构建时，TcpServer的属性acceptor同时也被建立。
在Acceptor的构造函数中分别调用了socket函数和bind函数完成了步骤1和步骤2。
即，当TcpServer server(&loop, listenAddr);$\color{red} {执行结束时，监听socket已经建立好，并已绑定到对应地址和端口了。}$
而当执行$\color{red} {server.start()}$时，主要做了两个工作：
    **1.在监听socket上启动listen函数，也就是步骤3；**
    **2.将监听socket的可读事件注册到EventLoop中。**
示意图如下:
    ![image-20220924202526117](image/image-20220924202526117.png)


此时，程序已完成对地址的监听，但还不够，因为此时程序的主角EventLoop尚未启动。

当调用$\color{red} {loop.loop()}$时，程序开始监听该socket的可读事件。

当新连接请求建立时，可读事件触发，此时该事件对应的callback在EventLoop::loop()中被调用。

该事件的callback实际上就是$\color{red} {Acceptor::handleRead()}$方法。

在Acceptor::handleRead()方法中，做了三件事：
```
    1.调用了accept函数，完成了步骤4，实现了连接的建立。得到一个已连接socket的fd
    2.创建TcpConnection对象
    3.将已连接socket的可读事件注册到EventLoop中。
```

这里还有一个需要注意的点，创建的TcpConnnection对象是个shared_ptr，该对象会被保存在TcpServer的connections中。$\color{red} {这样才能保证引用计数大于0，对象不被释放。}$

至此，一个新的连接已完全建立好，其可读事件也已注册到EventLoop中了。

![image-20220927171746079](image/image-20220927171746079.png)





![image-20220928153607311](image/image-20220928153607311.png)
