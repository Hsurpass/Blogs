# 目录

[TOC]



# Linux Network Programming

## 计算机网络

### 网络分层模型

#### TCP/IP模型

链路层(或者叫网络接口层)，网络层，传输层，应用层。（网网传应，链网传应）

#### OSI模型

物理层，数据链路层，网络层，传输层，会话层，表示层，应用层。（物数网传会表应）

![image-20230218161305178](image/image-20230218161305178.png)

### 数据的封包与拆包

数据在经过每一层时会在前面==封装==协议头部，最后封装成帧，传输给目的主机，目的主机接收到以太网帧再经过每一层的==拆包==最后得到数据。

以http协议发送数据包为例：

![image-20230218172339005](image/image-20230218172339005.png)

每一层对数据封装后都会有不同的称谓：传输层叫做TCP**段(segment)**，网络层叫IP**数据报(datagram)**，数据链路层叫以太网**帧(frame)**。

### 物理层

### 数据链路层

#### 以太网帧

##### 以太网帧格式

![image-20230218211851743](image/image-20230218211851743.png)

协议类型对应三种：IP，ARP，RARP。

以太网帧中数据长度最小46字节，最大1500字节。最大值1500称为以太网的最大传输单元(==MTU==)。如果数据包超过MTU则要进行分片。**不够46字节，则要补填充位**，例如：ARP和RARP数据包长度不够46字节就要在后面补填充位。

### 网络层

#### ICMP协议



#### IP协议

Internet Protocol，网际协议。

##### IP数据报格式

![image-20230219123056568](image/image-20230219123056568.png)



#### ARP协议

Address Resolution Protocol，地址解析协议。**每台主机都维护一个arp缓存表，使用`arp -a`查看。**

##### arp协议的功能

获取目的主机的物理地址（MAC地址）。

##### arp协议的作用

在网络通信时，数据包是先被==网卡==接收到的，然后再依次拆包传送到应用层，如果接收数据包的主机的物理地址与目的主机物理地址不一样，则丢弃。==因此在通信前必须获得目的主机的物理地址。==

##### arp协议格式

![image-20230218162811001](image/image-20230218162811001.png)

#### ICMP协议

Internet Control Message Protocol，网际控制报文协议





### 传输层

#### TCP协议

Transmission Control Protocol，传输控制协议

##### TCP头部





#### UDP协议

##### UDP头部





### 会话层

### 表示层

### 应用层

#### http协议



## 网络IO模型

读写IO大致分为两个操作：

1.   等待：等待socket的可读或可写事件被触发。
2.   拷贝数据：将内核的数据拷贝到用户进程(read)，将用户进程的数据拷贝到内核(write)。

### 同步阻塞IO

```
read(fd, buffer, count)
```

等待事件触发和拷贝完数据，read才会返回。如果没有数据就会之一阻塞等待。

### 同步非阻塞IO

```c++
int flags = fcntl(socket, F_GETFL, 0);
fcntl(socket, F_SETFL, flags | O_NONBLOCK);
```

使用fcntl设置fd属性为O_NONBLOCK，如果没有可读的数据就会立即返回，不会阻塞当前线程，一般使用轮询的方式来不断的检查是否有数据可读，但是拷贝数据的操作还是同步的。

### 异步IO

**在调用read的时候会马上返回， 不等待条件触发，而且等拷贝完数据才通过某种方式(例如：回调)通知用户。**

linux下虽然提供了aio的接口，但对异步的支持并不好，只是把同步封装了一层，像boost.asio。windows IOCP对异步支持比较好。



## TCP



### 字节序

#### 如何判断大小端

```c++
  union bl
  {
      int data; // 0x12345678
      char byte;    // 0x78 -->低字节放在低地址：小端
      // uint8_t byte;
  };
```







[TCP 为什么是三次握手，而不是两次或四次？](https://www.zhihu.com/question/24853633/answer/115173386)

三次握手

四次挥手

流量控制

滑动窗口

拥塞控制

-   慢开始( slow-start )
-   拥塞避免( congestion avoidance )
-   快重传( fast retransmit )
-   快恢复( fast recovery )

粘包。

2MSL

#### TCP 与 UDP 的区别

## references:

[linux网络基础.pdf](../wangguilin/-6- linux系统编程与网络编程/linux网络基础.pdf)

# HTTP

- cookie和session：
    cookie保存在客户端，session保存在服务端，当访问量增多session会影响服务器的的性能
    cookie不安全

