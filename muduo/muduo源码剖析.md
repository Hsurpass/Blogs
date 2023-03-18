# Muduo是什么？

[muduo](https://github.com/chenshuo/muduo)是[陈硕](http://chenshuo.com/)大神个人开发的C++的TCP网络编程库。muduo基于Reactor模式实现。Reactor模式也是目前大多数Linux端高性能网络编程框架和网络应用所选择的主要[架构](https://so.csdn.net/so/search?q=架构&spm=1001.2101.3001.7020)，例如内存数据库Redis和Java的Netty库等。

陈硕的《Linux多线程服务器端编程》一书对muduo整个架构进行了非常详尽的介绍和分析，可以说是学习muduo源码和设计理念最好的资料了。这本书也非常推荐大家购买阅读，感觉是后台开发的必读书目了。

而本文则主要是从源码角度辅助理解整个muduo的实现，同时也姑且算是对muduo的一个小小的补充。

同时提供了一个[muduo注释版](https://github.com/chenyahui/AnnotatedCode/tree/master/muduo)，以辅助大家参考学习。

# muduo的架构和概念

muduo中类的职责和概念划分的非常清晰，在《Linux多线程服务器端编程》一书的6.3.1章节有详细的介绍。实际上目前很多网络库的接口设计也都受到了muduo的影响，例如360的evpp等。

而 muduo 的整体风格受到 Netty 的影响，整个架构依照 Reactor 模式，基本与如下图所示相符：

![单线程 Reactor 模式](image/single_thread_reactor.png)

所谓 Reactor 模式，是指有一个循环的过程，不断监听对应事件是否触发，事件触发时调用对应的 **callback** 进行处理。

这里的事件在 muduo 中包括 Socket 可读写事件、定时器事件。在其他网络库中如 libevent 也包括了 signal、用户自定义事件等。

负责事件循环的部分在 muduo 被命名为 `EventLoop`，这个命名也基本是个约定语了，其他库如 Netty、libevent 也都有对应的组件。

负责监听事件是否触发的部分，在 muduo 中叫做 `Poller`。muduo 提供了 epoll 和 poll 两种来实现，默认是 epoll 实现。通过环境变量 `MUDUO_USE_POLL` 来决定是否使用 poll:

```c++
Poller* Poller::newDefaultPoller(EventLoop* loop)
{
  // 通过此环境变量来决定使用poll还是epoll
  if (::getenv("MUDUO_USE_POLL"))
  {
    return new PollPoller(loop);
  }
  else
  {
    return new EPollPoller(loop);
  }
}
```

此外，图中的acceptor负责accept新连接，并将新连接分发到subReactor。这个组件在muduo中也叫做`Acceptor`。 关于图中的其他部分，会在 [muduo 的线程模型](#muduo 的线程模型) 一节有详细介绍。

# 一个简单的例子

本文首先从最简单的echo server入手，来介绍muduo的基本使用，同时也方便后面概念的理解。

```c++
void onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf,
                           muduo::Timestamp time)
{
  conn->send(buf);
}

int main()
{
    muduo::net::EventLoop loop;//建立一个事件循环器EventLoop
    muduo::net::InetAddress listenAddr(2007);
    TcpServer server(&loop, listenAddr);//建立对应的业务服务器TcpServer
    server.setMessageCallback(onMessage);//设置TcpServer的Callback
    server.start();//启动server
    loop.loop();//开启事件循环
}
```

echo-server的代码量非常简洁。一个典型的muduo的TcpServer工作流程如下：

1. 建立一个事件循环器 EventLoop
2. 建立对应的业务服务器 TcpServer
3. 设置 TcpServer 的 Callback
4. 启动 server
5. 开启事件循环

 <u>==陈硕认为，TCP网络编程的本质是处理三个半事件==</u>，即：

- 连接的建立
- 连接的断开：包括主动断开和被动断开
- 消息到达，文件描述符可读。
- 消息发送完毕。这个算半个事件。

# 连接的建立

在我们单纯使用linux的API，编写一个简单的Tcp服务器时，建立一个新的连接通常需要四步：

> 步骤 1. socket() // 调用 socket 函数建立监听 socket
> 步骤 2. bind() // 绑定地址和端口
> 步骤 3. listen() // 开始监听端口
> 步骤 4. accept() // 返回新建立连接的 fd

我们接下来分析下，这四个步骤在muduo中都是何时进行的：

首先在TcpServer对象构建时，TcpServer的属性acceptor同时也被建立。在Acceptor的构造函数中分别调用了socket函数和bind函数完成了步骤1和步骤2。即，当`TcpServer server(&loop, listenAddr)`$\color{orange} {执行结束时，监听socket已经建立好，并已绑定到对应地址和端口了。}$

而当执行$\color{orange} {server.start()}$时，主要做了两个工作：

1. 在监听socket上启动listen函数，也就是**步骤3**；
2. 将监听socket的可读事件注册到EventLoop中。

此时，程序已完成对socket的监听，但还不够，因为此时程序的主角 `EventLoop` 尚未启动。
当调用 `loop.loop()` 时，程序开始循环监听该 socket 的可读事件。

当新连接请求建立时，可读事件触发，此时该事件对应的 callback 在 EventLoop::loop() 中被调用。**该事件的 callback 实际上就是 Acceptor::handleRead() 方法。**

在 Acceptor::handleRead() 方法中，做了三件事：

1. 调用了 accept 函数，完成了 **步骤 4**，实现了连接的建立。得到一个已连接 socket 的 fd。
2. 创建 TcpConnection 对象。
3. 将已连接 socket 的可读事件注册到 EventLoop 中。

这里还有一个需要注意的点，创建的 ==TcpConnnection 对象是个 shared_ptr==，该对象会被保存在 TcpServer 的 connections 中。**这样才能保证引用计数大于 0，对象不被释放**。

至此，一个新的连接已完全建立好，该连接的socket可读事件也已注册到 EventLoop 中了。

# 消息的读取

上节讲到，在新连接建立的时候，会将新连接的 socket 的可读事件注册到 EventLoop 中。
假如客户端发送消息，导致已连接 socket 的可读事件触发，该事件对应的 callback 同样也会在 EventLoop::loop() 中被调用。

该事件的 callback 实际上就是 TcpConnection::handleRead 方法。
在 TcpConnection::handleRead 方法中，主要做了两件事：

1. 从 socket 中读取数据，并将其放入 inputbuffer 中
2. 调用 messageCallback，执行业务逻辑。

```c++
  ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
  if (n > 0)
  {
    messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
  }
```

<u>messageCallback 是在建立新连接时，将 `TcpServer::messageCallback` 方法 bind 到了 `TcpConnection::messageCallback` 的方法。</u>

`TcpServer::messageCallback` 就是业务逻辑的主要实现函数。通常情况下，我们可以在里面实现消息的编解码、消息的分发等工作，这里就不再深入探讨了。

在我们上面给出的示例代码中，echo-server 的 messageCallback 非常简单，就是直接将得到的数据，重新 send 回去。在实际的业务处理中，一般都会调用 TcpConnection::send() 方法，给客户端回复消息。

==这里需要注意的是==，在 messageCallback 中，用户会有可能会把任务抛给自定义的 Worker 线程池处理。
但是这个在 Worker 线程池中任务，**切忌直接对 Buffer 的操作**。因为 ==Buffer 并不是线程安全的。==

我们需要记住一个准则:

> **所有对 IO 和 buffer 的读写，都应该在 IO 线程中完成。**

一般情况下，先在交给 Worker 线程池之前，应该先在 IO 线程中把 Buffer 进行切分解包等动作。将解包后的消息交由线程池处理，避免多个线程操作同一个资源。

# 消息的发送

用户通过调用 TcpConnection::send() 向客户端回复消息。由于 muduo 中使用了 OutputBuffer，因此消息的发送过程比较复杂。

首先需要注意的是线程安全问题, 上文说到对于消息的读写必须都在 EventLoop 的同一个线程 (通常称为 IO 线程) 中进行。因此，TcpConnection::send 必须要保证线程安全性，它是这么做的：

```c++
void TcpConnection::send(const StringPiece& message)
{
  if (state_ == kConnected)
  {
    if (loop_->isInLoopThread())
    {
      sendInLoop(message);
    }
    else
    {
      void (TcpConnection::*fp)(const StringPiece& message) = &TcpConnection::sendInLoop;
      loop_->runInLoop(
          std::bind(fp,
                    this,     // FIXME
                    message.as_string()));
                    //std::forward<string>(message)));
    }
  }
}
```

检测 send 的时候，是否在当前 IO 线程，如果是的话，直接进行写相关操作 `sendInLoop`。
如果不在一个线程的话，需要将该任务抛给 IO 线程执行 `runInloop`, 以保证 write 动作是在 IO 线程中执行的。我们后面会讲解 `runInloop` 的具体实现。

在 sendInloop 中，做了下面几件事：

1. 假如 OutputBuffer 为空，则直接向 socket 写数据
2. 如果向 socket 写数据没有写完，则统计剩余的字节个数，并进行下一步。没有写完可能是因为此时 socket 的 TCP 缓冲区已满了。
3. 如果此时 OutputBuffer 中的旧数据的个数和未写完字节个数之和大于 highWaterMark，则将 highWaterMarkCallback 放入待执行队列中
4. **将对应 socket 的可写事件注册到 EventLoop 中**

==注意==：直到发送消息的时候，muduo 才会把 socket 的可写事件注册到了 EventLoop 中。在此之前只注册了可读事件。

连接 socket 的可写事件对应的 callback 是 TcpConnection::handleWrite()
当某个 socket 的可写事件触发时，TcpConnection::handleWrite 会做两个工作：

1. 尽可能将数据从 OutputBuffer 中向 socket 中 write 数据
2. 如果 OutputBuffer 没有剩余的，则 **将该 socket 的可写事件移除**，并调用 writeCompleteCallback

## 为什么要移除可写事件

因为当 OutputBuffer 中没数据时，我们不需要向 socket 中写入数据。但是此时 socket 一直是处于可写状态的， 这将会导致 TcpConnection::handleWrite() 一直被触发。然而这个触发毫无意义，因为并没有什么可以写的。

所以 muduo 的处理方式是，当 OutputBuffer 还有数据时，socket 可写事件是注册状态。当 OutputBuffer 为空时，则将 socket 的可写事件移除。

此外，==highWaterMarkCallback 和 writeCompleteCallback 一般配合使用，起到限流的作用==。在《linux 多线程服务器端编程》一书的 8.9.3 一节中有详细讲解。这里就不再赘述了。