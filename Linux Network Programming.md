# 目录

[TOC]



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



三次握手

四次挥手

滑动窗口

拥塞控制

粘包。



## references:

[linux网络基础.pdf](../wangguilin/-6- linux系统编程与网络编程/linux网络基础.pdf)

# HTTP

- cookie和session：
    cookie保存在客户端，session保存在服务端，当访问量增多session会影响服务器的的性能
    cookie不安全


