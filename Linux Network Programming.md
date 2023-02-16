# 目录

[TOC]



# Linux Network Programming

字节序

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

