# 目录





# Design Patterns

## 单例 singleton pattern

**一个类只产生一个实例**。

单例模式可以分为**懒汉式和饿汉式**，两者之间的区别在于**创建实例的时间不同**。

### 饿汉式

指系统一运行，就初始化创建实例，当需要时，直接调用即可。（本身就线程安全，没有多线程的问题）

### 懒汉式

指系统运行中，实例并不存在，**只有当需要使用该实例时，才会去创建并使用实例**。（这种方式要考虑线程安全）

### pthread_once muduo

## 观察者 observer pattern

## 工厂模式 factor pattern

## 装饰模式 decorator pattern





