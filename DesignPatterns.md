# 目录





# Design Patterns

## 单例 singleton pattern

**一个类只产生一个实例**。

单例模式可以分为**懒汉式和饿汉式**，两者之间的区别在于**创建实例的时间不同**。

### 饿汉式

指系统一运行，就初始化创建实例，当需要时，直接调用即可。（本身就线程安全，没有多线程的问题）

### 懒汉式

指系统运行中，实例并不存在，**只有当需要使用该实例时，才会去创建并使用实例**。（这种方式要考虑线程安全）

#### double check

double check的好处：减少锁的获取，提高性能。如果只用一个check，每次调用getInstance时都要进行加锁的操作，性能较低。

double check的问题：即使是双检查也不是线程安全的。因为new这一操作分为三步：1.分配内存，2.调用构造函数，3.返回指针。第2、3步有可能会发生指令重排，如果先返回指针，此时另一个线程调用了getInstance得到了实例，但是构造函数还没调用，此时会发生错误。

解决懒汉式单例的线程安全问题：

1. 使用pthread_once （muduo库中使用）
2. 在c++11标准中，直接使用一个**局部的静态实例**，它是线程安全的。



### reference:

[C++ 线程安全的单例模式总结](https://zhuanlan.zhihu.com/p/83539039)

[C++ and the Perils of Double-Checked Locking](https://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf)



## 观察者 observer pattern

## 工厂模式 factor pattern

## 装饰模式 decorator pattern





