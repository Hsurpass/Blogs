# 开篇词
## 1.多线程编程是后台开发人员的基本功

多年以前，技术面试的时候面试官经常会问“**程序什么时候需要开启新的线程**”这样的问题，那个时候多核 CPU 才刚开始普及，很多人也是才开始逐渐接触多线程技术。而如今多核 CPU 和多线程编程技术已经是下里巴人的技术了，因此本专栏不会花大气力再去回答“**程序什么时候需要开启新的线程**”这一类问题，简单地解释一下，就是为了提高解决问题的效率，毕竟大多数情况下，多个 CPU 并行做一件事总比单个 CPU 做要快很多。

然而，多线程程序虽然强大，但也让原来的程序执行流程变得复杂和具有一定的不确定性，比如带来资源的竞态问题，初学者或不能意识到带来的后果，或不能够很好处理这个问题，**帮助希望学好多线程编程的初中级读者理清多线程程序的执行原理和脉络是本专栏的创作的初衷之一**。

拜各种库和运行环境对操作系统多线程接口的封装，很多技术开发者做了很多年的开发，仍然只是个界面或者仅知道调用库的“业务”程序员，他们只能面向搜索引擎编程，遇到稍微复杂一点的多线程逻辑就不知如何下手了。

本专栏将从**操作系统原理的角度**介绍多线程技术的方方面面，从基础的知识到高级进阶，它们是笔者这些年工作的经验总结和踩过的坑的出来的教训。

本专栏的内容主要分为以下三大方面。

#### **一、操作系统层面上关于多线程和多线程协作的接口原理**

无论是哪种编程语言和库，其最终都是要运行在操作系统上的，应用程序本身的特性应该是决定采用何种编程工具的最主要因素，但是无论你采用什么样的编程语言，**通过了解操作系统 API 从而深入理解操作系统的工作原理**，这本身就有很重要的意义。

操作系统是一个非常复杂的系统，在 API 之上加一层编程语言并不能消除其复杂性，最多不过是把复杂性隐藏起来而已。说不定什么时候，复杂的那一面迟早会蹦出来拖你的后腿，懂得系统 API 能让你到时候可以更快地挣脱困境。

因此，针对多线程编程，本专栏将详细地介绍 Windows 和 Linux 操作系统层面上提供的各种多线程接口，理解并熟悉它们的使用后，读者在接触或者学习其他语言或者库提供的多线程功能时，可以快速地上手和掌握。

以**协程**这一技术为例，虽然**协程**是计算机操作系统原理之一，但是我们所接触的大多数操作系统并没有从系统层面上支持**协程**这一技术。而像 Golang 这一类语言是提供协程功能的，那这一类语言是如何支持的？如果你对操作系统的线程有着深入的了解，你也不难想明白：

> 线程是操作系统的内核对象，当多线程编程时，如果线程数过多，就会导致频繁地上下文切换，这些对性能是一种额外的损耗。例如，在一些高并发的网络服务器编程中，使用一个线程服务一个 socket 连接是很不明智的，因此现在的主流做法是利用操作系统提供了基于事件模式的异步编程模型，用少量的线程来服务大量的网络连接和 IO。但是采用异步和基于事件的编程模型，让程序代码变得复杂，非常容易出错，也提高了排查错误的难度。
>
> **协程**，是在应用层模拟的线程，**它避免了上下文切换的额外损耗**，同时又兼顾了多线程的优点，简化了高并发程序的复杂度。还是以上面的高并发网络服务器为例，可以为每一个 socket 连接使用一个协程来处理，在兼顾性能的情况下，代码也清晰。

再例如，**线程局部存储技术**是我们常用的一项多线程技术，**它的存在让每个线程可以有自己私有存放数据的空间。**那线程局部存储技术是如何实现的呢？本专栏中会庖丁解牛地介绍线程局部存储是什么以及它的实现原理。

#### **二、 基于操作系统多线程理论衍生出来的一些扩展理论模型和应用**

正因为存在多线程编程，所以有了线程池模型，据我了解，“线程池”的实现和原理应该是多线程编程新手问的、聊的最多的一个技术点了。本专栏会带领读者利用各种操作系统提供的线程同步对象来实现一个线程池，进而引出生产者消费者理论模型，再进一步升华，引出所谓的消息中间件，如 Kafka、RabbitMQ。对于技术方案，我们不推崇重复造轮子，但是一定要具有重复造轮子的能力和了解轮子的制造原理。有了这项能力之后，在使用一些开源的消息中间件时，我们因为“知其然、知其所以然”才会把这些软件在项目中用得更好。

这里再给大家说个小故事：

> 刚开始参加工作的那年，公司安排我开发一款即时通讯软件（IM，类似于 QQ 聊天软件），在这之前我心里也知道如果多线程操作一个整型值是要加锁的，但是当时为了图代码简便，而且在实际调试的时候，没有加锁的代码也从来没出过问题。于是我就心存侥幸了，觉得对整型值加锁真是多此一举。我们的软件有类似于 QQ 这种单人聊天功能，每个用户都有一个整型的 userid，问题就出在这里了。
>
> 当时公司的老板和他媳妇儿也使用这款软件，有一天早上老板在这个软件上给他媳妇发了一段亲密的话，由于多线程操作他媳妇儿的 userid 没加锁，最终变成了另外一个人的 userid，而这个 userid 恰好是我的账户。于是老板发给他媳妇儿的聊天内容都发给我了。我当时看到聊天内容很奇怪，还回复了他一句，并且还带上了我自己的姓名……事情的结果，可想而知了，老板非常尴尬也非常生气……从那以后，老板看我的眼神都是怪怪的。我自知理亏，再也不侥幸了，凡是多线程读写整型变量都养成加锁的好习惯。

这是我曾经犯过的错误，也就是所谓的**线程安全问题**。“年轻”时的作者，当时不明白为什么一个整型变量在多线程操作时存在安全问题，进而引起业务上的错乱问题。

本专栏中会详细地介绍多线程操作整型变量非线程安全的原因以及解决方案。掌握了这些，你在学习像 Java 语言时，就明白了为什么 JDK 在操作一个整型变量时提供 AtomicInteger 这样的类了。

#### **三、和多线程相关的，一些实际开发中的技巧和经验**

如果你是一名开发者，那么曾经或许会为下面一些问题而头痛过，这些问题或许你在面试时被面试官问到或者在实际开发中遇到过：

- 进程的 CPU 使用率过高如何查找原因并解决？
- 如何让一个程序只允许使用者运行一个实例？
- 在实际开发中，避免死锁有哪些可以遵循的规则？
- 什么是**条件变量的虚假唤醒**？虚假唤醒会带来什么问题？如何解决？
- 如何设计高效的线程池和队列模型？
- 如何在线程函数中访问类的成员变量和函数？

诸如此类实际开发中经常遇到问题，实在太多了，这里就不一一列举了。它们都和多线程有关，如果你还存在一些疑惑，你可以看看这个专栏。本专栏在保持主干脉络介绍的同时，也会穿插介绍一些与多线程相关的开发技巧和经验。

当然，多线程问题本来就比较复杂，尤其是本专栏同时介绍 Windows 和 Linux 两个操作系统平台的接口，在实际编写程序时，由于操作系统提供的 API 不一样，为了跨平台，我们不得不写许多跨平台代码。好在，C++ 11/14 标准给 C++ 引入了大量的多线程类和库，本专栏也会详尽地介绍它们的用法。

![avatar](image/FhKFFtIyrl5lUBo3MDfFzO_i5NaC)

#### 学习建议 vs 专栏寄语

由于操作系统调度线程时许的不确定性，同样的逻辑可能在不同机器、不同时刻有不同的行为表现，也因此增加了排查和定位问题的难度。这是在学习和开发多线程程序时不得不面临的问题。建议读者将专栏各个章节中的代码示例都实际在机器上运行一遍，认真、准确地理解每一个多线程同步原语的适用场景和性能优缺点。只要透彻地理解了这些操作系统提供的基础多线程同步原语，在面对它们的衍生物（如线程池、消息队列、协程技术等）时可以更快地学习和用好。

操作系统提供的 API 接口一般在相当长的时间内会保持不变的（至少保持向后兼容），一经学会，终生受用。在新技术新思想层出不穷、令人应接不暇时，掌握了操作系统层面的 API 和其设计思想原理，可以以不变应万变。

最后，多线程编程在现代软件开发中是如此的重要，以至于熟练使用多线程编程是一名合格的后台开发人员的**基本功**，它是如此的重要，希望本专栏能帮助你掌握它，愿它能让你彻底告别多线程编程烦恼。

#### 分享交流

我们为本专栏**付费读者**创建了微信交流群，以方便更有针对性地讨论专栏相关的问题（入群方式请到第 03 篇末尾查看，谢谢）。


# 第一部分: 线程的创建、使用与回收
## 2.线程的基本概念及常见问题

多年以前，技术面试的时候面试官经常会问“**程序什么时候需要开启新的线程**”这样的问题，当时多核 CPU 才刚开始普及，很多人也是才开始逐渐接触多线程技术。而如今多核 CPU 和多线程编程技术已经是下里巴人的技术了，因此本专栏内容不会花大气力再去回答“**程序什么时候需要开启新的线程**”这一类问题，简单地解释一下，就是为了提高解决问题的效率，毕竟大多数情况下，多个 CPU 并行做一件事总比单个 CPU 做要快很多吧（根本原因其实是：现在的面试官也很少再问“**程序什么时候需要开启新的线程**”这样的问题了，哈哈 ^_^）。

然而，多线程程序虽然强大，但也让原来的程序执行流程变得复杂和具有一定的不确定性，比如带来资源的竞态问题，初学者或不能意识到带来的后果，或不能够很好地处理这个问题。不过不用担心，这是本专栏要介绍的重点内容之一。

多线程编程在现代软件开发中是如此的重要，以至于熟练使用多线程编程是一名合格的后台开发人员的**基本功**，注意，我这里用的是**基本功**一词。它是如此的重要，因此更应该掌握它。本专栏将结合操作系统原理介绍多线程的方方面面，同时涉及到 Windows 和 Linux 两个平台的线程技术，从基础的知识到高级进阶，让我们开始吧。

### 线程的基本概念

线程的英文单词是 **thread**，翻译成对应的中文有“分支”、“枝干”的意思，当然这里翻译成“线程”属于意译了。提到线程就不得不提与线程相关联的另外一个概念“**进程**”，一个“**进程**”代表计算机中实际跑起来的一个程序，在现代操作系统的保护模式下，每个进程拥有自己独立的进程地址空间和上下文堆栈。但是就一个程序本身执行的操作来说，进程其实什么也不做（不执行任何进程代码），它只是提供一个大环境容器，在进程中实际的执行体是“**线程**”。

**wiki** 百科上给线程的定义是：

> In computer science, a thread of execution is the smallest sequence of programmed instructions that can be managed independently by a scheduler, which is typically a part of the operating system.
>
> 计算机科学中，线程是操作系统管理的、可以执行编制好的最小单位的指令序列的调度器。

翻译的有点拗口，通俗地来说，线程是进程中实际执行代码的最小单元，它由操作系统安排调度（何时启动、何时运行和暂停以及何时消亡）。

### 关于线程的常见问题

进程与线程的区别及关系这里就不再多说了，任何一本关于操作系统的书籍都会有详细地介绍。这里需要重点强调的是如下几个问题，这也是我们在实际开发中使用多线程需要搞明白的问题。

#### 一个进程至少有一个线程

上面也提到了，线程是进程中实际干活的单位，因此**一个进程至少得有一个线程**，我们把这个线程称之为“**主线程**”。

#### 主线程退出，支线程也将退出吗？

在 **Windows** 系统中，当一个进程存在多个线程时，如果主线程执行结束了，那么这个时候即使支线程（也可以叫**工作线程**）还没完成相关的代码执行，支线程也会退出，也就是说，主线程一旦退出整个进程也就结束了。之所以强调这一点是，很多多线程编程的初学者经常犯在工作线程写了很多逻辑代码，但是没有注意到主线程已经提前退出，导致这些工作线程的代码来不及执行。解决这一问题的方案很多，核心就是让主线程不要退出，或者至少在工作线程完成工作之前主线程不要退出**。常见的解决方案有主线程启动一个循环或者主线程等待工作线程退出后再退出**（下文将会详细介绍）。

在 **Linux** 系统中，如果主线程退出，工作线程一般不会受到影响，还会继续运行下去，但是此时这个进程就会变成所谓的**僵尸进程**，这是一种不好的做法，实际开发中应该避免产生僵尸进程。

```
### ps -ef 命令查看系统进程列表时，带有<defunct>字样的进程即僵尸进程
[root@localhost ~]# ps -ef
UID        PID  PPID  C STIME TTY          TIME CMD
root         2     0  0 Jan18 ?        00:00:01 [kthreadd]
root         3     2  0 Jan18 ?        00:00:25 [ksoftirqd/0]
root         5     2  0 Jan18 ?        00:00:00 [kworker/0:0H]
root     60928     1  0 14:48 pts/1    00:00:00 [linuxtid] <defunct>
```

> Linux 版本众多，在某些 Linux 版本实现中，主线程退出也会导致支线程退出，这个行为就和 Windows 上一样了。读者在实际开发时应该以自己的机器测试结果为准。

#### 某个线程崩溃，会导致进程退出吗？

这是一个常见的面试题，还有一种问法是：**进程中某个线程崩溃，是否会对其他线程造成影响？**

一般来说，每个线程都是独立执行的单位，每个线程都有自己的上下文堆栈，一个线程的崩溃不会对其他线程造成影响。但是通常情况下，一个线程崩溃会产生一个进程内的错误，例如，在 Linux 操作系统中，可能会产生一个 **Segment Fault** 错误，这个错误会产生一个信号，操作系统默认对这个信号的处理就是结束进程，整个进程都被销毁了，这样的话这个进程中存在的其他线程自然也就不存在了。

### 总结

本讲我们介绍了线程的基本概念以及和线程相关一些常见问题，它是多线程编程入门级的概念，希望读者可以掌握它们。



## 3.线程的创建与使用

### 线程的创建

在使用线程之前，我们首先要学会如何创建一个新的线程。不管是哪个库还是哪种高级语言（如 Java），线程的创建最终还是调用操作系统的 API 来进行的。我们这里先介绍操作系统的接口，这里分为 Linux 和 Windows 两个常用的操作系统平台来介绍。当然，这里并不是照本宣科地把 Linux man 手册或者 msdn 上的函数签名搬过来，而是只介绍我们实际开发中常用的参数和需要注意的重难点。

#### Linux 线程创建

Linux 平台上使用 **pthread_create** 这个 API 来创建线程，其函数签名如下。

```c++
int pthread_create(pthread_t *thread, 
                   const pthread_attr_t *attr,
                   void *(*start_routine) (void *), 
                   void *arg);
```

- 参数 **thread**，是一个输出参数，如果线程创建成功，则通过这个参数可以得到创建成功的线程 ID（下文会介绍线程 ID 的知识）。
- 参数 **attr** 指定了该线程的属性，一般设置为 NULL，表示使用默认属性。
- 参数 **start_routine** 指定了线程函数，这里需要注意的是这个函数的调用方式必须是 `__cdecl` 调用，即 C Declaration 的缩写，这是 C/C++ 中定义函数时默认的调用方式，一般很少有人注意到这一点。而后面我们介绍在 Windows 操作系统上使用 CreateThread 定义线程函数时必须使用  `__stdcall` 调用方式时，由于函数不是默认函数调用方式，所以我们必须显式声明函数的调用方式了。

也就是说，如下函数的调用方式是等价的：

```c++
//代码片段1： 不显式指定函数调用方式，其调用方式为默认的 __cdecl
void* start_routine (void* args)
{
}

//代码片段2： 显式指定函数调用方式为默认的 __cdecl，等价于代码片段1
void* __cdecl start_routine (void* args)
{
}
```

- 参数 **arg**，通过这一参数可以在创建线程时将某个参数传入线程函数中，由于这是一个 **void*** 类型，可以方便我们最大化地传入任意多的信息给线程函数（下文会介绍一个使用示例）。
- 返回值：如果成功创建线程，则返回 **0**；如果创建失败，则返回相应的错误码。常见的错误码有 **EAGAIN**、**EINVAL**。**EAGAIN** 表示系统资源不足导致线程无法创建（如达到系统限制的最大线程数目），**EINVAL** 表示传入了无效的参数 **attr**。在实际开发只要我们正确的设置了各个参数，一般不关心该函数的返回值，即一般认为线程可以正确创建出来。

下面是一个使用 **pthread_create** 创建线程的简单示例：

```c++
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void* threadfunc(void* arg)
{
  while(1)
  {
    //睡眠1秒
    sleep(1);

    printf("I am New Thread!\n");
  }
}

int main()
{
  pthread_t threadid;
  pthread_create(&threadid, NULL, threadfunc, NULL);

  while (1)
  {
    sleep(1);
    //权宜之计，让主线程不要提前退出
  }

  return 0;
}
```

上述代码片段利用 **pthread_create** 函数在主线程创建了一个工作线程，线程函数为 **threadfunc**。

#### Windows 线程创建

Windows 上创建线程使用 **CreateThread**，其函数签名如下：

```c++
HANDLE CreateThread(
  LPSECURITY_ATTRIBUTES   lpThreadAttributes,
  SIZE_T                  dwStackSize,
  LPTHREAD_START_ROUTINE  lpStartAddress,
  LPVOID                  lpParameter,
  DWORD                   dwCreationFlags,
  LPDWORD                 lpThreadId
);
```

- 参数 **lpThreadAttributes**，是线程的安全属性，一般设置为 NULL。
- 参数 **dwStackSize**，线程的栈空间大小，单位为字节数，一般指定为 0，表示使用默认大小。
- 参数 **lpStartAddress**，为线程函数，其类型是 **LPTHREAD_START_ROUTINE**，这是一个函数指针类型，其定义如下：

```c++
typedef DWORD ( __stdcall *LPTHREAD_START_ROUTINE )(LPVOID lpThreadParameter);
```

> 需要注意的是，Windows 上创建的线程的线程函数其调用方式必须是**__stdcall**，如果将如下函数设置成线程函数是不行的：

```c++
DWORD threadfunc(LPVOID lpThreadParameter);
```

如上文所说，如果不指定函数的调用方式，使用默认调用方式 **__cdecl**，而这里的线程函数要求是 **__stdcall**，因此必须在函数名前面显式指定函数调用方式为 **__stdcall**。

```c++
DWORD __stdcall threadfunc(LPVOID lpThreadParameter);
```

Windows 上的宏 **WINAPI** 和 **CALLBACK** 这两个宏的定义都是 **__stdcall**。因为在项目中看到的线程函数的签名大多写成如下两种形式的一种：

```c++
//写法1
DWORD WINAPI threadfunc(LPVOID lpThreadParameter);
//写法2
DWORD CALLBACK threadfunc(LPVOID lpThreadParameter);
```

- 参数 **lpParameter** 为传给线程函数的参数，和 Linux 下的 **pthread_create** 函数的 **arg** 一样，这实际上也是一个 **void*** 类型（LPVOID 类型是用 typedef 包装后的 void* 类型）。

```c++
typedef void* LPVOID;
```

- 参数 **dwCreationFlags**，是一个 32 位无符号整型（DWORD），一般设置为 0，表示创建好线程后立即启动线程的运行；有一些特殊的情况，我们不希望创建线程后立即开始执行，可以将这个值设置为 **4**（对应 Windows 定义的宏 **CREATE_SUSPENDED**），后面在需要的时候，再使用 **ResumeThread** 这个 API 让线程运行起来。
- 参数 **lpThreadId**，为线程创建成功返回的线程 ID，这也是一个 32 位无符号整数（DWORD）的指针（LPDWORD）。
- 返回值：Windows 上使用句柄（HANDLE 类型）来管理线程对象，句柄本质上是内核句柄表中的索引值。如果成功创建线程，则返回该线程的句柄；如果创建失败，则返回 NULL。

下面的代码片段，演示了 Windows 上如何创建一个线程：

```c++
#include <Windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID lpParameters)
{
    while (true)
    {
        //睡眠 1 秒，Windows 上的 Sleep 函数参数事件单位为毫秒
        Sleep(1000);

        printf("I am New Thread!\n");
    }
}

int main()
{
    DWORD dwThreadID;
    HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &dwThreadID);
    if (hThread == NULL)
    {
        printf("Failed to CreateThread.\n");
    }

    while (true)
    {
        Sleep(1000);
        //权宜之计，让主线程不要提前退出
    }

    return 0;
}
```

上述代码片段利用 **CreateThread** 函数在主线程创建了一个工作线程，线程函数为 **ThreadProc**，线程函数名 **ThreadProc** 符合 Windows 程序设计风格。

#### Windows CRT 提供的线程创建函数

这里的 CRT，指的是 **C** **R**un**t**ime（C 运行时），通俗地说就是 C 函数库。在 Windows 操作系统上，微软实现的 C 库也提供了一套用于创建线程的函数（当然这个函数底层还是调用相应的操作系统平台的线程创建 API）。**在实际项目开发中推荐使用这个函数来创建线程而不是使用 CreateThread 函数。**

Windows C 库创建线程常用的函数是 _beginthreadex，声明位于 process.h 头文件中，其签名如下：

```c++
uintptr_t _beginthreadex( 
   void *security,  
   unsigned stack_size,  
   unsigned ( __stdcall *start_address )( void * ),  
   void *arglist,  
   unsigned initflag,  
   unsigned *thrdaddr   
);  
```

函数签名基本上和 Windows 上的 **CreateThread** 函数基本一致，这里就不再赘述了。

以下是使用 **_beginthreadex** 创建线程的一个例子：

```c++
#include <process.h>
//#include <Windows.h>
#include <stdio.h>

unsigned int __stdcall threadfun(void* args)
{
    while (true)
    {        
        //Sleep(1000);

        printf("I am New Thread!\n");
    }
}

int main(int argc, char* argv[])
{
    unsigned int threadid;
    _beginthreadex(0, 0, threadfun, 0, 0, &threadid);

    while (true)
    {
        //Sleep(1000);
        //权宜之计，让主线程不要提前退出
    }

    return 0;
}
```

上述代码片段利用 **_beginthreadex** 函数在主线程创建了一个工作线程，线程函数为 **threadfun**。

#### C++ 11 提供的 std::thread 类

无论是 Linux 还是 Windows 上创建线程的 API，都有一个非常不方便的地方，**就是线程函数的签名必须是固定的格式（参数个数和类型、返回值类型都有要求）。**C++11 新标准引入了一个新的类 **std::thread**（需要包含头文件 <thread>），使用这个类的可以将任何签名形式的函数作为线程函数。以下代码分别创建两个线程，线程函数签名不一样：

```c++
#include <stdio.h>
#include <thread>

void threadproc1()
{
    while (true)
    {
        printf("I am New Thread 1!\n");
    }
}

void threadproc2(int a, int b)
{
    while (true)
    {
        printf("I am New Thread 2!\n");
    }
}

int main()
{
    //创建线程t1
    std::thread t1(threadproc1);
    //创建线程t2
    std::thread t2(threadproc2, 1, 2);

    while (true)
    {
        //Sleep(1000);
        //权宜之计，让主线程不要提前退出
    }

    return 0;
}
```

当然， **std::thread** 在使用上容易犯一个错误，即在 **std::thread** 对象在线程函数运行期间必须是有效的。什么意思呢？我们来看一个例子：

```c++
#include <stdio.h>
#include <thread>

void threadproc()
{
    while (true)
    {
        printf("I am New Thread!\n");
    }
}

void func()
{
    std::thread t(threadproc);
}

int main()
{
    func();

    while (true)
    {
        //Sleep(1000);
        //权宜之计，让主线程不要提前退出
    }

    return 0;
}
```

上述代码在 **func** 中创建了一个线程，然后又在 **main** 函数中调用 **func** 方法，乍一看好像代码没什么问题，但是在实际运行时程序会崩溃。崩溃的原因是，当 **func** 函数调用结束后，**func** 中局部变量 **t** （**线程对象**）被销毁了，而此时**线程函数**仍然在运行。这就是我所说的，使用 **std::thread** 类时，必须保证线程函数运行期间，其线程对象有效。<u>这是一个很容易犯的错误，解决这个问题的方法是，**std::thread** 对象提供了一个 **detach** 方法，这个方法让**线程对象**与**线程函数**脱离关系，这样即使**线程对象**被销毁，仍然不影响**线程函数**的运行。</u>我们只需要在 **func** 函数中调用 **detach** 方法即可，代码如下：

```c++
//其他代码保持不变，这里就不重复贴出来了
void func()
{
    std::thread t(threadproc);
    t.detach();
}
```

然而，在实际编码中，这也是一个不推荐的做法，原因是我们需要使用**线程对象**去控制和管理线程的运行和生命周期。所以，我们的代码应该尽量保证**线程对象**在线程运行期间有效，而不是单纯地调用 **detach** 方法使线程对象与线程函数的运行分离。

### 总结

本讲介绍了 Linux 和 Windows 平台的线程创建基础 API，同时也介绍了 CRT 和 C++ 11 语言标准提供的创建线程的方法（它们可以方便我们写跨平台代码），但是读者一定要明白 CRT 和 C++ 11 创建线程的函数其实现是在对应的操作系统平台调用我们介绍的线程创建函数。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)

### 分享交流

我们为本专栏**付费读者**创建了微信交流群，以方便更有针对性地讨论专栏相关的问题。入群方式请添加 GitChat 小助手泰勒的微信号：GitChatty5（或扫描以下二维码），然后给小助手发「222」消息，即可拉你进群~

![img](image/FtkDbtI-hx5hlJERoW0MGan1I8Ax)

## 4.排查 Linux 进程 CPU 使用率过高问题

在实际开发中，有时候由于我们的程序逻辑不当问题，会导致某个线程**空转**（如无限空循环），进而引起该进程占用 CPU 使用率过高。这不仅会造成我们的系统卡顿，也是对 CPU 资源的一种浪费。那如何定位和排查引起 CPU 使用率过高的线程呢？

在 Linux 下我们可以综合使用 pstack 和 top 命令来排查此类问题。我们先来介绍一下 **pstack** 命令的使用方法。

### pstack 命令

Linux 系统中可以通过 **pstack** 来命令查看一个进程的线程数量和每个线程的调用堆栈情况。

```
pstack pid
```

**pid** 设置为要查看的进程的 id 即可。

> pstack 命令是 gdb 调试器提供的，如果读者在实际使用时提示找到该命令，可以安装一下 gdb 即可。

以我机器上 nginx 的 worker 进程为例，首先使用 **ps** 命令查看下 nginx 进程 id，然后使用 **pstack** 命令即可查看该进程每个线程的调用堆栈（我这里演示的 nginx 只有一个线程，如果有多个线程，会显示每个线程的调用堆栈）：

```
[root@iZ238vnojlyZ ~]# ps -ef | grep nginx
root      2150     1  0 May22 ?        00:00:00 nginx: master process /usr/sbin/nginx -c /etc/nginx/nginx.conf
nginx     2151  2150  0 May22 ?        00:00:07 nginx: worker process
root     16621 16541  0 18:53 pts/0    00:00:00 grep --color=auto nginx
[root@iZ238vnojlyZ ~]# pstack 2151
#0  0x00007f70a61ca2a3 in __epoll_wait_nocancel () from /lib64/libc.so.6
#1  0x0000000000437313 in ngx_epoll_process_events ()
#2  0x000000000042efc3 in ngx_process_events_and_timers ()
#3  0x0000000000435681 in ngx_worker_process_cycle ()
#4  0x0000000000434104 in ngx_spawn_process ()
#5  0x0000000000435854 in ngx_start_worker_processes ()
#6  0x000000000043631b in ngx_master_process_cycle ()
#7  0x0000000000412229 in main ()
```

上述输出即使用 pstack 命令查看进程 2151 的各个线程调用堆栈。

> 注意：**pstack** 命令查看的程序必须携带调试符号，且你所使用的用户必须具有相应的查看权限。

### 如何排查 Linux 进程 CPU 使用率过高问题

在了解了 pstack 命令的用法之后，我们来看一个具体的例子。

使用 top 命令发现机器上有一个叫 qmarket 的进程 CPU 使用率非常高，如下图所示：

![enter image description here](image/ed523b60-ce47-11e9-bb7f-bd5875ea71a6)

上图中进程 ID 为 **4427** 的 qmarket 进程占用 CPU 使用率达到 **22.8%**。我们使用 **top -H** 命令再次输出下系统的“进程”列表。

> top 命令的 -H 选项的作用是显示每个一个进程的各个线程运行状态（线程模式）。

我们来看下执行结果：

![enter image description here](image/3b402ee0-ce48-11e9-bdf7-7924fedc9f4e)

如上图所示，top 命令第一栏虽然输出还叫 PID，但此时显示的实际是每个线程的线程 ID。可以发现 qmarket 程序的线程号为 **4429**、**4430**、**4431**、**4432**、**4433**、**4434**、**4445** 这几个线程占用 CPU 使用率较高。那么这几个线程到底做了什么导致 CPU 使用率高呢？我们使用 **pstack 4427** 来看一下这几个线程（**4427** 是 qmarket 的进程 ID）。

```
[root@js-dev2 ~]# pstack 4427
Thread 9 (Thread 0x7f315cb39700 (LWP 4428)):
#0  0x00007f315db3d965 in pthread_cond_wait@@GLIBC_2.3.2 () from /lib64/libpthread.so.0
#1  0x00007f315d8dc82c in std::condition_variable::wait(std::unique_lock<std::mutex>&) () from /lib64/libstdc++.so.6
#2  0x0000000000467a89 in CAsyncLog::WriteThreadProc () at ../../sourcebase/utility/AsyncLog.cpp:300
#3  0x0000000000469a0f in std::_Bind_simple<void (*())()>::_M_invoke<>(std::_Index_tuple<>) (this=0xddeb60) at /usr/include/c++/4.8.2/functional:1732
#4  0x0000000000469969 in std::_Bind_simple<void (*())()>::operator()() (this=0xddeb60) at /usr/include/c++/4.8.2/functional:1720
#5  0x0000000000469902 in std::thread::_Impl<std::_Bind_simple<void (*())()> >::_M_run() (this=0xddeb48) at /usr/include/c++/4.8.2/thread:115
#6  0x00007f315d8e0070 in ?? () from /lib64/libstdc++.so.6
#7  0x00007f315db39dd5 in start_thread () from /lib64/libpthread.so.0
#8  0x00007f315d043ead in clone () from /lib64/libc.so.6
Thread 8 (Thread 0x7f3157fff700 (LWP 4429)):
#0  0x00007f315d00ae2d in nanosleep () from /lib64/libc.so.6
#1  0x00007f315d03b704 in usleep () from /lib64/libc.so.6
#2  0x000000000043ed67 in CThread::SleepMs (this=0x7ffc5eed32e0, nMilliseconds=1000) at ../../sourcebase/event/Thread.cpp:106
#3  0x0000000000441f82 in CEventDispatcher::Run (this=0x7ffc5eed32e0) at ../../sourcebase/event/EventDispatcher.cpp:63
#4  0x000000000043eb33 in CThread::_ThreadEntry (pParam=0x7ffc5eed32e0) at ../../sourcebase/event/Thread.cpp:26
#5  0x00007f315db39dd5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f315d043ead in clone () from /lib64/libc.so.6
Thread 7 (Thread 0x7f31573fd700 (LWP 4430)):
#0  0x00007f315d00ae2d in nanosleep () from /lib64/libc.so.6
#1  0x00007f315d03b704 in usleep () from /lib64/libc.so.6
#2  0x000000000043ed67 in CThread::SleepMs (this=0x7f3150022390, nMilliseconds=1000) at ../../sourcebase/event/Thread.cpp:106
#3  0x0000000000441f82 in CEventDispatcher::Run (this=0x7f3150022390) at ../../sourcebase/event/EventDispatcher.cpp:63
#4  0x000000000043eb33 in CThread::_ThreadEntry (pParam=0x7f3150022390) at ../../sourcebase/event/Thread.cpp:26
#5  0x00007f315db39dd5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f315d043ead in clone () from /lib64/libc.so.6
Thread 6 (Thread 0x7f3156bfc700 (LWP 4431)):
#0  0x00007f315d00ae2d in nanosleep () from /lib64/libc.so.6
#1  0x00007f315d03b704 in usleep () from /lib64/libc.so.6
#2  0x000000000043ed67 in CThread::SleepMs (this=0x7f3150047890, nMilliseconds=1000) at ../../sourcebase/event/Thread.cpp:106
#3  0x0000000000441f82 in CEventDispatcher::Run (this=0x7f3150047890) at ../../sourcebase/event/EventDispatcher.cpp:63
#4  0x000000000043eb33 in CThread::_ThreadEntry (pParam=0x7f3150047890) at ../../sourcebase/event/Thread.cpp:26
#5  0x00007f315db39dd5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f315d043ead in clone () from /lib64/libc.so.6
Thread 5 (Thread 0x7f31563fb700 (LWP 4432)):
#0  0x00007f315d00ae2d in nanosleep () from /lib64/libc.so.6
#1  0x00007f315d03b704 in usleep () from /lib64/libc.so.6
#2  0x000000000043ed67 in CThread::SleepMs (this=0x7f3148041fd8, nMilliseconds=1000) at ../../sourcebase/event/Thread.cpp:106
#3  0x0000000000441f82 in CEventDispatcher::Run (this=0x7f3148041fd8) at ../../sourcebase/event/EventDispatcher.cpp:63
#4  0x000000000043eb33 in CThread::_ThreadEntry (pParam=0x7f3148041fd8) at ../../sourcebase/event/Thread.cpp:26
#5  0x00007f315db39dd5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f315d043ead in clone () from /lib64/libc.so.6
Thread 4 (Thread 0x7f3155bfa700 (LWP 4433)):
#0  0x00007f315d00ae2d in nanosleep () from /lib64/libc.so.6
#1  0x00007f315d03b704 in usleep () from /lib64/libc.so.6
#2  0x000000000043ed67 in CThread::SleepMs (this=0x7f3148052620, nMilliseconds=1000) at ../../sourcebase/event/Thread.cpp:106
#3  0x0000000000441f82 in CEventDispatcher::Run (this=0x7f3148052620) at ../../sourcebase/event/EventDispatcher.cpp:63
#4  0x000000000043eb33 in CThread::_ThreadEntry (pParam=0x7f3148052620) at ../../sourcebase/event/Thread.cpp:26
#5  0x00007f315db39dd5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f315d043ead in clone () from /lib64/libc.so.6
Thread 3 (Thread 0x7f31553f9700 (LWP 4434)):
#0  0x00007f315d00ae2d in nanosleep () from /lib64/libc.so.6
#1  0x00007f315d03b704 in usleep () from /lib64/libc.so.6
#2  0x000000000043ed67 in CThread::SleepMs (this=0x7f3148062ee0, nMilliseconds=1000) at ../../sourcebase/event/Thread.cpp:106
#3  0x0000000000441f82 in CEventDispatcher::Run (this=0x7f3148062ee0) at ../../sourcebase/event/EventDispatcher.cpp:63
#4  0x000000000043eb33 in CThread::_ThreadEntry (pParam=0x7f3148062ee0) at ../../sourcebase/event/Thread.cpp:26
#5  0x00007f315db39dd5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f315d043ead in clone () from /lib64/libc.so.6
Thread 2 (Thread 0x7f3154bf8700 (LWP 4445)):
#0  0x00007f315d00ae2d in nanosleep () from /lib64/libc.so.6
#1  0x00007f315d03b704 in usleep () from /lib64/libc.so.6
#2  0x000000000043ed67 in CThread::SleepMs (this=0x7f3150001b00, nMilliseconds=1000) at ../../sourcebase/event/Thread.cpp:106
#3  0x0000000000441f82 in CEventDispatcher::Run (this=0x7f3150001b00) at ../../sourcebase/event/EventDispatcher.cpp:63
#4  0x000000000043eb33 in CThread::_ThreadEntry (pParam=0x7f3150001b00) at ../../sourcebase/event/Thread.cpp:26
#5  0x00007f315db39dd5 in start_thread () from /lib64/libpthread.so.0
#6  0x00007f315d043ead in clone () from /lib64/libc.so.6
Thread 1 (Thread 0x7f315f2ca3c0 (LWP 4427)):
#0  0x00007f315db3af47 in pthread_join () from /lib64/libpthread.so.0
#1  0x000000000043edc7 in CThread::Join (this=0x7ffc5eed32e0) at ../../sourcebase/event/Thread.cpp:130
#2  0x000000000040cc61 in main (argc=1, argv=0x7ffc5eed3668) at ../../sourceapp/qmarket/qmarket.cpp:309
```

在 pstack 输出的各个线程中，只要逐一对照我们的程序源码来梳理下该线程中是否有大多数时间都处于空转的逻辑，然后修改和优化这些逻辑就可以解决 CPU 使用率过高的问题了，一般情况下，不工作的线程应尽量使用锁对象让其挂起，而不是空转，这样可以提高系统资源利用率。关于线程各种锁对象，下文中将详细介绍。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 5.线程 ID 的用途及原理

前面介绍了如何创建一个线程，本讲我们来介绍一下线程 ID 的内容，线程 ID 一般是用于标识一个线程的整形数值。

### 线程 ID

一个线程创建成功以后，我们可以拿到一个线程 ID。我们可以使用线程 ID 来标识和区分线程，例如在日志文件中，把打印日志的所在的线程 ID 也一起打印出来，我们通过线程 ID 来确定日志内容是不是属于同一个线程上下文。创建线程时，上文也介绍了可以通过 **pthread_create** 函数的第一个参数 **thread** （linux平台）和 **CreateThread** 函数的最后一个参数 **lpThreadId** （Windows平台）得到线程的 ID。大多数时候，我们需要在当前调用线程中获取当前线程的 ID，在 Linux 平台上可以使用 **pthread_self** 函数（还有另外两种方式，下问介绍），在 Windows 平台上可以使用 **GetCurrentThreadID** 函数获取，这两个函数的签名分别如下：

```c++
pthread_t pthread_self(void);

DWORD GetCurrentThreadId();
```

这两个函数比较简单，这里就不介绍了，无论是 **pthread_t** 还是 **DWORD** 类型，都是一个 32 位无符号整型值。

在 Windows 7 操作系统中可以在任务管理器中查看某个进程的线程数量：

![enter image description here](image/07273ce0-ce23-11e9-8bf7-f7666cc59bcf)

上图中标红的一栏即每个进程的线程数量，例如对于 vmware-tray.exe 进程一共有三个线程。如果读者打开任务管理器没有看到**线程数**这一列，可以点击任务管理器的【**查看**】- 【**选择列**】菜单，在弹出的对话框中勾选**线程数**即可显示出**线程数**这一列。

### inux 系统线程 ID 的本质

Linux 系统中有三种方式可以获取一个线程的 ID。

**方法一**

调用 **pthread_create** 函数时，第一个参数在函数调用成功后可以得到线程 ID：

```c++
#include <pthread.h>

pthread_t tid;
pthread_create(&tid, NULL, thread_proc, NULL);
```

**pthread_create** 函数我们在前面篇幅中已经介绍过了。

**方法二**

在需要获取 ID 的线程中调用 **pthread_self()** 函数获取。

```c++
#include <pthread.h>

pthread_t tid = pthread_self();
```

**方法三**

通过系统调用获取线程 ID

```c++
#include <sys/syscall.h>
#include <unistd.h>

int tid = syscall(SYS_gettid);
```

**方法一**和**方法二**获取的线程 ID 结果是一样的，这是一个 **pthread_t**，输出时本质上是一块内存空间地址，示意图如下：

![enter image description here](image/6307bf10-ce48-11e9-bdf7-7924fedc9f4e)

由于不同的进程可能有同样地址的内存块，因此**方法一**和**方法二**获取的线程 ID 可能不是全系统唯一的，一般是一个很大的数字（内存地址）。而**方法三**获取的线程 ID 是系统范围内全局唯一的，一般是一个不会太大的整数，这个数字也是就是所谓的 LWP （Light Weight Process，轻量级进程，早期的 Linux 系统的线程是通过进程来实现的，这种线程被称为轻量级线程）的 ID。

我们来看一段具体的代码：

```c++
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void* thread_proc(void* arg)
{
    pthread_t* tid1 = (pthread_t*)arg;
    int tid2 = syscall(SYS_gettid);
    pthread_t tid3 = pthread_self();

    while(true)
    {
        printf("tid1: %ld, tid2: %ld, tid3: %ld\n", *tid1, tid2, tid3);
        sleep(1);
    }

}

int main()
{    
    pthread_t tid;
    pthread_create(&tid, NULL, thread_proc, &tid);

    pthread_join(tid, NULL);

    return 0;
}
```

上述代码在新开的线程中使用上面介绍的三种方式获取线程 ID，并打印出来，输出结果如下：

```
tid1: 140185007511296, tid2: 60837, tid3: 140185007511296
```

**tid2** 即 LWP 的 ID，而 **tid1** 和 **tid3** 是一个内存地址，转换成 16 进制即：

```
0x7F7F5D935700
```

这与我们用 pstack 命令看到的线程 ID 是一样的：

```
[root@localhost ~]# ps -efL | grep linuxtid
root     60712 60363 60712  0    2 13:25 pts/1    00:00:00 ./linuxtid
root     60712 60363 60713  0    2 13:25 pts/1    00:00:00 ./linuxtid
root     60720 60364 60720  0    1 13:25 pts/3    00:00:00 grep --color=auto linuxtid
[root@localhost ~]# pstack 60712
Thread 2 (Thread 0x7fd897a50700 (LWP 60713)):
#0  0x00007fd897b15e2d in nanosleep () from /lib64/libc.so.6
#1  0x00007fd897b15cc4 in sleep () from /lib64/libc.so.6
#2  0x0000000000400746 in thread_proc (arg=0x7fff390921c8) at linuxtid.cpp:15
#3  0x00007fd898644dd5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007fd897b4eead in clone () from /lib64/libc.so.6
Thread 1 (Thread 0x7fd898a6e740 (LWP 60712)):
#0  0x00007fd898645f47 in pthread_join () from /lib64/libpthread.so.0
#1  0x000000000040077e in main () at linuxtid.cpp:25
[root@localhost ~]# ps -ef | grep linuxtid
root     60838 60363  0 14:27 pts/1    00:00:00 ./linuxtid
root     60846 60364  0 14:28 pts/3    00:00:00 grep --color=auto linuxtid
[root@localhost ~]# pstack 60838
Thread 2 (Thread 0x7f7f5d935700 (LWP 60839)):
#0  0x00007f7f5d9fae2d in nanosleep () from /lib64/libc.so.6
#1  0x00007f7f5d9facc4 in sleep () from /lib64/libc.so.6
#2  0x0000000000400746 in thread_proc (arg=0x7fff0523ae68) at linuxtid.cpp:15
#3  0x00007f7f5e529dd5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f7f5da33ead in clone () from /lib64/libc.so.6
Thread 1 (Thread 0x7f7f5e953740 (LWP 60838)):
#0  0x00007f7f5e52af47 in pthread_join () from /lib64/libpthread.so.0
#1  0x000000000040077e in main () at linuxtid.cpp:25
```

### C++11 的获取当前线程 ID 的方法

C++11 的线程库可以使用 **std::this_thread**类的 **get_id** 获取当前线程的 id，这是一个类静态方法。

当然也可以使用 **std::thread** 的 **get_id** 获取指定线程的 id，这是一个类实例方法。

<u>但是 **get_id** 方法返回的是一个包装类型的 **std::thread::id** 对象，不可以直接强转成整型，也没有提供任何转换成整型的接口。所以，我们一般使用 **std::cout** 这样的输出流来输出，或者先转换为 **std::ostringstream** 对象，再转换成字符串类型，然后把字符串类型转换成我们需要的整型。</u>这一点，个人觉得算是 C++11 线程库获取线程 id 一个不太方便的地方。

```c++
//test_cpp11_thread_id.cpp
#include <thread>
#include <iostream>
#include <sstream>

void worker_thread_func()
{
    while (true)
    {

    }
}

int main()
{
    std::thread t(worker_thread_func);
    //获取线程 t 的 ID
    std::thread::id worker_thread_id = t.get_id();
    std::cout << "worker thread id: " << worker_thread_id << std::endl;

    //获取主线程的线程 ID
    std::thread::id main_thread_id = std::this_thread::get_id();
    //先将 std::thread::id 转换成 std::ostringstream 对象
    std::ostringstream oss;
    oss << main_thread_id;
    //再将 std::ostringstream 对象转换成std::string
    std::string str = oss.str();
    std::cout << "main thread id: " << str << std::endl;
    //最后将 std::string 转换成整型值
    unsigned long long threadid = std::stoull(str);
    std::cout << "main thread id: " << threadid << std::endl;

    while (true)
    {
        //权宜之计，让主线程不要提前退出
    }

    return 0;
}
```

在 Linux x64 系统上编译并运行程序，输出结果如下：

```
[root@myaliyun codes]# g++ -g -o test_cpp11_thread_id test_cpp11_thread_id.cpp -lpthread
[root@myaliyun codes]# ./test_cpp11_thread_id 
worker thread id: 139875808245504
main thread id: 139875825641280
main thread id: 139875825641280
```

编译成 Windows x86 程序运行结果如下：

![img](image/20e65af0-c8fd-11ea-846e-931488aef7b9)

### 总结

线程 ID 在实际编码中是一个很重要的上下文信息，因此熟练地获取某个线程的线程 ID，是多线程编程的基本功之一。

这里给读者留一个小问题：

> 线程 ID 是系统唯一的吗？答案可以在对应的课程微信群中获得。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 6.如何等待线程结束

前面课程介绍了创建线程，既然线程可以创建，线程也应该可以结束。那如何等待一个线程结束呢？

实际项目开发中，我们常常会有这样一种需求，即一个线程需要等待另外一个线程执行完任务退出后再继续执行。这在 Linux 和 Windows 操作系统中都提供了相应的操作系统 API，我们来分别介绍一下。

### Linux 下等待线程结束

Linux 线程库提供了 **pthread_join** 函数，用来等待某线程的退出并接收它的返回值。这种操作被称为**连接**（joining），**pthread_join** 函数签名如下：

```c++
int pthread_join(pthread_t thread, void** retval);
```

- 参数 **thread**，需要等待的线程 id。
- 参数 **retval**，输出参数，用于接收等待退出的线程的退出码（**Exit Code**），线程退出码可以通过调用 **pthread_exit** 退出线程时指定，也可以在线程函数中通过 **return** 语句返回。

```c++
#include <pthread.h>

void pthread_exit(void* value_ptr);&nbsp;
```

参数 **value_ptr** 的值可以在 **pthread_join** 中拿到，没有可以设置为 NULL。

**pthread_join 函数等待其他线程退出期间会挂起等待的线程**，<u>*被挂起的线程不会消耗宝贵任何 CPU 时间片。直到目标线程退出后，等待的线程会被唤醒。*</u>

我们通过一个实例来演示一下这个函数的使用方法，实例功能如下：

程序启动时，开启一个工作线程，工作线程将当前系统时间写入文件中后退出，主线程等待工作线程退出后，从文件中读取出时间并显示在屏幕上。代码如下：

```c++
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define TIME_FILENAME "time.txt"

void* fileThreadFunc(void* arg)
{
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char timeStr[32] = {0};
    snprintf(timeStr, 32, "%04d/%02d/%02d %02d:%02d:%02d", 
             t->tm_year+1900,
             t->tm_mon+1,
             t->tm_mday,
             t->tm_hour,
             t->tm_min,
             t->tm_sec);
    //文件不存在，则创建；存在，则覆盖
    FILE* fp = fopen(TIME_FILENAME, "w");
    if (fp == NULL)
    {
      printf("Failed to create time.txt.\n");
        return;
    }

    size_t sizeToWrite = strlen(timeStr) + 1;
    size_t ret = fwrite(timeStr, 1, sizeToWrite, fp);
    if (ret != sizeToWrite)
    {
        printf("Write file error.\n");
    }

    fclose(fp);
}

int main()
{
    pthread_t fileThreadID;
    int ret = pthread_create(&fileThreadID, NULL, fileThreadFunc, NULL);
    if (ret != 0)
    {
        printf("Failed to create fileThread.\n");
        return -1;
    }

    int* retval;
    pthread_join(fileThreadID, (void**)&retval);

    //使用r选项，要求文件必须存在
    FILE* fp = fopen(TIME_FILENAME, "r");
    if (fp == NULL)
    {
        printf("open file error.\n");
        return -2;
    }

    char buf[32] = {0};
    int sizeRead = fread(buf, 1, 32, fp);
    if (sizeRead == 0)
    {
      printf("read file error.\n");
      return -3;
    }

    printf("Current Time is: %s.\n", buf);

    return 0;
}
```

程序执行结果如下：

```
[root@localhost threadtest]# ./test
Current Time is: 2018/09/24 21:06:01.
```

### Windows 下等待线程结束

Windows 下使用 API **WaitForSingleObject** 或 **WaitForMultipleObjects** 函数，$\color{red} {前者用于等待一个线程结束，后者可以同时等待多个线程结束。}$这是两个非常重要的函数，$\color{red} {它们的作用不仅可以用于等待线程退出，还可以用于等待其他线程同步对象}$，本文后面的将详细介绍这两个函数。与 Linux 的 **pthread_join** 函数不同，Windows 的**WaitForSingleObject** 函数提供了可选择等待时间的精细控制。

这里我们仅演示等待线程退出。

- 参数 **hHandle** 是需要等待的对象的句柄，等待线程退出，传入线程句柄。
- 参数 **dwMilliseconds** 是需要等待的毫秒数，如果使用 **INFINITE** 宏，则表示无限等待下去。
- **返回值**：该函数的返回值有点复杂，我们后面文章具体介绍。当 **dwMilliseconds** 参数使用 **INFINITE** 值，该函数会挂起当前等待线程，直到等待的线程退出后，等待的线程才会被唤醒，**WaitForSingleObject** 后的程序执行流继续执行。

我们将上面的 Linux 示例代码改写成 Windows 版本的：

```c++
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define TIME_FILENAME "time.txt"

DWORD WINAPI FileThreadFunc(LPVOID lpParameters)
{
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char timeStr[32] = { 0 };
    sprintf_s(timeStr, 32, "%04d/%02d/%02d %02d:%02d:%02d",
              t->tm_year + 1900,
              t->tm_mon + 1,
              t->tm_mday,
              t->tm_hour,
              t->tm_min,
              t->tm_sec);
    //文件不存在，则创建；存在，则覆盖
    FILE* fp = fopen(TIME_FILENAME, "w");
    if (fp == NULL)
    {
        printf("Failed to create time.txt.\n");
        return 1;
    }

    size_t sizeToWrite = strlen(timeStr) + 1;
    size_t ret = fwrite(timeStr, 1, sizeToWrite, fp);
    if (ret != sizeToWrite)
    {
        printf("Write file error.\n");
    }

    fclose(fp);

    return 2;
}


int main()
{
    DWORD dwFileThreadID;
    HANDLE hFileThread = CreateThread(NULL, 0, FileThreadFunc, NULL, 0, 
                                      &dwFileThreadID);
    if (hFileThread == NULL)
    {
        printf("Failed to create fileThread.\n");
        return -1;
    }

    //无限等待，直到文件线程退出，否则程序将一直挂起
    WaitForSingleObject(hFileThread, INFINITE);

    //使用r选项，要求文件必须存在
    FILE* fp = fopen(TIME_FILENAME, "r");
    if (fp == NULL)
    {
        printf("open file error.\n");
        return -2;
    }

    char buf[32] = { 0 };
    int sizeRead = fread(buf, 1, 32, fp);
    if (sizeRead == 0)
    {
        printf("read file error.\n");
        return -3;
    }

    printf("Current Time is: %s.\n", buf);

    return 0;
}
```

与 Linux 版本一样，我们得到类似的程序执行结果：

![enter image description here](image/2ad72550-ce4c-11e9-9f77-155b7642027f)

### C++ 11 提供的等待线程结果函数

可以想到，C++ 11 的 **std::thread** 既然统一了 Linux 和 Windows 的线程创建函数，那么它应该也提供等待线程退出的接口，确实如此，**std::thread** 的 **join** 方法就是用来等待线程退出的函数。<u>*当然使用这个函数时，必须保证该线程还处于运行中状态，也就是说等待的线程必须是可以 “**join**”的，如果需要等待的线程已经退出，此时调用**join** 方法，程序会产生崩溃。*</u>因此，C++ 11 的线程库同时提供了一个 **joinable** 方法来判断某个线程是否可以 join，如果不确定线程是否可以“join”，可以先调用 **joinable** 函数判断一下是否需要等待。

还是以上面的例子为例，改写成 C++11 的代码：

```c++
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <thread>

#define TIME_FILENAME "time.txt"

void FileThreadFunc()
{
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char timeStr[32] = { 0 };
    sprintf_s(timeStr, 32, "%04d/%02d/%02d %02d:%02d:%02d",
              t->tm_year + 1900,
              t->tm_mon + 1,
              t->tm_mday,
              t->tm_hour,
              t->tm_min,
              t->tm_sec);
    //文件不存在，则创建；存在，则覆盖
    FILE* fp = fopen(TIME_FILENAME, "w");
    if (fp == NULL)
    {
        printf("Failed to create time.txt.\n");
        return;
    }

    size_t sizeToWrite = strlen(timeStr) + 1;
    size_t ret = fwrite(timeStr, 1, sizeToWrite, fp);
    if (ret != sizeToWrite)
    {
        printf("Write file error.\n");
    }

    fclose(fp);
}

int main()
{
    std::thread t(FileThreadFunc);
    if (t.joinable())
        t.join();

    //使用 r 选项，要求文件必须存在
    FILE* fp = fopen(TIME_FILENAME, "r");
    if (fp == NULL)
    {
        printf("open file error.\n");
        return -2;
    }

    char buf[32] = { 0 };
    int sizeRead = fread(buf, 1, 32, fp);
    if (sizeRead == 0)
    {
        printf("read file error.\n");
        return -3;
    }

    printf("Current Time is: %s.\n", buf);

    return 0;
}
```

### 总结

在 A 线程等待 B 线程结束，相当于 A 线程和 B 线程在该点汇集（或连接），这就是 **join** 函数的语义来源，因此很多其他编程语言也使用 join 一词表示等待线程结束。

**思考题**

C++ 11 的 std::thread 类提供了一个 join() 方法，如果某个线程已经结束，调用其 join() 方法会怎样呢？有没有办法判断一个线程已经结束？ 答案可以在对应的课程微信群中获得。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 7.线程函数传 C++ 类实例指针惯用法

前面的内容介绍了*<u>除了 C++ 11 的线程库提供了的 **std::thread** 类对线程函数签名没有特殊要求外</u>*，$\color{red} {无论是 Linux 还是 Windows 的线程函数的签名都必须是指定的格式，即参数和返回值必须是规定的形式。}$**如果使用 C++ 面向对象的方式对线程函数进行封装，那么线程函数就不能是类的实例方法，即必须是类的静态方法。**那么，为什么不能是类的实例方法呢？<u>*我们以 Linux 的线程函数签名为例：*</u>

```c++
void threadFunc(void* arg);
```

假设，将线程的基本功能封装到一个 **Thread** 类中，部分代码如下：

```c++
class Thread
{
public:
    Thread();
    ~Thread();

    void start();
    void stop();

    void* threadFunc(void* arg);
};
```

由于 **threadFunc** 是一个类实例方法，无论是类的实例方法还是静态方法，C++ 编译器在编译时都会将这些函数“翻译”成全局函数，即去掉类的域限制。对于实例方法，为了保证类方法的正常功能，C++ 编译器在翻译时，会将类的实例对象地址（也就是 this 指针）作为第一个参数传递给该方法，也就是说，翻译后的 **threadFunc** 的签名变成了如下形式（伪代码）：

```c++
void* threadFunc(Thread* this, void* arg);
复制
```

**这样的话，就不符合线程函数签名要求了。因此如果一个线程函数作为类方法，只能是静态方法而不能是实例方法。**

<u>当然，如果是使用 C++ 11 的 **std::thread** 类就没有这个限制，即使类成员函数是类的实例方法也可以</u>，*但是**必须显式地**将线程函数所属的类对象实例指针（在类的内部就是 **this** 指针）作为构造函数参数传递给 **std::thread**，*还是需要传递类的 this 指针，这在本质上是一样的，代码实例如下：

```c++
#include <thread>
#include <memory>
#include <stdio.h>

class Thread
{
public:
    Thread()
    {
    }

    ~Thread()
    {
    }

    void Start()
    {
        m_stopped = false;
        //threadFunc 是类的非静态方法，因此作为线程函数，第一个参数必须传递类实例地址，即 this 指针
        m_spThread.reset(new std::thread(&Thread::threadFunc, this, 8888, 9999));
    }

    void Stop()
    {
        m_stopped = true;
        if (m_spThread)
        {
            if (m_spThread->joinable())
                m_spThread->join();
        }
    }

private:
    void threadFunc(int arg1, int arg2)
    {
        while (!m_stopped)
        {
            printf("Thread function use instance method.\n");
        }      
    }

private:
    std::shared_ptr<std::thread>  m_spThread;
    bool                          m_stopped;
};

int main()
{
    Thread mythread;
    mythread.Start();

    while (true)
    {
        //权宜之计，让主线程不要提前退出
    }

    return 0;
}
```

上述代码中使用了 C++ 11 新增的智能指针 **std::shared_ptr** 类来包裹了一下 new 出来的 **std::thread** 对象，<u>这样我们就不需要自己手动 delete 这个 **std::thread** 对象了。</u>

综上所述，**如果不使用 C++ 11 的语法，那么线程函数只能作为类的静态方法，且函数签名必须按规定的签名格式来。**如果是类的静态方法，那么就没法访问类的实例方法了，为了解决这个问题，在实际开发中往往会在创建线程时将当前对象的地址（**this** 指针）传递给线程函数，然后在线程函数中，将该指针转换成原来的类实例，再通过这个实例就可以访问类的所有方法了。代码示例如下：

**.h** 文件代码如下：

```c++
/**
 * Thread.h
 */
#ifdef WIN32
//#include <windows.h>
typedef HANDLE THREAD_HANDLE ;
#else
//#include <pthread.h>
typedef pthread_t THREAD_HANDLE ;
#endif

/**定义了一个线程对象
*/
class  CThread  
{
public:
    /**构造函数
    */
    CThread();

    /**析构函数
    */
    virtual ~CThread();

    /**创建一个线程
    * @return true:创建成功 false:创建失败
    */
    virtual bool Create();

    /**获得本线程对象存储的线程句柄
    * @return 本线程对象存储的线程句柄线程句柄
    */
    THREAD_HANDLE GetHandle();

    /**线程睡眠 seconds 秒
    * @param seconds 睡眠秒数
    */
    void OSSleep(int nSeconds);

    void SleepMs(int nMilliseconds);

    bool Join();

    bool IsCurrentThread();

    void ExitThread();

private:    
#ifdef WIN32
    static DWORD WINAPI _ThreadEntry(LPVOID pParam);
#else
    static void* _ThreadEntry(void* pParam);
#endif

    /**虚函数，子类可做一些实例化工作
    * @return true:创建成功 false:创建失败
    */
    virtual bool InitInstance();

    /**虚函数，子类清楚实例
    */
    virtual void ExitInstance();

    /**线程开始运行，纯虚函数，子类必须继承实现
    */
    virtual void Run() = 0;

private:
     THREAD_HANDLE  m_hThread;  /**< 线程句柄 */
     DWORD          m_IDThread;

};
```

**.cpp** 文件如下：

```c++
/**
 * Thread.cpp
 */
#include "Thread.h"

#ifdef WIN32
DWORD WINAPI CThread::_ThreadEntry(LPVOID pParam)
#else
void* CThread::_ThreadEntry(void* pParam)
#endif
{
    CThread *pThread = (CThread *)pParam;
    if(pThread->InitInstance())
    {
        pThread->Run();
    }

    pThread->ExitInstance();

    return NULL;
}

CThread::CThread()
{
    m_hThread = (THREAD_HANDLE)0;
    m_IDThread = 0;
}

CThread::~CThread()
{
}

bool CThread::Create()
{
    if (m_hThread != (THREAD_HANDLE)0)
    {
        return true;
    }
    bool ret = true;
#ifdef WIN32
    m_hThread = ::CreateThread(NULL, 0, _ThreadEntry, this, 0, &m_IDThread);
    if(m_hThread==NULL)
    {
        ret = false;
    }
#else
    ret = (::pthread_create(&m_hThread, NULL, &_ThreadEntry, this) == 0);
#endif
    return ret;
}

bool CThread::InitInstance()
{
    return true;
}

void CThread::ExitInstance()
{
}

void CThread::OSSleep(int seconds)
{
#ifdef WIN32
    ::Sleep(seconds*1000);
#else
    ::sleep(seconds);
#endif
}

void CThread::SleepMs(int nMilliseconds)
{
#ifdef WIN32
    ::Sleep(nMilliseconds);
#else
    ::usleep(nMilliseconds);
#endif
}

bool CThread::IsCurrentThread()
{
#ifdef WIN32
    return ::GetCurrentThreadId() == m_IDThread;
#else
    return ::pthread_self() == m_hThread;
#endif
}

bool CThread::Join()
{    
    THREAD_HANDLE hThread = GetHandle();
    if(hThread == (THREAD_HANDLE)0)
    {
        return true;
    }
#ifdef WIN32
    return (WaitForSingleObject(hThread,INFINITE) != 0);
#else
    return (pthread_join(hThread, NULL) == 0);
#endif
}

void CThread::ExitThread()
{
#ifdef WIN32
    ::ExitThread(0);
#else
#endif
}
```

上述代码 **CThread** 类封装了一个线程的常用的操作，使用宏 **WIN32** 来分别实现了 Windows 和 Linux 两个操作系统平台的线程操作。其中 **InitInstance** 和 **ExitInstance** 方法为虚函数，在继承 **CThread** 的子类中可以改写这两个方法，根据实际需要在线程函数正式业务逻辑前后做一些初始化和反初始化工作，而纯虚接口 **Run** 方法必须改写，改写成您的线程实际执行函数。

在线程函数中通过在创建线程时（调用 **CreateThread** 或 **pthread_create** 方法）时，将当前对象的 **this** 指针作为线程的函数的唯一参数传入，这样在线程函数中，可以通过线程函数参数得到对象的指针，通过这个指针就可以自由访问类的实例方法了。**这一技巧非常常用，它广泛地用于各类开源 C++ 项目或者实际的商业 C++ 项目中，希望读者能理解并熟练掌握它**。

**思考题**

正如本节介绍的，由于作为线程函数的类方法必须是类的静态方法，每次要在该方法中访问实例方法和属性必须使用线程函数参数传递一个 this 指针，那么线程函数可以是类的非静态方法吗？ 答案可以在对应的课程微信群中获得。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。


# 第二部分: 多线程同步
## 8.整型变量的原子操作

从本讲开始，我们讨论的主题为线程之间的同步技术。所谓线程同步技术，指的是多个线程同时操作某个资源（从程序的术语来说，这里的资源可能是一个简单的整型变量，也可能是一个复杂的 C++ 对象）。多线程同时操作资源指的是多线程同时对资源的读和写，我们需要采取一些特殊的措施去保护这些资源，以免引起一些资源访问冲突（如死锁）或者得到意料外的结果。

当然，最简单的资源类型应该就是整形变量了。这里给大家说个小故事：在我刚开始参加工作的那年，公司安排我开发一款即时通讯软件（IM，类似于 QQ 聊天软件），在这之前我心里也知道如果多线程操作一个整型值是要加锁的，但是当时为了图代码简便，而且在实际调试的时候，没有加锁的代码也从来没出过问题。于是我就心存侥幸了，觉得对整型值加锁真是多此一举。

我们的软件有类似于 QQ 这种单人聊天功能，每个用户都有一个整型的 userid，问题就出在这里。当时公司的老板和他媳妇儿也使用这款软件，问题来了：有一天早上老板在这个软件上给他媳妇发了一段亲密的话，问题是，由于多线程操作他媳妇儿的 userid 没加锁，最终变成了另外一个人的 userid，而这个 userid 恰好是我的账户。于是老板发给他媳妇儿的聊天内容就被发给我了。我当时看到聊天内容很奇怪，还回复了他一句，并且还带上了我自己的姓名……事情的结果，可想而知了，老板非常尴尬也非常生气……从那以后，老板看我的眼神都是怪怪的。我自知理亏，再也不侥幸了，凡是多线程读写整型变量都养成加锁的好习惯。

### 为什么整型变量赋值操作不是原子的

那么为什么整型变量的操作不是原子性的呢？常见的整型变量操作有如下几种情况：

- 给整型变量赋值一个确定的值，如：

```c++
int a = 1;
```

这条指令操作一般是原子的，因为对应着一条计算机指令，CPU 将立即数 1 搬运到变量 **a** 的内存地址中即可，汇编指令如下：

```
mov dword ptr [a], 2
```

然后这确是最不常见的情形，由于现代编译器一般存在优化策略，如果变量 **a** 的值在编译期间就可以计算出来（例如这里的例子中 **a** 的值就是**1**），那么 **a** 这个变量本身在正式版本的软件中（release 版）就很有可能被编译器优化掉，凡是使用 **a** 的地方，直接使用常量 **1** 来代替。因此实际的执行指令中，这样的指令存在的可能性比较低。

- 变量自身增加或者减去一个值，如：

```c++
a++;
```

从 C/C++ 语法的级别来看，这是一条语句，是原子的；**但是从实际执行的二进制指令来看，也不是原子的，其一般对应三条指令**，1.首先将变量 **a** 对应的内存值搬运到某个寄存器（如 **eax** ）中，2.然后将该寄存器中的值自增 **1**，3.再将该寄存器中的值搬运回 **a** 代表的内存中：

```
mov eax, dword ptr [a]
inc eax
mov dword ptr [a], eax
```

现在假设 **a** 的值是 0，有两个线程，每个线程对变量 **a** 的值递增 **1**，我们预想的结果应该是 **2**，可实际运行的结果可能是 **1**！是不是很奇怪？分析如下：

```c++
int a = 0;

//线程1
void thread_func1()
{
    a ++;
}

//线程2
void thread_func2()
{
    a ++;
}
```

![enter image description here](image/122d6e10-cf19-11e9-9620-ed84a236482a)

我们预想的结果是**线程 1** 和 **线程 2** 的三条指令各自执行，最终 **a** 的值变为 **2**，但是由于操作系统线程调度的不确定性，**线程 1** 执行完指令 ① 和 ② 后，**eax** 寄存器中的值变为 **1**，此时操作系统切换到 **线程2** 执行，执行指令 ③ ④ ⑤，此时 **eax** 的值变为 **1**；接着操作系统切回**线程 1** 继续执行，执行指令 ⑥，得到 **a** 的最终结果 **1**。

- 把一个变量的值赋值给另外一个变量，或者把一个表达式的值赋值给另外一个变量，如

```c++
int a = b;
```

从 C/C++ 语法的级别来看，这也是一条语句，是原子的；但是从实际执行的二进制指令来看，**由于现代计算机 CPU 架构体系的限制，数据不可以直接从内存搬运到另外一块内存，必须借助寄存器中转**，<u>这条语句一般对应两条计算机指令</u>，1.即将变量 **b** 的值搬运到某个寄存器（如 **eax**）中，2.再从该寄存器搬运到变量 **a** 的内存地址：

```
mov eax, dword ptr [b]
mov dword ptr [a], eax 
```

既然是两条指令，那么多个线程在执行这两条指令时，某个线程可能会在第一条指令执行完毕后被剥夺 CPU 时间片，切换到另外一个线程而产生不确定的情况。这和上一种情况类似，就不再详细分析了。

说点题外话，网上很多人强调某些特殊的整型数值类型（如 bool 类型）的操作是原子的，这是由于，某些 CPU 生产商开始有意识地从硬件平台保证这一类操作的原子性，**但这并不是每一种类型的 CPU 架构都支持**，在这一事实成为标准之前，我们在多线程操作整型时还是老老实实使用下文介绍的原子操作或线程同步技术来对这些数据类型进行保护。

### Windows 平台上整型变量的原子操作

整型变量的原子操作是一些非常常用且实用的操作，因此 Windows 操作系统也提供了 API 级别的支持，使用这些 API 可以直接对整型变量进行原子操作，而不用借助专门的锁对象，在 Windows 平台上，它们是 **Interlocked** 系列函数。这里给出 Interlocked 常用的 API 的一个列表：

|           函数名           |                      函数说明                       |
| :------------------------: | :-------------------------------------------------: |
|    InterlockedIncrement    |               将 32 位整型变量自增 1                |
|    InterlockedDecrement    |               将 32 位整型变量自减 1                |
|   InterlockedExchangeAdd   |        将 32 位整型值增加 n （n 可以是负值）        |
|       InterlockedXor       |           将 32 位整型值与 n 进行异或操作           |
| InterlockedCompareExchange | 将 32 位整型值与 n1 进行比较，如果相等，则替换成 n2 |

上表中仅列出了与 32 位（bit）整型相关的 API 函数，Windows 还提供了对 8 位、16 位以及 64 位的整型变量进行原子操作的 API，读者在实际使用时可以自行参考 MSDN。

我们以上表中 **InterlockedIncrement** 为例来说明这类函数的用法，**InterlockedIncrement** 的函数签名是：

```c++
LONG InterlockedIncrement(LONG volatile *Addend);
```

这个函数的作用是将变量 **Addend** 自增 1，并返回自增后的值。

> 注意：这里的 LONG 型即 long 型，在 32 位系统中，LONG 占 4个字节。

我们来写一个例子来验证一下：

```c++
#include <Windows.h>

int main()
{
    LONG nPreValue = 99;
    LONG nPostValue = InterlockedIncrement(&nPreValue);

    printf("nPreValue=%d, nPostValue=%d\n", nPreValue, nPostValue);

    return 0;
}
复制
```

程序执行结果：

![enter image description here](image/887b1310-cf19-11e9-9cb8-a1abccba9727)

### C++11 对整型变量原子操作的支持

在 C++ 98/03 标准中，如果想对整型变量进行原子操作，要么利用操作系统提供的相关原子操作 API，要么利用对应操作系统提供的锁对象来对变量进行保护，无论是哪种方式，编写的代码都无法实现跨平台操作。例如上一小节介绍的 **Interlocked** 系列 API 代码仅能运行于 Windows 系统，无法移植到 Linux 系统。C++ 11 新标准发布以后，改变了这种困境，新标准提供了对整型变量原子操作的相关库，即 std::atomic ，这是一个模板类型：

```c++
template<class T>
struct atomic;
```

你可以传入具体的整型类型（如 bool、char、short、int、uint 等）对模板进行实例化，实际上 stl 库也提供了这些实例化的模板类型：

![avatar](image/FnXmmECnZEji5D_mz9OnINWxS6xs)

上表中仅列出了 C++ 11 支持的常用的整型原子变量，[完整的列表读者可以参考这里](https://zh.cppreference.com/w/cpp/atomic/atomic)。

有了 C++ 语言本身对原子变量的支持以后，我们就可以“愉快地”写出跨平台的代码了，来看一段代码：

```c++
#include <atomic>
#include <stdio.h>

int main()
{
    std::atomic<int> value;
    value = 99;
    printf("%d\n", (int)value);

    //自增1，原子操作
    value++;
    printf("%d\n", (int)value);

    return 0;
}
```

以上代码可以同时在 Windows 和 Linux 平台上运行，但是有读者可能会根据个人习惯将上述代码写成如下形式：

```c++
#include <atomic>
#include <stdio.h>

int main()
{
    std::atomic<int> value = 99;
    printf("%d\n", (int)value);

    //自增1，原子操作
    value++;
    printf("%d\n", (int)value);

    return 0;
}
```

代码仅仅做了一点简单的改动，这段代码在 Windows 平台上运行良好，但是在 Linux 平台上会无法编译通过（这里指的是在支持 C++ 11 语法的 G++ 编译中编译），提示错误是：

```
error: use of deleted function ‘std::atomic<int>::atomic(const std::atomic<int>&)’
```

产生这个错误的原因是 “**std::atomic\ value = 99;**” 这一行代码调用的是 std::atomic 的拷贝构造函数，对于 int 型，其形式一般如下：

```c++
std::atomic<int>::atomic(const std::atomic<int>& rhs);
```

而根据 C++ 11 的规范，这个拷贝构造函数是默认使用 **=delete** 语法禁止编译器生成的，g++ 遵循了这个标准，[参见这里](https://zh.cppreference.com/w/cpp/atomic/atomic/operator%3D)：

```c++
atomic& operator=( const atomic& ) = delete;
```

因此 Linux 平台上编译器会提示错误，而 Windows 的 VC++ 编译器没有遵循这个规范。而对于代码：

```c++
value = 99;
```

g++ 和 VC++ 同时实现规范中的：

```c++
T operator=( T desired )
```

> 因此，如果读者想利用 C++ 11 提供的 std::atomic 库编写跨平台的代码，在使用 std::atomic 提供的方法时建议参考官方 std::atomic 提供的接口说明来使用，而不是想当然地认为一个方法在此平台上可以运行，在另外一个平台也能有相同的行为，避免出现上面说的这种情形。

上述代码中之所以可以对 value 进行自增（++）操作是因为 **std::atomic** 类内部重载了 **operator++** 运算符，除此以外， **std::atomic** 还提供了大量有用的方法，这些方法读者一定会觉得似曾相似：

![avatar](image/Fipp5M8Dox4HWrwSxeVtjj-qkwGa)

上表中各个函数基本上是见名知义，读者不必死记硬背，需要时知道如何查询即可。

### 总结

本讲介绍了整型变量的原子操作，以及为何多线程操作一个整型变量是不安全的。整型变量的原子操作是实际开发中非常常用一个技术场景，建议读者熟练掌握。

**思考题**：

请读者想一想，整型变量的原子操作函数是如何实现的？答案可以在对应的课程微信群中获得。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 9.Windows 线程资源同步之临界区

前面章节介绍了多线程编程的一些基础内容，从本讲开始，我将系统地介绍一遍 Windows 和 Linux 操作系统下各种常用的多线程资源同步对象。

在开始介绍 Windows 多线程资源同步之前，我们来介绍两个重要的 Windows API 函数 **WaitForSingleObject** 和 **WaitForMultipleObjects**，Windows 上所有多线程同步对象基本上都是通过这两个函数完成的，前者只能一次操作一个资源同步对象，后者可以同时操作多个资源同步对象。

先来说 **WaitForSingleObject**，这个函数的签名是：

```c++
DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
```

这个函数的作用是等待一个内核对象，在 Windows 系统上一个内核对象通常使用其句柄来操作，参数 **hHandle** 即需要等待的内核对象，参数 **dwMilliseconds** 是等待这个内核对象的最大时间，时间单位是毫秒，其类型是 DWORD，这是一个 **unsigned long** 类型。如果我们需要无限等待下去，可以将这个参数值设置为 **INFINITE** 宏。

在 Windows 上可以调用 **WaitForSingleObject** 等待的常见对象如下表所示：

|  可以被等待的对象   | 等待对象成功的含义                                        | 对象类型 |
| :-----------------: | :-------------------------------------------------------- | :------: |
|        线程         | 等待线程结束                                              |  HANDLE  |
|       Process       | 等待进程结束                                              |  HANDLE  |
|    Event（事件）    | 等待 Event 有信号                                         |  HANDLE  |
|   Mutex (互斥体)    | 等待持有 Mutex 的线程释放该 Mutex，等待成功，拥有该 Mutex |  HANDLE  |
| Semaphore（信号量） | 等待该 Semaphore 对象有信号                               |  HANDLE  |

上面介绍的等待线程对象上文中已经详细介绍过了，这里不再重复了，等待进程退出与等待线程退出类似，也不再赘述。下文中我们将详细介绍 Event、Mutex、Semaphore 这三种类型的资源同步对象，这里我们先接着介绍 **WaitForSingleObject** 函数的用法，该函数的返回值一般有以下类型：

- **WAIT_FAILED**，表示 **WaitForSingleObject** 函数调用失败了，可以通过 **GetLastError()** 函数得到具体的错误码；
- **WAIT_OBJECT_0**，表示 **WaitForSingleObject** 成功“等待”到设置的对象；
- **WAIT_TIMEOUT**，等待超时；
- **WAIT_ABANDONED**，当等待的对象是 Mutex 类型时，如果持有该 Mutex 对象的线程已经结束，但是没有在结束前释放该 Mutex，此时该 Mutex 已经处于废弃状态，其行为是未知的，不建议再使用。

**WaitForSingleObject** 如其名字一样，只能“等待”单个对象，如果需要同时等待多个对象可以使用 **WaitForMultipleObjects**，除了对象的数量变多了，其用法基本上和 **WaitForSingleObject** 一样。 **WaitForMultipleObjects** 函数签名如下：

```c++
DWORD WaitForMultipleObjects(
    DWORD        nCount,
    const HANDLE *lpHandles,
    BOOL         bWaitAll,
    DWORD        dwMilliseconds
);
```

参数 **lpHandles** 是需要等待的对象数组指针，参数 **nCount** 指定了该数组的长度，参数 **bWaitAll** 表示是否等待数组 **lpHandles** 所有对象有“信号”，取值为 **TRUE** 时，**WaitForMultipleObjects** 会等待所有对象有信号才会返回，取值为 **FALSE** 时，当其中有一个对象有信号时，立即返回，此时其返回值表示哪个对象有信号。

在参数 **bWaitAll** 设置为 **FALSE** 的情况下， 除了上面介绍的返回值是 **WAIT\*FAILED\*** *和 **WAIT*****TIMEOUT** 以外，返回值还有另外两种情形（分别对应 **WaitForSingleObject** 返回值是 **WAIT_OBJECT_0** 和 **WAIT_ABANDONED** 两种情形）：

- **WAIT_OBJECT_0** to (**WAIT_OBJECT_0** + *nCount*– 1)，举个例子，假设现在等待三个对象 A1、A2、A3，它们在数组 **lpHandles** 中的下标依次是 0、1、2，某次 **WaitForMultipleObjects** 返回值是 **Wait_OBJECT_0 + 1**，则表示对象 A2 有信号，导致 WaitForMultipleObjects 调用成功返回。

伪码如下：

```c++
  HANDLE waitHandles[3];
  waitHandles[0] = hA1Handle;
  waitHandles[1] = hA2Handle;
  waitHandles[2] = hA3Handle;

  DWORD dwResult = WaitForMultipleObjects(3, waitHandles, FALSE, 3000);
  switch(dwResult)
  {
      case WAIT_OBJECT_0 + 0:
          //A1 有信号
          break;

      case WAIT_OBJECT_0 + 1:
          //A2 有信号
          break;

      case WAIT_OBJECT_0 + 2:
          //A3 有信号
          break;

      default:
          //出错或超时
          break;
  }
```

- **WAIT_ABANDONED_0** to (**WAIT_ABANDONED_0** + *nCount*– 1)，这种情形与上面的使用方法相同，通过 nCount - 1 可以知道是等待对象数组中哪个对象始终没有被其他线程释放使用权。

> 这里说了这么多理论知识，读者将在下文介绍的 Windows 常用的资源同步对象章节中看到具体的示例代码。

### Windows 的临界区对象

在所有的 Windows 资源同步对象中，CriticalSection （临界区对象，有些书上翻译成“关键段”）是最简单易用的，从程序的术语来说，它防止多线程同时执行其保护的那段代码（**临界区代码**），即临界区代码某一时刻只允许一个线程去执行，示意图如下：

![img](image/ff474c00-cf1b-11e9-af41-f5624add887e)

Windows 没有公开 CriticalSection 数据结构的定义，我们一般使用如下五个 API 函数操作临界区对象：

```c++
void InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
void DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);

BOOL TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
void EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
void LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
复制
```

**InitializeCriticalSection** 和 **DeleteCriticalSection** 用于初始化和销毁一个 **CRITICAL_SECTION** 对象；位于**EnterCriticalSection** 和 **LeaveCriticalSection** 之间的代码即临界区代码；调用 **EnterCriticalSection** 的线程会尝试“进入“临界区，如果进入不了，则会阻塞调用线程，直到成功进入或者超时；**TryEnterCriticalSection** 会尝试进入临界区，如果可以进入，则函数返回 **TRUE** ，如果无法进入则立即返回不会阻塞调用线程，函数返回 **FALSE**。**LeaveCriticalSection** 函数让调用线程离开临界区，离开临界区以后，临界区的代码允许其他线程调用 **EnterCriticalSection** 进入。

> **EnterCriticalSection** 超时时间很长，可以在注册表 **HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager** 这个位置修改参数 CriticalSectionTimeout 的值调整，当然实际开发中我们从来不会修改这个值，如果你的代码等待时间较长最终超时，请检查你的逻辑设计是否合理。

我们来看一段实例代码：

```c++
1  #include <Windows.h>
2  #include <list>
3  #include <iostream>
4  #include <string>
5 
6  CRITICAL_SECTION       g_cs;
7  int                    g_number = 0;
8
9  DWORD __stdcall WorkerThreadProc(LPVOID lpThreadParameter)
10 {
11    DWORD dwThreadID = GetCurrentThreadId();
12    
13    while (true)
14    {
15        EnterCriticalSection(&g_cs);
16          std::cout << "EnterCriticalSection, ThreadID: " << dwThreadID << std::endl;
17        g_number++;
18        SYSTEMTIME st;
19        //获取当前系统时间
20        GetLocalTime(&st);
21        char szMsg[64] = { 0 };
22        sprintf(szMsg, 
23                "[%04d-%02d-%02d %02d:%02d:%02d:%03d]NO.%d, ThreadID: %d.", 
24                st.wYear, st.wMonth, st.wDay, 
25                  st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, 
26                g_number, dwThreadID);
27
28        std::cout << szMsg << std::endl;
29        std::cout << "LeaveCriticalSection, ThreadID: " << dwThreadID << std::endl;
30        LeaveCriticalSection(&g_cs);
31
32        //睡眠1秒
33        Sleep(1000);
34    }
35
36    return 0;
37 }
38
39 int main()
40 {
41    InitializeCriticalSection(&g_cs);
42
43    HANDLE hWorkerThread1 = CreateThread(NULL, 0, WorkerThreadProc, NULL, 0, NULL);
44    HANDLE hWorkerThread2 = CreateThread(NULL, 0, WorkerThreadProc, NULL, 0, NULL);
45
46    WaitForSingleObject(hWorkerThread1, INFINITE);
47    WaitForSingleObject(hWorkerThread2, INFINITE);
48
49    //关闭线程句柄
50    CloseHandle(hWorkerThread1);
51    CloseHandle(hWorkerThread2);
52
53    DeleteCriticalSection(&g_cs);
54
55    return 0;
56 }
```

上述程序执行输出结果如下：

```c++
EnterCriticalSection, ThreadID: 1224
[2019-01-19 22:25:41:031]NO.1, ThreadID: 1224.
LeaveCriticalSection, ThreadID: 1224
EnterCriticalSection, ThreadID: 6588
[2019-01-19 22:25:41:031]NO.2, ThreadID: 6588.
LeaveCriticalSection, ThreadID: 6588
EnterCriticalSection, ThreadID: 6588
[2019-01-19 22:25:42:031]NO.3, ThreadID: 6588.
LeaveCriticalSection, ThreadID: 6588
EnterCriticalSection, ThreadID: 1224
[2019-01-19 22:25:42:031]NO.4, ThreadID: 1224.
LeaveCriticalSection, ThreadID: 1224
EnterCriticalSection, ThreadID: 1224
[2019-01-19 22:25:43:031]NO.5, ThreadID: 1224.
LeaveCriticalSection, ThreadID: 1224
EnterCriticalSection, ThreadID: 6588
[2019-01-19 22:25:43:031]NO.6, ThreadID: 6588.
LeaveCriticalSection, ThreadID: 6588
EnterCriticalSection, ThreadID: 1224
[2019-01-19 22:25:44:031]NO.7, ThreadID: 1224.
LeaveCriticalSection, ThreadID: 1224
EnterCriticalSection, ThreadID: 6588
[2019-01-19 22:25:44:031]NO.8, ThreadID: 6588.
LeaveCriticalSection, ThreadID: 6588
```

在上述代码中我们新建两个工作线程，线程函数都是 **WorkerThreadProc**。线程函数在 **15** 行调用 **EnterCriticalSection** 进入临界区，在 **30** 行调用 **LeaveCriticalSection** 离开临界区，**16** ～ **29** 行之间的代码即临界区的代码，这段代码由于受到临界区对象 **g_cs** 的保护，因为每次只允许一个工作线程执行这段代码。虽然临界区代码中有多个输出，但是这些输出一定都是连续的，不会出现交叉输出的结果。

心的读者会发现上述输出中存在同一个的线程连续两次进入临界区，这是有可能的。也就是说，当其中一个线程离开临界区，即使此时有其他线程在这个临界区外面等待，由于线程调度的不确定性，此时正在等待的线程也不会有先进入临界区的优势，它和刚离开这个临界区的线程再次竞争进入临界区是机会均等的。我们来看一张图：

![enter image description here](image/d100fbc0-cf1b-11e9-af41-f5624add887e)

上图中我们将线程函数的执行流程绘制成一个流程图，两个线程竞争进入临界区可能存在如下情形，为了表述方便，将线程称为 A、B。

- **情形一**：线程 A 被唤醒获得 CPU 时间片进入临界区，执行流程 ①，然后执行临界区代码输出 → 线程 B 获得 CPU 时间片，执行流程 ②，然后失去 CPU 时间片进入休眠 → 线程 A 执行完临界区代码离开临界区后执行流程 ⑤，然后失去 CPU 时间片进入休眠 → 线程 B 被唤醒获得 CPU 时间片执行流程 ③、①，然后执行临界区代码输出。

这种情形下，线程 A 和线程 B 会轮流进入临界区执行代码。

- **情形二**：线程 A 被唤醒获得 CPU 时间片进入临界区，执行流程 ①，然后执行临界区代码输出 → 线程 B 获得 CPU 时间片，执行流程 ③，然后执行流程 ② 在临界区外面失去 CPU 时间片进入休眠 → 线程 A 执行完临界区代码离开临界区后执行流程 ④、① 。

这种情形下，会出现某个线程连续两次甚至更多次的进入临界区执行代码。

如果某个线程在尝试进入临界区时因无法阻塞而进入睡眠状态，当其他线程离开这个临界区后，之前因为这个临界区而阻塞的线程可能会被唤醒进行再次竞争，也可能不被唤醒。但是存在这样一种特例，假设现在存在两个线程 A 和 B，线程 A 离开临界区的线程再也不需要再次进入临界区，那么线程 B 在被唤醒时一定可以进入临界区。线程 B 从睡眠状态被唤醒，这涉及到一次线程的切换，有时候这种开销是不必要的，我们可以让 B 简单地执行一个循环等待一段时间后去进去临界区，而不是先睡眠再唤醒，与后者相比，执行这个循环的消耗更小。这就是所谓的“自旋”，在这种情形下，Windows 提供了另外一个初始化临界区的函数 **InitializeCriticalSectionAndSpinCount**，这个函数比 **InitializeCriticalSection** 多一个自旋的次数：

```c++
BOOL InitializeCriticalSectionAndSpinCount(
      LPCRITICAL_SECTION lpCriticalSection,
      DWORD              dwSpinCount
);
```

参数 **dwSpinCount** 是自旋的次数，$\color{red} {利用自旋来代替让 CPU 进入睡眠和再次被唤醒，消除线程上下文切换带来的消耗，提高效率。}$<u>当然，在实际开发中这种方式是靠不住的，线程调度是操作系统内核的策略，应用层上的应用不应该假设线程的调度策略是按预想的来执行</u>。但是理解线程与临界区之间的原理有利于编写出更高效的应用来。

需要说明的是，临界区对象通过保护一段代码不被多个线程同时执行，进而来保证多个线程之间读写一个对象是安全的。由于同一时刻只有一个线程可以进入临界区，因此这种对资源的操作是排他的，即对于同一个临界区对象，不会出现多个线程同时操作该资源，哪怕是资源本身可以在同一时刻被多个线程进行操作，如多个线程对资源进行读操作，这就带来了效率问题。

我们一般将进入临界区的线程称为该临界区的拥有者（owner）——临界区持有者。

最后，为了避免死锁，**EnterCriticalSection** 和 **LeaveCriticalSection** 需要成对使用，尤其是在具有多个出口的函数中，记得在每个分支处加上 **LeaveCriticalSection**。伪码如下：

```c++
void someFunction()
{
    EnterCriticalSection(&someCriticalSection);
    if (条件A)
    {
        if (条件B)
        {
            LeaveCriticalSection(&someCriticalSection);
            //出口1
            return;
        }

        LeaveCriticalSection(&someCriticalSection);
        //出口2
        return;
    }

    if (条件C)
    {
        LeaveCriticalSection(&someCriticalSection);
        // 出口3
        return;
    }

    if (条件C)
    {
        LeaveCriticalSection(&someCriticalSection);
        // 出口4
        return;
    }
}
```

上述代码中，为了能让临界区对象被正常的释放，在函数的每个出口都加上了 **LeaveCriticalSection** 调用，如果函数的出口非常多，这样的代码太难维护了。因此一般建议使用 **RAII** 技术将临界区 API 封装成对象，<u>**该对象在函其作用域内进入临界区，在出了其作用域后自动离开临界区**</u>，示例代码如下：

```c++
class CCriticalSection
{
public:
    CCriticalSection(CRITICAL_SECTION& cs) : mCS(cs)
    {
        EnterCriticalSection(&mCS);
    }

    ~CCriticalSection()
    {
        LeaveCriticalSection(&mCS);
    }

private:
    CRITICAL_SECTION& mCS;
};
```

利用 **CCriticalSection** 类，我们可以对上述伪码进行优化：

```c++
void someFunction()
{
    CCriticalSection autoCS(someCriticalSection);
    if (条件A)
    {
        if (条件B)
        { 
            //出口1
            return;
        }

        //出口2
        return;
    }

    if (条件C)
    {      
        // 出口3
        return;
    }

    if (条件C)
    {        
        // 出口4
        return;
    }
}
```

上述代码中由于变量 **autoCS** 会在出了函数作用域后调用其析构函数，在析构函数中调用 **LeaveCriticalSection** 自动离开临界区。

### 总结

本讲介绍了 WaitForSingleObject 和 WaitForMultipleObjects 这两个重要的 Windows API 函数，同时介绍了 Windows 上第一个线程同步对象——临界区，为了避免因函数有多个出口造成的编码疏漏，我们介绍了使用 RAII 封装临界区对象的方法。临界区对象是 Windows 系统多线程资源同步最常用的对象之一。

**思考题**

> Windows 临界区对象可以跨进程使用吗？答案可以在对应的课程微信群中获得。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 10.Windows 线程资源同步之 Event

前面一讲我们介绍了 WaitForSingleObject 和 WaitForMultipleObjects 函数，它们是 Windows 多线程编程基础 API，所有资源同步对象都得和它们打交道；然后介绍了可以临界区对象，并且介绍了一个把临界区当自旋锁的扩展用法。本讲我们来介绍 Windows 最常用的多线程同步对象 —— Event。

### Event 使用方法

本节讨论的 Event 对象不是 Windows UI 事件驱动机制中的事件，而是多线程资源同步中的 Event 对象，它也是 Windows 内核对象之一。在 Windows 多线程程序设计中，使用频率较高，我们先来学习一下如何创建 Event 对象，然后逐步展开。创建 Event 的 Windows API 函数签名是：

```c++
HANDLE CreateEvent(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  BOOL                  bManualReset,
  BOOL                  bInitialState,
  LPCTSTR               lpName
);
```

参数和返回值的说明如下。

- 参数 **lpEventAttributes**，这个参数设置了 Event 对象的安全属性，Windows 中所有的内核对象都可以设置这个属性，我们一般设置为 NULL，即使用默认安全属性。
- 参数 **bManualReset**，这个参数设置 Event 对象受信（变成有信号状态）时的行为，当设置为 TRUE 时，表示需要手动调用 ResetEvent 函数去将 Event 重置成无信号状态；当设置为 FALSE，Event 事件对象受信后会自动重置为无信号状态。
- 参数 **bInitialState** 设置 Event 事件对象初始状态是否是受信的，TRUE 表示有信号，FALSE 表示无信号。
- 参数 **lpName** 可以设置 Event 对象的名称，如果不需要设置名称，可以将该参数设置为 NULL。一个 Event 对象根据是否设置了名称分为**具名对象**（具有名称的对象）和**匿名对象**。Event 对象是可以通过名称在不同进程之间共享的，通过这种方式共享很有用，后面我们会详细介绍。
- **返回值**，如果成功创建 Event 对象返回对象的句柄，如果创建失败返回 NULL。

一个无信号的 Event 对象，我们可以通过 **SetEvent** 将其变成受信状态，**SetEvent** 的函数签名如下：

```c++
BOOL SetEvent(HANDLE hEvent);
```

我们将参数 **hEvent** 设置为需要设置信号的 Event 句柄即可。

同理，一个已经受信的 Event 对象，可以使用 **ResetEvent** 对象将其变成无信号状态，**ResetEvent** 的函数签名如下：

```c++
BOOL ResetEvent(HANDLE hEvent);
```

参数 **hEvent** 即我们需要重置的 Event 对象句柄。

说了这么多，来看一个具体的例子。假设现在有两个线程，其中一个是主线程，主线程等待工作线程执行某一项耗时的任务完成后，将任务结果显示出来。代码如下：

```c++
#include <Windows.h>
#include <string>
#include <iostream>

bool        g_bTaskCompleted = false;
std::string g_TaskResult;

DWORD __stdcall WorkerThreadProc(LPVOID lpThreadParameter)
{
    //使用 Sleep 函数模拟一个很耗时的操作
    //睡眠3秒
    Sleep(3000);
    g_TaskResult = "task completed";
    g_bTaskCompleted = true;

    return 0;
}

int main()
{
    HANDLE hWorkerThread = CreateThread(NULL, 0, WorkerThreadProc, NULL, 0, NULL); 
    while (true)
    {
        if (g_bTaskCompleted)
        {
            std::cout << g_TaskResult << std::endl;
            break;
        }        
        else
            std::cout << "Task is in progress..." << std::endl;
    }

    CloseHandle(hWorkerThread);
    return 0;
}
```

上述代码在主线程（**main** 函数）创建一个工作线程，然后<u>主线程进入一个无限循环等待布尔变量 **gbTaskCompleted** 变成真值</u>；工作线程（**WorkerThreadProc** 为线程函数）休眠 3 秒后将变量 **gbTaskCompleted** 设置为真后主线程得以退出循环，并打印代表条件满足后的结果。

程序执行结果如下图所示：

![enter image description here](image/ece5d860-cf20-11e9-956a-e59402c7f15a)

在上述代码中，主线程为了等待工作线程完成任务后获取结果，**使用了一个循环去不断查询任务完成标识，这是很低效的一种做法，等待的线程（主线程）做了很多无用功，对 CPU 时间片也是一种浪费**。我们使用 Event 对象来改写一下上述代码：

```c++
1  #include <Windows.h>
2  #include <string>
3  #include <iostream>
4 
5  bool        g_bTaskCompleted = false;
6  std::string g_TaskResult;
7  HANDLE      g_hTaskEvent = NULL;
8 
9  DWORD __stdcall WorkerThreadProc(LPVOID lpThreadParameter)
10 {
11    //使用 Sleep 函数模拟一个很耗时的操作
12    //睡眠3秒
13    Sleep(3000);
14    g_TaskResult = "task completed";
15    g_bTaskCompleted = true;
16
17    //设置事件信号
18    SetEvent(g_hTaskEvent);
19
20    return 0;
21 }
22
23 int main()
24 {
25    //创建一个匿名的手动重置初始无信号的事件对象
26    g_hTaskEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
27    HANDLE hWorkerThread = CreateThread(NULL, 0, WorkerThreadProc, NULL, 0, NULL); 
28    
29    DWORD dwResult = WaitForSingleObject(g_hTaskEvent, INFINITE);
30    if (dwResult == WAIT_OBJECT_0)
31    {
32        std::cout << g_TaskResult << std::endl;
33    }
34    
35    CloseHandle(hWorkerThread);
36    CloseHandle(g_hTaskEvent);
37    return 0;
38 }
```

在上述代码中，主线程在工作线程完成任务之前会**一直阻塞**代码 **29** 行，**没有任何消耗**，当工作线程完成任务后调用 **SetEvent** 让事件对象受信，这样主线程会立即得到通知，从 **WaitForSingleObject** 返回，此时任务已经完成，就可以得到任务结果了。

在实际的开发中，可以利等待的时间去做一点其他的事情，在我们需要的时候去检测一下事件对象是否有信号即可。另外，Event 对象有两个显著的特点：

- 与临界区对象（以及接下来要介绍的 Mutex 对象）相比，Event 对象没有被谁持让持有者线程变成其 owner 这一说法，因此 Event 对象可以同时唤醒多个等待的工作线程。
- 手动重置的 Event 对象一旦变成受信状态，其信号不会丢失，也就是说当 Event 从无信号变成有信号时，即使某个线程当时没有调用 WaitForSingleObject 等待该 Event 对象受信，而是在这之后才调用 WaitForSingleObject ，仍然能检测到事件的受信状态，即不会丢失信号，**而后面要介绍的条件变量就可能会丢失信号。**

### Event 使用示例

蘑菇街开源的即时通讯 Teamtalk pc 版（[代码下载地址请点击这里](https://github.com/baloonwj/TeamTalk)）在使用 socket 连接服务器时，使用 Event 对象设计了一个超时做法。传统的做法是将 socket 设置为非阻塞的，调用完 connect 函数之后，调用 select 函数检测 socket 是否可写，在 select 函数里面设置超时时间。Teamtalk 的做法如下：

```c++
 //TcpClientModule_Impl.cpp 145行
 IM::Login::IMLoginRes* TcpClientModule_Impl::doLogin(CString &linkaddr, UInt16 port
    ,CString& uName,std::string& pass)
{
    //imcore::IMLibCoreConnect 中通过 connect 连接服务器
    m_socketHandle = imcore::IMLibCoreConnect(util::cStringToString(linkaddr), port);
    imcore::IMLibCoreRegisterCallback(m_socketHandle, this);
    if(util::waitSingleObject(m_eventConnected, 5000))
    {
        IM::Login::IMLoginReq imLoginReq;
        string& name = util::cStringToString(uName);
        imLoginReq.set_user_name(name);
        imLoginReq.set_password(pass);
        imLoginReq.set_online_status(IM::BaseDefine::USER_STATUS_ONLINE);
        imLoginReq.set_client_type(IM::BaseDefine::CLIENT_TYPE_WINDOWS);
        imLoginReq.set_client_version("win_10086");

        if (TCPCLIENT_STATE_OK != m_tcpClientState)
            return 0;

        sendPacket(IM::BaseDefine::SID_LOGIN, IM::BaseDefine::CID_LOGIN_REQ_USERLOGIN, ++g_seqNum
            , &imLoginReq);
        m_pImLoginResp->Clear();
        util::waitSingleObject(m_eventReceived, 10000);
    }

    return m_pImLoginResp;
}
```

**util::waitSingleObject** 即封装 API WaitForSingleObject 函数：

```c++
//utilCommonAPI.cpp 197行
BOOL waitSingleObject(HANDLE handle, Int32 timeout)
{
    int t = 0;
    DWORD waitResult = WAIT_FAILED;
    do
    {
        int timeWaiter = 500;
        t += timeWaiter;
        waitResult = WaitForSingleObject(handle, timeWaiter);
    } while ((WAIT_TIMEOUT == waitResult) && (t < timeout));

    return (WAIT_OBJECT_0 == waitResult);
}
```

等待的 m_eventConnected 对象即是一个 Event 类型：

```c++
//定义
HANDLE                            m_eventConnected;
//在 TcpClientModule_Impl 构造函数中初始化
//m_eventConnected = CreateEvent(NULL, FALSE, FALSE, NULL);
```

这个 WaitForSingleObejct 何时会返回呢？如果网络线程中 connect 函数可以正常连接服务器，会让 m_eventConnected 受信，这样 WaitForSingleObejct 函数就会返回了，接着组装登录数据包接着发数据。

```c++
void TcpClientModule_Impl::onConnectDone()
{
    m_tcpClientState = TCPCLIENT_STATE_OK;
    ::SetEvent(m_eventConnected);

    m_bDoReloginServerNow = FALSE;
    if (!m_pServerPingTimer)
    {
        _startServerPingTimer();
    }
}
```

归纳起来，这里利用了一个 Event 对象实现了一个同步登录的过程，网络连接最大超时事件设置成了 5000 毫秒（5 秒）：

```c++
util::waitSingleObject(m_eventConnected, 5000)
```

### 总结

Event 对象是 Windows 多线程最常用的同步对象之一，其特点是简单易用，如果多个线程都是等待一个 Event 对象受信，无法精确控制唤醒指定数量的线程，后面我们用信号量来解决该问题。

**思考题**

Windows Event 对象可以跨进程使用吗？如果可以，如何多进程共享同一个 Event 对象？答案可以在对应的课程微信群中获得。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 11.Windows 线程同步之 Mutex

**Mutex**（ 互斥量）采用的是英文 **Mutual Exclusive**（互相排斥之意）的缩写。见名知义，Windows 中的 Mutex 对象在同一个时刻最多只能属于一个线程，当然也可以不属于任何线程，获得 Mutex 对象的线程成为该 Mutex 的拥有者（owner）。我们可以在创建 Mutex 对象时设置 Mutex 是否属于创建它的线程，其他线程如果希望获得该 Mutex，则可以调用 WaitForSingleObject 进行申请。创建 Mutex 的 API 是 **CreateMutex**，其函数签名如下：

```c++
HANDLE CreateMutex(
      LPSECURITY_ATTRIBUTES lpMutexAttributes,
      BOOL                  bInitialOwner,
      LPCTSTR               lpName
);
```

参数和返回值说明：

- 参数 **lpMutexAttributes** 用法同 CreateEvent，上面已经介绍过了，一般设置为 NULL；
- 参数 **bInitialOwner**，设置调用 CreateMutex 的线程是否立即拥有该 Mutex 对象，TRUE 拥有，FALSE 不拥有，不拥有时，其他线程调用 WaitForSingleObject 可以获得该 Mutex 对象；
- 参数 **lpName**，Mutex 对象的名称，Mutex 对象和 Event 对象一样，也可以通过名称在多个线程之间共享，如果不需要名称则可以将该参数设置为 NULL，根据是否具有名称 Mutex 对象分为具名 Mutex 和匿名 Mutex；
- 返回值，如果函数调用成功返回 Mutex 的句柄，调用失败返回 NULL。

当一个线程不再需要该 Mutex，可以使用 **ReleaseMutex** 函数释放 Mutex，让其他需要等待该 Mutex 的线程有机会获得该 Mutex，**ReleaseMutex** 的函数签名如下：

```c++
BOOL ReleaseMutex(HANDLE hMutex);
```

参数 **hMutex** 即需要释放所有权的 Mutex 对象句柄。

我们来看一段具体的实例代码：

```c++
#include <Windows.h>
#include <string>
#include <iostream>

HANDLE      g_hMutex = NULL;
int         g_iResource = 0;

DWORD __stdcall WorkerThreadProc(LPVOID lpThreadParameter)
{
    DWORD dwThreadID = GetCurrentThreadId();
    while (true)
    {
        if (WaitForSingleObject(g_hMutex, 1000) == WAIT_OBJECT_0)
        {
            g_iResource++;
            std::cout << "Thread: " << dwThreadID << " becomes mutex owner, ResourceNo: " << g_iResource  << std::endl;
            ReleaseMutex(g_hMutex);
        }
        Sleep(1000);
    }

    return 0;
}

int main()
{
    //创建一个匿名的 Mutex 对象，默认情况下主线程不拥有该 Mutex
    g_hMutex = CreateMutex(NULL, FALSE, NULL);

    HANDLE hWorkerThreads[5]; 
    for (int i = 0; i < 5; ++i)
    {
        hWorkerThreads[i] = CreateThread(NULL, 0, WorkerThreadProc, NULL, 0, NULL);
    }

    for (int i = 0; i < 5; ++i)
    {
        //等待工作线程退出
        WaitForSingleObject(hWorkerThreads[i], INFINITE);
        CloseHandle(hWorkerThreads[i]);
    }

    CloseHandle(g_hMutex);
    return 0;
```

在上述代码中，主线程创建一个 Mutex，并且设置不拥有它，然后五个工作线程去竞争获得这个 Mutex 的使用权，拿到这个 Mutex 之后就可以操作共享资源 **g_iResource** 了，程序的执行效果是五个工作线程随机获得该资源的使用权：

![enter image description here](image/35b97dd0-cf21-11e9-b7bb-e113b501764e)

互斥体对象的排他性，有点类似于公共汽车上的座位，如果一个座位已经被别人占用，其他人需要等待，如果该座位没人坐，则其他人“先到先得”。当你不需要使用的时候，要把座位腾出来让其他有需要的人使用。假设某个线程在退出后，仍然没有释放其持有的 Mutex 对象，这时候使用 WaitForSingleObject 等待该 Mutex 对象的线程，也会立即返回，返回值是 **WAIT_ABANDONED**，表示该 Mutex 处于废弃状态（abandoned），处于废弃状态的 Mutex 不能再使用，其行为是未定义的。

通过上面的分析，我们知道 Windows Mutex 对象存在一个 owner 的概念，即哪个线程获取了该 Mutex 即成为该线程的 owner，事实上 Mutex 对象有一个内部属性记录了 owner，只不过微软没有公开而已。如果对 Mutex 内部实现原理感兴趣，可以阅读“开源版的 Windows” 的源码——ReactOS，其主页如下：https://reactos.org/。

**思考题**

Windows Mutex 对象可以跨进程使用吗？如果可以，如何多进程共享同一个 Mutex 对象？答案可以在对应的课程微信群中获得。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 12.Windows 线程同步之 Semaphore

Semaphore 也是 Windows 多线程同步常用的对象之一，与上面介绍的 Event、Mutex 不同，信号量存在一个资源计数的概念，Event 对象虽然可以同时唤醒多个线程，但是它不能精确地控制同时唤醒指定数目的线程，而 Semaphore 可以。创建 Semaphore 对象的 API 函数签名如下：

```c++
HANDLE CreateSemaphore(
      LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
      LONG                  lInitialCount,
      LONG                  lMaximumCount,
      LPCTSTR               lpName
);
```

**参数**和**返回值**介绍：

- 参数 **lpSemaphoreAttributes** 指定了 Semaphore 对象的安全属性，一般设置为 NULL 使用默认安全属性；
- 参数 **lInitialCount** 指定初始可用资源数量，假设初始资源数量为 2，如果有 5 个线程正在调用 WaitForSingleObject 函数等待该信号量，则有 2 个线程会被唤醒，**每调用一次 WaitForSingleObject 获得 Semaphore 对象，该对象的资源计数会减少一个**。
- 参数 **lMaximumCount** 最大资源数量上限，如果使用 **ReleaseSemaphore** 不断增加资源计数，资源数量最大不能超过这个值，这个值必须设置大于 0。
- 参数 **lpName** 指定 Semaphore 对象的名称，Semaphore 对象也是可以通过名称跨进程共享的，如果不需要设置名称可以将该参数设置为 NULL，设置了名称的 Semaphore 对象被称为具名信号量，反之叫匿名信号量。
- **返回值**：函数调用成功返回 Semaphore 对象的句柄，反之返回 NULL。

如果需要增加信号量的资源计数个数，可以使用 **ReleaseSemaphore** 函数，其签名如下：

```c++
BOOL ReleaseSemaphore(
      HANDLE hSemaphore,
      LONG   lReleaseCount,
      LPLONG lpPreviousCount
);
```

- 参数 **hSemaphore** 是需要操作的信号量句柄；
- 参数 **lReleaseCount**，需要增加的资源数量；
- 参数 **lpPreviousCount** 是一个 long 型（32 位系统上 4 个字节）的指针，函数执行成功后，返回是上一次资源的数量，如果用不到该参数，可以设置为 NULL。

信号量的使用方式类似，<u>根据当前资源的数量按需分配资源消费者，资源消费者会让资源数量减少，**如果资源数量减少为 0，消费者将全部处于挂起状态；**当有新的资源来到时，消费者将继续被唤醒进行处理。</u>

假设现在有一个即时通讯的程序，网络线程不断从网络上收到一条条聊天消息，其他 4 个消息处理线程需要对收到的聊天信息进行加工。由于我们需要根据当前消息的数量来唤醒其中 4 个工作线程中的一个或多个，这正是信号量使用的典型案例，代码如下：

```c++
#include <Windows.h>
#include <string>
#include <iostream>
#include <list>
#include <time.h>

HANDLE                  g_hMsgSemaphore = NULL;
std::list<std::string>  g_listChatMsg;
//保护 g_listChatMsg 的临界区对象
CRITICAL_SECTION        g_csMsg;

DWORD __stdcall NetThreadProc(LPVOID lpThreadParameter)
{
    int nMsgIndex = 0;
    while (true)
    {
        EnterCriticalSection(&g_csMsg);
        //随机产生1～4条消息
        int count = rand() % 4 + 1;
        for (int i = 0; i < count; ++i)
        {
            nMsgIndex++;
            SYSTEMTIME st;
            GetLocalTime(&st);
            char szChatMsg[64] = { 0 };
            sprintf_s(szChatMsg, 64, "[%04d-%02d-%02d %02d:%02d:%02d:%03d] A new msg, NO.%d.",
                st.wYear,
                st.wMonth,
                st.wDay,
                st.wHour,
                st.wMinute,
                st.wSecond,
                st.wMilliseconds,
                nMsgIndex);
            g_listChatMsg.emplace_back(szChatMsg);
        }   
        LeaveCriticalSection(&g_csMsg);

        //增加 count 个资源数量
        ReleaseSemaphore(g_hMsgSemaphore, count, NULL);
    }// end while-loop

    return 0;
}

DWORD __stdcall ParseThreadProc(LPVOID lpThreadParameter)
{
    DWORD dwThreadID = GetCurrentThreadId();
    std::string current;
    while (true)
    {
        if (WaitForSingleObject(g_hMsgSemaphore, INFINITE) == WAIT_OBJECT_0)
        {
            EnterCriticalSection(&g_csMsg);
            if (!g_listChatMsg.empty())
            {
                current = g_listChatMsg.front();
                g_listChatMsg.pop_front();
                std::cout << "Thread: " << dwThreadID << " parse msg: " << current << std::endl;
            }         
            LeaveCriticalSection(&g_csMsg);
        }
    }

    return 0;
}

int main()
{
    //初始化随机数种子
    srand(time(NULL));
    InitializeCriticalSection(&g_csMsg);

    //创建一个匿名的 Semaphore 对象，初始资源数量为 0
    g_hMsgSemaphore = CreateSemaphore(NULL, 0, INT_MAX, NULL);

    HANDLE hNetThread = CreateThread(NULL, 0, NetThreadProc, NULL, 0, NULL);

    HANDLE hWorkerThreads[4];
    for (int i = 0; i < 4; ++i)
    {
        hWorkerThreads[i] = CreateThread(NULL, 0, ParseThreadProc, NULL, 0, NULL);
    }

    for (int i = 0; i < 4; ++i)
    {
        //等待工作线程退出
        WaitForSingleObject(hWorkerThreads[i], INFINITE);
        CloseHandle(hWorkerThreads[i]);
    }

    WaitForSingleObject(hNetThread, INFINITE);
    CloseHandle(hNetThread);

    CloseHandle(g_hMsgSemaphore);

    DeleteCriticalSection(&g_csMsg);
    return 0;
}
```

在上述代码中，网络线程每次随机产生 1 ～ 4 个聊天消息放入消息容器 **g_listChatMsg** 中，然后根据当前新产生的消息数目调用 **ReleaseSemaphore** 增加相应的资源计数，这样就有相应的处理线程被唤醒，从容器 **g_listChatMsg** 中取出消息进行处理。

> 注意：由于会涉及到多个线程操作消息容器 **g_listChatMsg**，这里使用了一个临界区对象 **g_csMsg** 对其进行保护。

程序执行效果如下：

```c++
//这里截取输出中间部分...输出太多，部分结果省略
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.26.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.27.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.28.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.29.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.30.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.31.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.32.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.33.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.34.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.35.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.36.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.37.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.38.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.39.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.40.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.41.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.42.
Thread: 3704 parse msg: [2019-01-20 16:31:47:568] A new msg, NO.43.
Thread: 3704 parse msg: [2019-01-20 16:31:47:569] A new msg, NO.44.
Thread: 3704 parse msg: [2019-01-20 16:31:47:569] A new msg, NO.45.
Thread: 3704 parse msg: [2019-01-20 16:31:47:569] A new msg, NO.46.
Thread: 3704 parse msg: [2019-01-20 16:31:47:569] A new msg, NO.47.
Thread: 5512 parse msg: [2019-01-20 16:31:47:569] A new msg, NO.48.
Thread: 6676 parse msg: [2019-01-20 16:31:47:569] A new msg, NO.49.
Thread: 6676 parse msg: [2019-01-20 16:31:47:569] A new msg, NO.50.
```

总结起来，Semaphore 与上面介绍的 Event、Mutex 不一样，由于存在资源计数的概念，可以精准地控制同时唤醒几个等待的线程。

**思考题一**

> 我当初在学习 Windows 信号量对象时是通过利用信号量写一个 12306 售票程序，由于从 A 站到 B 站的票数量有限，当多个顾客同时购票时只会有部分顾客可以买到。读者不妨也尝试写一下。
>
> 答案可以在对应的课程微信群中获得。

**思考题二**

> Windows Semaphore 对象可以跨进程使用吗？如果可以，如何多进程共享同一个 Mutex 对象？答案可以在对应的课程微信群中获得。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 13.如何让程序只能启动一个实例

前面介绍的 Windows Event、Mutex、Semaphore 对象其创建函数 CreateX 都可以给这些对象指定一个名字，<u>*有了**名字**之后这些线程资源同步对象就可以**通过这个名字在不同进程之间共享**。*</u>

在 Windows 系统上读者应该有这样的体验：有些程序无论双击其启动图标都只会启动一个，我们把这类程序叫做**单实例程序**（Single Instance）。可以利用命名的线程资源同步对象来实现这个效果，这里以互斥体为例。

示例代码如下：

```c++
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //...省略无关代码...

    if (CheckInstance())
    {
        HWND hwndPre = FindWindow(szWindowClass, NULL);
        if (IsWindow(hwndPre))
        {
            if (::IsIconic(hwndPre))
                ::SendMessage(hwndPre, WM_SYSCOMMAND, SC_RESTORE | HTCAPTION, 0);

            ::SetWindowPos(hwndPre, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
            ::SetForegroundWindow(hwndPre);
            ::SetFocus(hwndPre);
            return 0;
        }
    }

    //...省略无关代码
}
```

上述代码在 WinMain 函数开始处先检查是否已经运行起来的程序实例，如果存在，则找到运行中的实例程序主窗口并激活之，这就是读者看到最小化很多单例程序后双击该程序图标会重新激活最小化的程序的效果实现原理。

现在重点是 **CheckInstance()** 函数的实现：

```c++
bool CheckInstance()
{
    HANDLE hSingleInstanceMutex = CreateMutex(NULL, FALSE,_T("MySingleInstanceApp"));
    if (hSingleInstanceMutex != NULL)
    {
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            return true;
        }
    }

    return false;
}
```

我们来分析一下上述 **CheckInstance** 函数：

假设首次启动这个进程，这个进程会调用 **CreateMutex** 函数创建一个名称为“**MySingleInstanceApp**”的互斥体对象。当再次准备启动一份这个进程时，再次调用 **CreateMutex** 函数，由于该名称的互斥体对象已经存在，将会返回已经存在的互斥体对象地址，此时通过 GetLastError() 函数得到的错误码是 **ERROR_ALREADY_EXISTS** 表示该名称的互斥体对象已经存在，此时我们激活已经存在的前一个实例，然后退出当前进程即可。

[完整的代码下载地址请单击这里](https://github.com/baloonwj/mybooksources)。

### 总结

在 Windows 上有太多的应用场景只允许程序启动一个示例，而其原理就是本节所介绍的，希望读者可以理解并掌握该方法。如何保证程序只会启动一个实例是 Windows 开发最常用的应用场景之一，建议读者自己练习一下，尽量掌握。

**思考题**

> 除了使用线程内核同步对象来保证程序只启动一个实例，读者知道还有其他方法吗？我们来看一下金山卫士的源码中是如何实现类似的效果的，请读者尝试分析之。答案可以在对应的课程微信群中获得。

```c++
BOOL CBeikeSafeModule::CheckInstance()
{
    BOOL bRet = FALSE;
    HRESULT hRet = E_FAIL;
    BOOL bAlreadyExisted = FALSE;

    if (NULL != m_mapping.GetHandle())
        return TRUE;

    //重点在这里！
    hRet = m_mapping.MapSharedMem(sizeof(BkSafe_Instance_Data), BKSAFE_DDE_WND_CLASS, &bAlreadyExisted);
    if (FAILED(hRet))
        return bRet;

    if (bAlreadyExisted)
    {
        HWND hWndActive = ((BkSafe_Instance_Data *)m_mapping)->hActiveWnd;

        if( IsWindowRunBackGround(hWndActive) )
        {
            SetWindowRunBackGround(hWndActive, FALSE);
        }

        if (::IsIconic(hWndActive))
            ::SendMessage(hWndActive, WM_SYSCOMMAND, SC_RESTORE | HTCAPTION, 0);

        ::SetWindowPos(hWndActive, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
        ::SetForegroundWindow(hWndActive);
        ::SetFocus(hWndActive);

        goto Exit0;
    }

    bRet = TRUE;

Exit0:

    return bRet;
}

class CAtlFileMappingBase
{
public:
    CAtlFileMappingBase() throw()
    {
        m_pData = NULL;
        m_hMapping = NULL;
    }

    ~CAtlFileMappingBase() throw()
    {
        Unmap();
    }

    HRESULT MapFile(
        _In_ HANDLE hFile,
        _In_ SIZE_T nMappingSize = 0,
        _In_ ULONGLONG nOffset = 0,
        _In_ DWORD dwMappingProtection = PAGE_READONLY,
        _In_ DWORD dwViewDesiredAccess = FILE_MAP_READ) throw()
    {
        ATLASSUME(m_pData == NULL);
        ATLASSUME(m_hMapping == NULL);
        ATLASSERT(hFile != INVALID_HANDLE_VALUE && hFile != NULL);

        ULARGE_INTEGER liFileSize;
        liFileSize.LowPart = ::GetFileSize(hFile, &liFileSize.HighPart);
        if (liFileSize.QuadPart < nMappingSize)
            liFileSize.QuadPart = nMappingSize;

        m_hMapping = ::CreateFileMapping(hFile, NULL, dwMappingProtection, liFileSize.HighPart, liFileSize.LowPart, 0);
        if (m_hMapping == NULL)
            return AtlHresultFromLastError();

        if (nMappingSize == 0)
            m_nMappingSize = (SIZE_T) (liFileSize.QuadPart - nOffset);
        else
            m_nMappingSize = nMappingSize;

        m_dwViewDesiredAccess = dwViewDesiredAccess;
        m_nOffset.QuadPart = nOffset;

        m_pData = ::MapViewOfFileEx(m_hMapping, m_dwViewDesiredAccess, m_nOffset.HighPart, m_nOffset.LowPart, m_nMappingSize, NULL);
        if (m_pData == NULL)
        {
            HRESULT hr;

            hr = AtlHresultFromLastError();
            ::CloseHandle(m_hMapping);
            m_hMapping = NULL;
            return hr;
        }

        return S_OK;
    }

    HRESULT MapSharedMem(
        _In_ SIZE_T nMappingSize,
        _In_z_ LPCTSTR szName,
        _Out_opt_ BOOL* pbAlreadyExisted = NULL,
        _In_opt_ LPSECURITY_ATTRIBUTES lpsa = NULL,
        _In_ DWORD dwMappingProtection = PAGE_READWRITE,
        _In_ DWORD dwViewDesiredAccess = FILE_MAP_ALL_ACCESS) throw()
    {
        ATLASSUME(m_pData == NULL);
        ATLASSUME(m_hMapping == NULL);
        ATLASSERT(nMappingSize > 0);
        ATLASSERT(szName != NULL); // if you just want a regular chunk of memory, use a heap allocator

        m_nMappingSize = nMappingSize;

        ULARGE_INTEGER nSize;
        nSize.QuadPart = nMappingSize;
        m_hMapping = ::CreateFileMapping(INVALID_HANDLE_VALUE, lpsa, dwMappingProtection, nSize.HighPart, nSize.LowPart, szName);
        if (m_hMapping == NULL)
        {
            HRESULT hr = AtlHresultFromLastError();
            _Analysis_assume_(FAILED(hr));
            return hr;
        }

        if (pbAlreadyExisted != NULL)
            *pbAlreadyExisted = (GetLastError() == ERROR_ALREADY_EXISTS);

        m_dwViewDesiredAccess = dwViewDesiredAccess;
        m_nOffset.QuadPart = 0;

        m_pData = ::MapViewOfFileEx(m_hMapping, m_dwViewDesiredAccess, m_nOffset.HighPart, m_nOffset.LowPart, m_nMappingSize, NULL);
        if (m_pData == NULL)
        {
            HRESULT hr;

            hr = AtlHresultFromLastError();
            ::CloseHandle(m_hMapping);
            m_hMapping = NULL;
            return hr;
        }


        return S_OK;
    }

    HRESULT OpenMapping(
        _In_z_ LPCTSTR szName,
        _In_ SIZE_T nMappingSize,
        _In_ ULONGLONG nOffset = 0,
        _In_ DWORD dwViewDesiredAccess = FILE_MAP_ALL_ACCESS) throw()
    {
        ATLASSUME(m_pData == NULL);
        ATLASSUME(m_hMapping == NULL);
        ATLASSERT(szName != NULL); // if you just want a regular chunk of memory, use a heap allocator

        m_nMappingSize = nMappingSize;
        m_dwViewDesiredAccess = dwViewDesiredAccess;

        m_hMapping = ::OpenFileMapping(m_dwViewDesiredAccess, FALSE, szName);
        if (m_hMapping == NULL)
            return AtlHresultFromLastError();

        m_dwViewDesiredAccess = dwViewDesiredAccess;
        m_nOffset.QuadPart = nOffset;

        m_pData = ::MapViewOfFileEx(m_hMapping, m_dwViewDesiredAccess, m_nOffset.HighPart, m_nOffset.LowPart, m_nMappingSize, NULL);
        if (m_pData == NULL)
        {
            HRESULT hr;

            hr = AtlHresultFromLastError();
            ::CloseHandle(m_hMapping);
            m_hMapping = NULL;
            return hr;
        }

        return S_OK;
    }

    HRESULT Unmap() throw()
    {
        HRESULT hr = S_OK;

        if (m_pData != NULL)
        {
            if (!::UnmapViewOfFile(m_pData))
                hr = AtlHresultFromLastError();
            m_pData = NULL;
        }
        if (m_hMapping != NULL)
        {
            if (!::CloseHandle(m_hMapping) && SUCCEEDED(hr))
                hr = AtlHresultFromLastError();
            m_hMapping = NULL;
        }
        return hr;
    }

    void* GetData() const throw()
    {
        return m_pData;
    }

    HANDLE GetHandle() const throw()
    {
        return m_hMapping;
    }

    SIZE_T GetMappingSize() throw()
    {
        return m_nMappingSize;
    }

    HRESULT CopyFrom(_In_ CAtlFileMappingBase& orig) throw()
    {
        if (this == &orig)
            return S_OK;
        ATLASSUME(m_pData == NULL);
        ATLASSUME(m_hMapping == NULL);
        ATLASSERT(orig.m_pData != NULL);
        ATLENSURE_RETURN_VAL(orig.m_hMapping != NULL, E_FAIL);

        m_dwViewDesiredAccess = orig.m_dwViewDesiredAccess;
        m_nOffset.QuadPart = orig.m_nOffset.QuadPart;
        m_nMappingSize = orig.m_nMappingSize;

        if (!::DuplicateHandle(GetCurrentProcess(), orig.m_hMapping, GetCurrentProcess(),
                &m_hMapping, NULL, TRUE, DUPLICATE_SAME_ACCESS))
            return AtlHresultFromLastError();

        m_pData = ::MapViewOfFileEx(m_hMapping, m_dwViewDesiredAccess, m_nOffset.HighPart, m_nOffset.LowPart, m_nMappingSize, NULL);
        if (m_pData == NULL)
        {
            HRESULT hr;

            hr = AtlHresultFromLastError();
            ::CloseHandle(m_hMapping);
            m_hMapping = NULL;
            return hr;
        }

        return S_OK;
    }

    CAtlFileMappingBase(_In_ CAtlFileMappingBase& orig)
    {
        m_pData = NULL;
        m_hMapping = NULL;

        HRESULT hr = CopyFrom(orig);
        if (FAILED(hr))
            AtlThrow(hr);
    }

    CAtlFileMappingBase& operator=(_In_ CAtlFileMappingBase& orig)
    {
        HRESULT hr = CopyFrom(orig);
        if (FAILED(hr))
            AtlThrow(hr);

        return *this;
    }

private:
    void* m_pData;
    SIZE_T m_nMappingSize;
    HANDLE m_hMapping;
    ULARGE_INTEGER m_nOffset;
    DWORD m_dwViewDesiredAccess;
};
```



## 14.Linux 线程同步之互斥体

介绍完 Windows 上的常用多线程同步内核对象后，我们来看一下 Linux 下的线程同步对象。本讲我们介绍一下 Linux 操作系统的 mutex 对象。

### Linux mutex 的用法介绍

Linux 互斥体的用法和 Windows 的临界区对象用法很相似，一般也是通过限制多个线程同时执行某段代码来达到保护资源的目的。和接下来要介绍的信号量、条件变量一样，Linux 互斥体都实现在 NPTL （Native POSIX Thread Library）。在 NPTL 中我们使用数据结构 **pthread_mutex_t** 来表示一个互斥体对象（定义于 **pthread.h** 头文件中）。$\color{red} {互斥体对象我们可以使用两种方式来初始化：}$

- 使用 **PTHREAD_MUTEX_INITIALIZER** 直接给互斥体变量赋值

示例代码如下：

```
#include <pthread.h>
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
```

- 使用 **pthread_mutex_init** 函数初始化

如果互斥量是动态分配的或者需要给互斥量设置属性，则需要使用 **pthread_mutex_init** 函数来初始化互斥体，这个函数的签名如下：

```c++
int pthread_mutex_init(pthread_mutex_t* restrict mutex, 
                       const pthread_mutexattr_t* restrict attr);
```

参数 **mutex** 即我们需要初始化的 mutex 对象的指针，参数 **attr** 是需要设置的互斥体属性，通常情况下，使用默认属性可以将这个参数设置为 NULL，后面会详细介绍每一种属性的用法。如果函数执行成功则会返回 0，如果执行失败则会返回一个具体的错误码信息。

**pthread_mutex_init** 代码示例如下：

```c++
#include <pthread.h>

pthread_mutex_t mymutex;
pthread_mutex_init(&mutex, NULL);
```

当不再需要一个互斥体对象时，可以使用 **pthread_mutex_destroy** 函数来销毁它， **pthread_mutex_destroy** 函数的签名如下：

```c++
int pthread_mutex_destroy(pthread_mutex_t* mutex);
```

参数 **mutex** 即我们需要销毁的互斥体对象，如果函数执行成功会返回 0，如果执行失败会返回一个错误码表面出错原因。这里我们需要注意两点：

- <u>**使用 PTHREAD_MUTEX_INITIALIZER 初始化的互斥量无须销毁**；</u>
- **不要去销毁一个已经加锁或正在被条件变量使用的互斥体对象**，*<u>当互斥量处于已加锁的状态或者正在和条件变量配合使用时，调用 pthread_mutex_destroy 函数会返回 **EBUSY** 错误。</u>*

以下代码段演示了尝试销毁一个被锁定的 mutex 对象：

```c++
  //test_destroy_locked_mutex.cpp
  #include <pthread.h>
  #include <stdio.h>
  #include <errno.h>

  int main()
  {
      pthread_mutex_t mymutex;
      pthread_mutex_init(&mymutex, NULL);
      int ret = pthread_mutex_lock(&mymutex);

      //尝试对被锁定的mutex对象进行销毁
      ret = pthread_mutex_destroy(&mymutex);
      if (ret != 0)
      {
          if (ret == EBUSY)
              printf("EBUSY\n");
          printf("Failed to destroy mutex.\n");
      }

      ret = pthread_mutex_unlock(&mymutex);
      //尝试对已经解锁的mutex对象进行销毁
      ret = pthread_mutex_destroy(&mymutex);
      if (ret == 0)
          printf("Succeeded to destroy mutex.\n");

      return 0;
  }
```

编译上述代码并执行得到我们期望的结果：

```
  [root@myaliyun codes]# g++ -g -o test_destroy_locked_mutex test_destroy_locked_mutex.cpp -lpthread
  [root@myaliyun codes]# ./test_destroy_locked_mutex 
  EBUSY
  Failed to destroy mutex.
  Succeed to destroy mutex.
```

在实际开发中，如果我们遵循正确的使用 mutex 的规范，如创建 mutex 对象后再对其加锁，加锁后才对其进行解锁操作，解锁后才做销毁操作，那么编码时一般不用考虑 pthread_mutex_init/pthread_mutex_destroy/pthread_mutex_lock/pthread_mutex_unlock 等函数的返回值。

对于互斥体的加锁和解锁操作我们一般使用以下三个函数：

```c++
int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_trylock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t* mutex);
```

参数 **mutex** 设置为我们需要加锁和解锁的互斥体对象，上述函数执行成功则返回 0；如果执行失败则返回一个错误码表示具体的出错原因。**具体错误码，随互斥体对象的属性类型的不同而不同。**

设置互斥体对象的属性需要创建一个 pthread_mutexattr_t 类型的对象，和互斥体对象一样，需要使用 pthread_mutexattr_init 函数初始化之，当不需要这个属性对象时，记得使用 pthread_mutexattr_destroy 去销毁它，这两个函数的签名如下：

```c++
int pthread_mutexattr_init(pthread_mutexattr_t* attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t* attr);
```

使用 **pthread_mutexattr_settype**/**pthread_mutexattr_gettype** 设置或获取想要的属性类型：

```c++
int pthread_mutexattr_settype(pthread_mutexattr_t* attr, int type);
int pthread_mutexattr_gettype(const pthread_mutexattr_t* restrict attr, int* restrict type);
```

### mutex 锁的类型

属性类型一般有如下取值：

#### PTHREAD_MUTEX_NORMAL（普通锁）

这是互斥体对象的默认属性（即上文中介绍的 **pthread_mutex_init** 第二个函数设置为 NULL）。当一个线程对一个普通锁加锁以后，其他线程会阻塞在 **pthread_mutex_lock** 调用处， 直到对互斥体加锁的线程释放了锁，我们来用一段实例代码来验证一下：

```c++
  #include <pthread.h>
  #include <stdio.h>
  #include <errno.h>
  #include <unistd.h>

  pthread_mutex_t mymutex;
  int             resourceNo = 0;

  void* worker_thread(void* param)
  {
      pthread_t threadID = pthread_self();

      printf("thread start, ThreadID: %d\n", threadID);

      while (true)
      {
          pthread_mutex_lock(&mymutex);

          printf("Mutex lock, resourceNo: %d, ThreadID: %d\n", resourceNo, threadID);
          resourceNo++;

          printf("Mutex unlock, resourceNo: %d, ThreadID: %d\n", resourceNo, threadID);

          pthread_mutex_unlock(&mymutex);

          //休眠1秒
          sleep(1);
      }

      return NULL;
  }

  int main()
  {
      pthread_mutexattr_t mutex_attr;
      pthread_mutexattr_init(&mutex_attr);
      pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_NORMAL);
      pthread_mutex_init(&mymutex, &mutex_attr);

      //创建5个工作线程
      pthread_t threadID[5];

      for (int i = 0; i < 5; ++i)
      {
          pthread_create(&threadID[i], NULL, worker_thread, NULL);
      }

      for (int i = 0; i < 5; ++i)
      {
          pthread_join(threadID[i], NULL);
      }

      pthread_mutex_destroy(&mymutex);
      pthread_mutexattr_destroy(&mutex_attr);

      return 0;
  }
```

上述代码创建了 5 个工作线程，由于使用了互斥体保护资源 **resourceNo**，因而每次在 **pthread_mutex_lock** 与 **pthread_mutex_unlock** 之间的输出都是连续的，一个线程必须完成了这个工作，其他线程才有机会获得执行这段代码的机会，当一个线程拿到锁后，其他线程会阻塞在 **pthread_mutex_lock** 处。

程序执行结果如下：

```c++
  [root@localhost testmultithread]# ./test
  thread start, ThreadID: 520349440
  Mutex lock, resourceNo: 0, ThreadID: 520349440
  Mutex unlock, resourceNo: 1, ThreadID: 520349440
  thread start, ThreadID: 545527552
  Mutex lock, resourceNo: 1, ThreadID: 545527552
  Mutex unlock, resourceNo: 2, ThreadID: 545527552
  thread start, ThreadID: 511956736
  Mutex lock, resourceNo: 2, ThreadID: 511956736
  Mutex unlock, resourceNo: 3, ThreadID: 511956736
  thread start, ThreadID: 537134848
  Mutex lock, resourceNo: 3, ThreadID: 537134848
  Mutex unlock, resourceNo: 4, ThreadID: 537134848
  thread start, ThreadID: 528742144
  Mutex lock, resourceNo: 4, ThreadID: 528742144
  Mutex unlock, resourceNo: 5, ThreadID: 528742144
  Mutex lock, resourceNo: 5, ThreadID: 545527552
  Mutex unlock, resourceNo: 6, ThreadID: 545527552
  Mutex lock, resourceNo: 6, ThreadID: 537134848
  Mutex unlock, resourceNo: 7, ThreadID: 537134848
  Mutex lock, resourceNo: 7, ThreadID: 528742144
  Mutex unlock, resourceNo: 8, ThreadID: 528742144
  Mutex lock, resourceNo: 8, ThreadID: 520349440
  Mutex unlock, resourceNo: 9, ThreadID: 520349440
  Mutex lock, resourceNo: 9, ThreadID: 511956736
  Mutex unlock, resourceNo: 10, ThreadID: 511956736
  Mutex lock, resourceNo: 10, ThreadID: 545527552
  Mutex unlock, resourceNo: 11, ThreadID: 545527552
  Mutex lock, resourceNo: 11, ThreadID: 537134848
  Mutex unlock, resourceNo: 12, ThreadID: 537134848
  Mutex lock, resourceNo: 12, ThreadID: 520349440
  Mutex unlock, resourceNo: 13, ThreadID: 520349440
  Mutex lock, resourceNo: 13, ThreadID: 528742144
  Mutex unlock, resourceNo: 14, ThreadID: 528742144
  Mutex lock, resourceNo: 14, ThreadID: 511956736
  Mutex unlock, resourceNo: 15, ThreadID: 511956736
  Mutex lock, resourceNo: 15, ThreadID: 528742144
  Mutex unlock, resourceNo: 16, ThreadID: 528742144
  Mutex lock, resourceNo: 16, ThreadID: 545527552
  Mutex unlock, resourceNo: 17, ThreadID: 545527552
  Mutex lock, resourceNo: 17, ThreadID: 520349440
  Mutex unlock, resourceNo: 18, ThreadID: 520349440
  Mutex lock, resourceNo: 18, ThreadID: 537134848
  Mutex unlock, resourceNo: 19, ThreadID: 537134848
  Mutex lock, resourceNo: 19, ThreadID: 511956736
  Mutex unlock, resourceNo: 20, ThreadID: 511956736
  Mutex lock, resourceNo: 20, ThreadID: 545527552
  Mutex unlock, resourceNo: 21, ThreadID: 545527552
  Mutex lock, resourceNo: 21, ThreadID: 528742144
  Mutex unlock, resourceNo: 22, ThreadID: 528742144
  Mutex lock, resourceNo: 22, ThreadID: 520349440
  Mutex unlock, resourceNo: 23, ThreadID: 520349440
  Mutex lock, resourceNo: 23, ThreadID: 537134848
  Mutex unlock, resourceNo: 24, ThreadID: 537134848
  Mutex lock, resourceNo: 24, ThreadID: 511956736
  Mutex unlock, resourceNo: 25, ThreadID: 511956736
  Mutex lock, resourceNo: 25, ThreadID: 528742144
  Mutex unlock, resourceNo: 26, ThreadID: 528742144
  Mutex lock, resourceNo: 26, ThreadID: 545527552
  Mutex unlock, resourceNo: 27, ThreadID: 545527552
  Mutex lock, resourceNo: 27, ThreadID: 520349440
  Mutex unlock, resourceNo: 28, ThreadID: 520349440
  Mutex lock, resourceNo: 28, ThreadID: 511956736
  Mutex unlock, resourceNo: 29, ThreadID: 511956736
  Mutex lock, resourceNo: 29, ThreadID: 537134848
  Mutex unlock, resourceNo: 30, ThreadID: 537134848
复制
```

一个线程如果对一个已经加锁的普通锁再次使用 pthread_mutex_lock 加锁，程序会阻塞在第二次调用 pthread_mutex_lock 代码处。测试代码如下：

```c++
  #include <pthread.h>
  #include <stdio.h>
  #include <errno.h>
  #include <unistd.h>

  int main()
  {
      pthread_mutex_t mymutex;
      pthread_mutexattr_t mutex_attr;
      pthread_mutexattr_init(&mutex_attr);
      pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_NORMAL);
      pthread_mutex_init(&mymutex, &mutex_attr);

      int ret = pthread_mutex_lock(&mymutex);
      printf("ret = %d\n", ret);

      ret = pthread_mutex_lock(&mymutex);
      printf("ret = %d\n", ret);



      pthread_mutex_destroy(&mymutex);
      pthread_mutexattr_destroy(&mutex_attr);

      return 0;
  }
```

编译并使用 gdb 将程序运行起来，程序只输出了一行，我们按 Ctrl + C （下文中 ^C 字符）将 gdb 中断下来，然后使用 bt 命令发现程序确实阻塞在第二个 **pthread_mutex_lock** 函数调用处：

```c
  [root@localhost testmultithread]# g++ -g -o test test.cpp -lpthread
  [root@localhost testmultithread]# gdb test
  Reading symbols from /root/testmultithread/test...done.
  (gdb) r
  Starting program: /root/testmultithread/test 
  [Thread debugging using libthread_db enabled]
  Using host libthread_db library "/lib64/libthread_db.so.1".
  ret = 0
  ^C
  Program received signal SIGINT, Interrupt.
  0x00007ffff7bcd4ed in __lll_lock_wait () from /lib64/libpthread.so.0
  Missing separate debuginfos, use: debuginfo-install glibc-2.17-260.el7.x86_64 libgcc-4.8.5-36.el7.x86_64 libstdc++-4.8.5-36.el7.x86_64
  (gdb) bt
  #0  0x00007ffff7bcd4ed in __lll_lock_wait () from /lib64/libpthread.so.0
  #1  0x00007ffff7bc8dcb in _L_lock_883 () from /lib64/libpthread.so.0
  #2  0x00007ffff7bc8c98 in pthread_mutex_lock () from /lib64/libpthread.so.0
  #3  0x00000000004007f4 in main () at ConsoleApplication10.cpp:17
  (gdb) 
```

在这种类型的情况， **pthread_mutex_trylock** 函数如果拿不到锁，**不会阻塞，函数会立即返回**，并返回 **EBUSY** 错误码。

#### PTHREAD_MUTEX_ERRORCHECK（检错锁）

如果一个线程使用 **pthread_mutex_lock** 对已经加锁的互斥体对象再次加锁，**pthread_mutex_lock** 会返回 **EDEADLK**。

我们验证一下线程对自己已经加锁的互斥体对象再次加锁是什么行为？

```c
  #include <pthread.h>
  #include <stdio.h>
  #include <errno.h>
  #include <unistd.h>

  int main()
  {
      pthread_mutex_t mymutex;
      pthread_mutexattr_t mutex_attr;
      pthread_mutexattr_init(&mutex_attr);
      pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_ERRORCHECK);
      pthread_mutex_init(&mymutex, &mutex_attr);

      int ret = pthread_mutex_lock(&mymutex);
      printf("ret = %d\n", ret);

      ret = pthread_mutex_lock(&mymutex);
      printf("ret = %d\n", ret);
      if (ret == EDEADLK)
      {
          printf("EDEADLK\n");
      }

      pthread_mutex_destroy(&mymutex);
      pthread_mutexattr_destroy(&mutex_attr);

      return 0;
  }
```

编译并运行程序，程序输出结果确实如上面所说：

```c
  [root@localhost testmultithread]# g++ -g -o test11 test.cpp -lpthread
  [root@localhost testmultithread]# ./test11
  ret = 0
  ret = 35
  EDEADLK
```

再来看一下，一个线程加锁，其他线程再次加锁的效果：

```c++
  #include <pthread.h>
  #include <stdio.h>
  #include <errno.h>
  #include <unistd.h>

  pthread_mutex_t mymutex;

  void* worker_thread(void* param)
  {
      pthread_t threadID = pthread_self();

      printf("thread start, ThreadID: %d\n", threadID);

      while (true)
      {
          int ret = pthread_mutex_lock(&mymutex);
          if (ret == EDEADLK)
          {
              printf("EDEADLK, ThreadID: %d\n", threadID);
          } 
          else
              printf("ret = %d, ThreadID: %d\n", ret, threadID);

          //休眠1秒
          sleep(1);
      }

      return NULL;
  }

  int main()
  {
      pthread_mutexattr_t mutex_attr;
      pthread_mutexattr_init(&mutex_attr);
      pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_ERRORCHECK);
      pthread_mutex_init(&mymutex, &mutex_attr);

      int ret = pthread_mutex_lock(&mymutex);
      printf("ret = %d\n", ret);

      //创建5个工作线程
      pthread_t threadID[5];
      for (int i = 0; i < 5; ++i)
      {
          pthread_create(&threadID[i], NULL, worker_thread, NULL);
      }

      for (int i = 0; i < 5; ++i)
      {
          pthread_join(threadID[i], NULL);
      }

      pthread_mutex_destroy(&mymutex);
      pthread_mutexattr_destroy(&mutex_attr);

      return 0;
  }
```

编译程序，然后使用 gdb 运行起来，发现程序并没有有任何输出，按 Ctrl + C 中断下来，输入 **info thread** 命令发现工作线程均阻塞在 **pthread_mutex_lock** 函数调用处。操作及输出结果如下：

```c
  [root@localhost testmultithread]# g++ -g -o test8 ConsoleApplication8.cpp -lpthread
  [root@localhost testmultithread]# ./test8
  ret = 0
  thread start, ThreadID: -1821989120
  thread start, ThreadID: -1830381824
  thread start, ThreadID: -1838774528
  thread start, ThreadID: -1847167232
  thread start, ThreadID: -1813596416
  ^C
  [root@localhost testmultithread]# gdb test8
  GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-114.el7
  Copyright (C) 2013 Free Software Foundation, Inc.
  License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
  This is free software: you are free to change and redistribute it.
  There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
  and "show warranty" for details.
  This GDB was configured as "x86_64-redhat-linux-gnu".
  For bug reporting instructions, please see:
  <http://www.gnu.org/software/gdb/bugs/>...
  Reading symbols from /root/testmultithread/test8...done.
  (gdb) r
  Starting program: /root/testmultithread/test8 
  [Thread debugging using libthread_db enabled]
  Using host libthread_db library "/lib64/libthread_db.so.1".
  ret = 0
  [New Thread 0x7ffff6fd2700 (LWP 3276)]
  thread start, ThreadID: -151181568
  [New Thread 0x7ffff67d1700 (LWP 3277)]
  thread start, ThreadID: -159574272
  [New Thread 0x7ffff5fd0700 (LWP 3278)]
  thread start, ThreadID: -167966976
  [New Thread 0x7ffff57cf700 (LWP 3279)]
  thread start, ThreadID: -176359680
  [New Thread 0x7ffff4fce700 (LWP 3280)]
  thread start, ThreadID: -184752384
  ^C
  Program received signal SIGINT, Interrupt.
  0x00007ffff7bc7f47 in pthread_join () from /lib64/libpthread.so.0
  Missing separate debuginfos, use: debuginfo-install glibc-2.17-260.el7.x86_64 libgcc-4.8.5-36.el7.x86_64 libstdc++-4.8.5-36.el7.x86_64
  (gdb) bt
  #0  0x00007ffff7bc7f47 in pthread_join () from /lib64/libpthread.so.0
  #1  0x00000000004009e9 in main () at ConsoleApplication8.cpp:50
  (gdb) inf threads
    Id   Target Id         Frame 
    6    Thread 0x7ffff4fce700 (LWP 3280) "test8" 0x00007ffff7bcd4ed in __lll_lock_wait () from /lib64/libpthread.so.0
    5    Thread 0x7ffff57cf700 (LWP 3279) "test8" 0x00007ffff7bcd4ed in __lll_lock_wait () from /lib64/libpthread.so.0
    4    Thread 0x7ffff5fd0700 (LWP 3278) "test8" 0x00007ffff7bcd4ed in __lll_lock_wait () from /lib64/libpthread.so.0
    3    Thread 0x7ffff67d1700 (LWP 3277) "test8" 0x00007ffff7bcd4ed in __lll_lock_wait () from /lib64/libpthread.so.0
    2    Thread 0x7ffff6fd2700 (LWP 3276) "test8" 0x00007ffff7bcd4ed in __lll_lock_wait () from /lib64/libpthread.so.0
  * 1    Thread 0x7ffff7fee740 (LWP 3272) "test8" 0x00007ffff7bc7f47 in pthread_join () from /lib64/libpthread.so.0
  (gdb)
```

通过上面的实验，如果互斥体的属性是 **PTHREAD_MUTEX_ERRORCHECK**，当前线程重复调用 **pthread_mutex_lock** 会直接返回 **EDEADLOCK**，其他线程如果对这个互斥体再次调用 **pthread_mutex_lock** 会阻塞在该函数的调用处。

#### PTHREAD_MUTEX_RECURSIVE（嵌套锁）

该属性允许$\color{red} {同一个线程}$对其持有的互斥体**重复加锁**，每次成功调用 **pthread_mutex_lock** 一次，**该互斥体对象的锁引用计数就会增加一次**，相反，每次成功调用 **pthread_mutex_unlock** 一次，**锁引用计数就会减少一次**，当锁引用计数值为 0 时允许其他线程获得该锁，否则其他线程调用 **pthread_mutex_lock** 时尝试获取锁时，会阻塞在那里。这种方式很好理解，这里就不贴示例代码了。

### 总结

我们来总结下 Linux 互斥体对象的使用要点：

- 虽然在上文演示了同一个线程对一个互斥体对象反复进行加锁，但在实际开发中，我们需要用到这种场景的情形非常少；
- 与 Windows 的临界区对象一样，一些有很多出口的逻辑中，为了避免因忘记调用 **pthread_mutex_unlock** 出现死锁或者在逻辑出口处有大量解锁的重复代码出现，建议使用 RAII 技术将互斥体对象封装起来，具体方式在上文中已经介绍过了，这里不再赘述。

**思考题**

> 读者觉得 Linux 的 mutex 对象的用法和 Windows 的哪个内核同步对象最相似？答案可以在对应的课程微信群中获得。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 15.Linux 线程同步之信号量

与 Windows 的 Semaphore 对象使用原理一样，Linux 的信号量本质上也是暗含着“资源有多份，可以同时被多个线程访问”的意味，故信号量的原理这里不再赘述。

Linux 信号量常用的一组 API 函数是：

```c++
#include <semaphore.h>
int sem_init(sem_t* sem, int pshared, unsigned int value);
int sem_destroy(sem_t* sem);
int sem_post(sem_t* sem);
int sem_wait(sem_t* sem);
int sem_trywait(sem_t* sem);
int sem_timedwait(sem_t* sem, const struct timespec* abs_timeout);
```

- 函数 **sem_init** 用于初始化一个信号量，1.第一个参数 **sem** 传入需要初始化的信号量对象的地址；2.第二个参数 **pshared** 表示该信号量是否可以被共享，**取值为 0 表示该信号量可以在同一个进程多个线程之间共享(匿名二值信号量模拟互斥锁)**，**取值为非 0 表示可以在多个进程之间共享(<u>有名信号量</u>)**；第三个参数 **value** 用于设置信号量初始状态下资源的数量。函数 **sem_init** 函数调用成功返回 0，失败返回 -1，实际编码中只要我们的写法得当一般不用关心该函数的返回值。

- 函数 **sem_destroy** 用于销毁一个信号量。
- 函数 **sem_post** 将信号量的资源计数递增 1，并解锁该信号量对象，这样其他由于使用 **sem_wait** 被阻塞的线程会被唤醒。
- 如果当前信号量资源计数为 0，函数 **sem_wait** 会阻塞调用线程；直到信号量对象的资源计数大于 0 时被唤醒，唤醒后将资源计数递减 1，然后立即返回；函数 **sem_trywait** 是函数 **sem_wait** 的非阻塞版本，如果当前信号量对象的资源计数等于 0，**sem_trywait** 会立即返回不会阻塞调用线程，返回值是 ﹣1，错误码 errno 被设置成 **EAGAIN**；函数 **sem_timedwait** 是带有等待时间的版本，等待时间在第二个参数 **abs_timeout** 中设置，这是个结构体的定义如下：

```c++
struct timespec
{
    time_t tv_sec;      /* 秒 */
    long   tv_nsec;     /* 纳秒 [0 .. 999999999] */
};
```

**sem_timedwait** 在参数 **abs_timeout** 设置的时间内等待信号量对象的资源计数大于0，否则超时返回，返回值为 ﹣1，错误码 errno 是 **ETIMEDOUT**。<u>*当使用 **sem_timedwait** 时，参数 **abs_timeout** 不能设置为 NULL，否则程序会在运行时调用 **sem_timedwait** 产生崩溃。*</u>

> 注意：
>
> sem_wait、sem_trywait、sem_timedwait 函数将资源计数递减一时会同时锁定信号量对象，因此当资源计数为 1 时，如果有多个线程调用 sem_wait 等函数等待该信号量时，只会有一个线程被唤醒。当 sem_wait 函数返回时，会释放对该信号量的锁。
>
> sem_wait、sem_trywait、sem_timedwait 函数调用成功后返回值均为 0，调用失败返回 ﹣1，可以通过错误码 errno 获得失败原因。
>
> sem_wait、sem_trywait、sem_timedwait **可以被 Linux 信号中断，被信号中断后，函数立即返回，返回值是 ﹣1，错误码 errno 为 EINTR。**

虽然上述函数没有以 pthread_ 作为前缀，实际使用这个系列的函数时需要链接 pthread 库。

我们看一个信号量的具体使用示例：

```c++
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <list>
#include <semaphore.h>
#include <iostream>

class Task
{
public:
    Task(int taskID)
    {
        this->taskID = taskID;
    }

    void doTask()
    {
        std::cout << "handle a task, taskID: " << taskID << ", threadID: " << pthread_self() << std::endl; 
    }

private:
    int taskID;
};

pthread_mutex_t  mymutex;
std::list<Task*> tasks;
sem_t            mysemaphore;

void* consumer_thread(void* param)
{    
    Task* pTask = NULL;
    while (true)
    {
        if (sem_wait(&mysemaphore) != 0)
            continue;

        if (tasks.empty())
            continue;

        pthread_mutex_lock(&mymutex);   
        pTask = tasks.front();
        tasks.pop_front();
        pthread_mutex_unlock(&mymutex);

        pTask->doTask();
        delete pTask;
    }

    return NULL;
}

void* producer_thread(void* param)
{
    int taskID = 0;
    Task* pTask = NULL;

    while (true)
    {
        pTask = new Task(taskID);

        pthread_mutex_lock(&mymutex);
        tasks.push_back(pTask);
        std::cout << "produce a task, taskID: " << taskID << ", threadID: " << pthread_self() << std::endl; 

        pthread_mutex_unlock(&mymutex);

        //释放信号量，通知消费者线程
        sem_post(&mysemaphore);

        taskID ++;

        //休眠1秒
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_mutex_init(&mymutex, NULL);
    //初始信号量资源计数为0
    sem_init(&mysemaphore, 0, 0);

    //创建5个消费者线程
    pthread_t consumerThreadID[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&consumerThreadID[i], NULL, consumer_thread, NULL);
    }

    //创建一个生产者线程
    pthread_t producerThreadID;
    pthread_create(&producerThreadID, NULL, producer_thread, NULL);

    pthread_join(producerThreadID, NULL);

    for (int i = 0; i < 5; ++i)
    {
        pthread_join(consumerThreadID[i], NULL);
    }

    sem_destroy(&mysemaphore);
    pthread_mutex_destroy(&mymutex);

    return 0;
}
```

以上代码中我们创建一个生产者线程和 5 个消费者线程，**初始信号量计数为 0 代表开始没有可执行任务**，因此 5 个消费线程均阻塞在 **sem_wait** 调用处，接着生产者每隔 1 秒产生一个任务，然后通过调用 **sem_post** 将信号量资源计数增加一，此时其中一个线程会被唤醒，然后从任务队列中取出任务，执行任务，由于任务对象是 new 出来的，需要 delete 掉以避免内存泄露。

有读者可能会奇怪，在调用 **sem_wait** 和 **sem_post** 时会对信号量对象进行加锁和解锁，为什么这里还需要使用一个 mutex？这个 mutex 是用来保护队列 **tasks** 的，因为多个线程会同时读写之。这个例子类似于银行里多个客户等待柜台有空闲办理取钱业务，每次有空闲的柜台，就可以告诉客户，但是多人同时取钱时，银行的资金总账户增减一定是原子性的。

编译并生成文件 **semaphore** ，然后运行之，输出结果如下：

```c
[root@localhost testsemaphore]# g++ -g -o semaphore semaphore.cpp -lpthread
[root@localhost testsemaphore]# ./semaphore 
produce a task, taskID: 0, threadID: 140055260595968
handle a task, taskID: 0, threadID: 140055277381376
produce a task, taskID: 1, threadID: 140055260595968
handle a task, taskID: 1, threadID: 140055277381376
produce a task, taskID: 2, threadID: 140055260595968
handle a task, taskID: 2, threadID: 140055268988672
produce a task, taskID: 3, threadID: 140055260595968
handle a task, taskID: 3, threadID: 140055294166784
produce a task, taskID: 4, threadID: 140055260595968
handle a task, taskID: 4, threadID: 140055302559488
produce a task, taskID: 5, threadID: 140055260595968
handle a task, taskID: 5, threadID: 140055285774080
produce a task, taskID: 6, threadID: 140055260595968
handle a task, taskID: 6, threadID: 140055277381376
produce a task, taskID: 7, threadID: 140055260595968
handle a task, taskID: 7, threadID: 140055268988672
produce a task, taskID: 8, threadID: 140055260595968
handle a task, taskID: 8, threadID: 140055294166784
produce a task, taskID: 9, threadID: 140055260595968
handle a task, taskID: 9, threadID: 140055302559488
...更多输出结果省略...
```

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 16.Linux 线程同步之条件变量

有人说 Linux 条件变量（Condition Variable）是最不会用错的一种线程同步对象，确实是这样，但这必须建立在你对条件变量熟练使用的基础之上。我们先来讨论一下为什么会存在条件变量这样一种机制。

### 为什么需要使用条件变量

实际应用中，我们常常会有类似如下需求：

```c++
//以下是伪码，m 的类型是 pthread_mutex_t，并且已经初始化过了
int WaitForTrue()
{
    pthread_mutex_lock(&m);
    while (condition is false)      //条件不满足
    {
        pthread_mutex_unlock(&m);   //解锁等待其他线程改变 condition
        sleep(n);                   //睡眠n秒
        //n秒后再次加锁验证条件是否满足
        pthread_mutex_lock(&m);
    }

    return 1;
}
```

以上逻辑可以表示成如下流程图：

![enter image description here](image/78109bc0-cf92-11e9-a227-638143eb6e37)

这段逻辑的用途是我们需要反复判断一个多线程共享条件是否满足，一直到该条件满足为止，由于该条件被多个线程操作因此每次判断之前都需要进行加锁操作，判断完毕后需要进行解锁操作。但是上述逻辑存在严重的效率问题，假设解锁离开临界区后，此时由于其他线程修改了条件导致条件满足了，此时程序仍然需要睡眠 n 秒后才能得到反馈。因此我们需要这样一种机制：

> 某个线程 A 在条件不满足的情况下，主动让出互斥量，让其他线程去折腾，线程在此处等待，等待条件的满足；一旦条件满足，线程就可以被立刻唤醒。线程 A 之所以可以安心等待，依赖的是其他线程的协作，它确信会有一个线程在发现条件满足以后，将向它发送信号，并且让出互斥量。如果其他线程不配合（不发信号，不让出互斥量），这个主动让出互斥量并等待事件发生的线程 A 就真的要等到花儿都谢了。

这个例子解释了为什么需要条件等待，但是条件等待还不是条件变量的全部功能。

### 条件变量为什么要与互斥体对象结合

很多第一次学习 Linux 条件变量的读者会觉得困惑：**为什么条件变量一定要与一个互斥体对象结合使用？**我们来看下，**假设条件变量不与互斥体对象结合的效果**。

```c++
1 //m的类型是 pthread_mutex_t，并且已经初始化过了，cv 是条件变量
2 pthread_mutex_lock(&m)
3 while(condition_is_false)
4 {
5     pthread_mutex_unlock(&m);
6     //解锁之后，等待之前，可能条件已经满足，信号已经发出，但是该信号可能会被错过
7     cond_wait(&cv);
8     pthread_mutex_lock(&m);
9 }
```

上述代码中，假设线程 A 执行完第 5 行代码 pthread_mutex_unlock(&m); 后 CPU 时间片被剥夺，此时另外一个线程 B 获得该互斥体对象 m，然后发送条件信号，等线程 A 重新获得时间片后，由于该信号已经被错过了，**这样可能会导致线程 A 在 第 7 行 cond_wait(&cv); 无限阻塞下去。**

**造成这个问题的根源是释放互斥体对象与条件变量等待唤醒不是原子操作，即解锁和等待这两个步骤必须是同一个原子性的操作，<u>以确保 cond_wait 唤醒之前不会有其他线程获得这个互斥体对象</u>。**

介绍了这么多，我们来正式介绍一下条件变量相关的系统 API 的使用方法。

条件变量的初始化和销毁可以使用如下 API 函数：

```c++
int pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t* attr);
int pthread_cond_destroy(pthread_cond_t* cond);
```

在 Linux 系统中 **pthread_cond_t** 即是条件变量的类型，**当然和前面介绍的互斥体一样，也可以使用如下方式去初始化一个条件变量**：

```c++
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
```

等待条件变量的满足可以使用如下 API 函数：

```c++
int pthread_cond_wait(pthread_cond_t* restrict cond, pthread_mutex_t* restrict mutex);
int pthread_cond_timedwait(pthread_cond_t* restrict cond, pthread_mutex_t* restrict mutex, const struct timespec* restrict abstime);
```

一般情况下如果条件变量代表的条件不会满足，调用

**pthread_cond_wait** 的线程会一直等待下去；<u>**pthread_cond_timedwait** 是 **pthread_cond_wait** 非阻塞版本，</u>它会在指定时间内等待条件满足，超过参数 **abstime** 设置的时候后 **pthread_cond_timedwait** 函数会立即返回。

> 注意：对于参数 **abstime**，正如其名字暗示的，这是一个 absolute time（**绝对时间**），也就是说，如果你打算让函数等待 5 秒，那么**你应该先得到当前系统的时间，然后加上 5 秒计算出最终的时间**作为参数 **abstime** 的值。

因调用 **pthread_cond_wait** 等待的线程可以被以下 API 函数唤醒：

```c++
int pthread_cond_signal(pthread_cond_t* cond);
int pthread_cond_broadcast(pthread_cond_t* cond); 
```

**pthread_cond_signal** 一次唤醒一个线程，如果有多个线程调用 **pthread_cond_wait** 等待，具体哪个线程被唤醒是不确定的（**可以认为是随机的**）；**pthread_cond_broadcast** 可以同时唤醒多个调用 **pthread_cond_wait** 等待的线程。前者相当于发送一次条件通知，后者广播一次条件通知。成功等待到条件信号，**pthread_cond_signal** 和 **pthread_cond_broadcast** 返回 0，反之返回非 0 值，具体错误原因可以通过错误码 errno 获得。

我们将前文中介绍信号量的示例代码用条件变量来改写下：

```c++
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <list>
#include <semaphore.h>
#include <iostream>

class Task
{
public:
    Task(int taskID)
    {
        this->taskID = taskID;
    }

    void doTask()
    {
        std::cout << "handle a task, taskID: " << taskID << ", threadID: " << pthread_self() << std::endl; 
    }

private:
    int taskID;
};

pthread_mutex_t  mymutex;
std::list<Task*> tasks;
pthread_cond_t   mycv;

void* consumer_thread(void* param)
{    
    Task* pTask = NULL;
    while (true)
    {
        pthread_mutex_lock(&mymutex);
        while (tasks.empty())
        {               
            //如果获得了互斥锁，但是条件不合适的话，pthread_cond_wait 会释放锁，不往下执行
            //当发生变化后，条件合适，pthread_cond_wait 将直接获得锁
            pthread_cond_wait(&mycv, &mymutex);
        }

        pTask = tasks.front();
        tasks.pop_front();

        pthread_mutex_unlock(&mymutex);

        if (pTask == NULL)
            continue;

        pTask->doTask();
        delete pTask;
        pTask = NULL;       
    }

    return NULL;
}

void* producer_thread(void* param)
{
    int taskID = 0;
    Task* pTask = NULL;

    while (true)
    {
        pTask = new Task(taskID);

        pthread_mutex_lock(&mymutex);
        tasks.push_back(pTask);
        std::cout << "produce a task, taskID: " << taskID << ", threadID: " << pthread_self() << std::endl; 

        pthread_mutex_unlock(&mymutex);

        //释放信号量，通知消费者线程
        pthread_cond_signal(&mycv);

        taskID++;

        //休眠1秒
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_mutex_init(&mymutex, NULL);
    pthread_cond_init(&mycv, NULL);

    //创建 5 个消费者线程
    pthread_t consumerThreadID[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&consumerThreadID[i], NULL, consumer_thread, NULL);
    }

    //创建一个生产者线程
    pthread_t producerThreadID;
    pthread_create(&producerThreadID, NULL, producer_thread, NULL);

    pthread_join(producerThreadID, NULL);

    for (int i = 0; i < 5; ++i)
    {
        pthread_join(consumerThreadID[i], NULL);
    }

    pthread_cond_destroy(&mycv);
    pthread_mutex_destroy(&mymutex);

    return 0;
}
```

编译并执行上述程序，输出结果如下：

```bash
[root@localhost testsemaphore]# g++ -g -o cv cv.cpp -lpthread
[root@localhost testsemaphore]# ./cv
produce a task, taskID: 0, threadID: 140571200554752
handle a task, taskID: 0, threadID: 140571242518272
produce a task, taskID: 1, threadID: 140571200554752
handle a task, taskID: 1, threadID: 140571225732864
produce a task, taskID: 2, threadID: 140571200554752
handle a task, taskID: 2, threadID: 140571208947456
produce a task, taskID: 3, threadID: 140571200554752
handle a task, taskID: 3, threadID: 140571242518272
produce a task, taskID: 4, threadID: 140571200554752
handle a task, taskID: 4, threadID: 140571234125568
produce a task, taskID: 5, threadID: 140571200554752
handle a task, taskID: 5, threadID: 140571217340160
produce a task, taskID: 6, threadID: 140571200554752
handle a task, taskID: 6, threadID: 140571225732864
produce a task, taskID: 7, threadID: 140571200554752
handle a task, taskID: 7, threadID: 140571208947456
produce a task, taskID: 8, threadID: 140571200554752
handle a task, taskID: 8, threadID: 140571242518272
...更多输出结果省略...
```

条件变量最关键的一个地方就是需要清楚地记得 **pthread_cond_wait** 在条件满足与不满足时的两种行为，这是难点也是**重点**：

- 当 **pthread_cond_wait** 函数阻塞时，它会释放其绑定的互斥体，**并阻塞线程**，因此在调用该函数前应该对互斥体有个加锁操作（上述代码的第 **34** 行的 pthread_mutex_lock(&mymutex);）。
- 当收到条件信号时， **pthread_cond_wait** 会返回并对其绑定的互斥体进行加锁，因此在其下面一定有个对互斥体进行解锁的操作（上述代码的第 **45** 行 pthread_mutex_unlock(&mymutex);）。

### 条件变量的虚假唤醒

上面将互斥量和条件变量配合使用的示例代码中有个很有意思的地方，**就是用了 while 语句，醒来之后要再次判断条件是否满足。**

```c++
while (tasks.empty())
{                
    pthread_cond_wait(&mycv, &mymutex);
}
```

为什么不写成：

```c++
if (tasks.empty())
{                
    pthread_cond_wait(&mycv, &mymutex);
}
```

答案是不得不如此。因为可能某次操作系统唤醒 pthread_cond_wait 时 tasks.empty() 可能仍然为 true，言下之意就是操作系统可能会在一些情况下唤醒条件变量，即使没有其他线程向条件变量发送信号，等待此条件变量的线程也有可能会醒来。我们将条件变量的这种行为称之为 **虚假唤醒** （**spurious wakeup**）。因此将条件（判断 tasks.empty() 为 true）放在一个 while 循环中意味着光唤醒条件变量不行，还必须条件满足程序才能继续执行正常的逻辑。

这看起来这像是个 bug，但它在 Linux 系统中是实实在在存在的。为什么会存在虚假唤醒呢？一个原因是：**pthread_cond_wait** 是 futex 系统调用，属于阻塞型的系统调用，**当系统调用被信号中断的时候**，会返回 **﹣1**，并且把 errno 错误码置为 EINTR。很多这种系统调用为了防止被信号中断都会重启系统调用（即再次调用一次这个函数），代码如下：

```c++
pid_t r_wait(int *stat_loc)
{
    int retval;
    //wait 函数因为被信号中断导致调用失败会返回 ﹣1，错误码是 EINTR  
    //注意：这里的 while 循环体是一条空语句
    while(((retval = wait(stat_loc)) == -1 && (errno == EINTR));

    return retval;
}
```

但是 **pthread_cond_wait** 用途有点不一样，假设 **pthread_cond_wait** 函数被信号中断了，在 **pthread_cond_wait** 返回之后，到重新调用之前，**pthread_cond_signal** 或 **pthread_cond_broadcast** 可能已经调用过。一旦错失，可能由于条件信号不再产生，再次调用 **pthread_cond_wait** 将导致程序无限制地等待下去。为了避免这种情况，宁可虚假唤醒，也不能再次调用 **pthread_cond_wait**，以免陷入无穷的等待中。

**<u>*除了上面的信号因素外，还存在以下情况*</u>**：条件满足了发送信号，但等到调用 **pthread_cond_wait** 的线程得到 CPU 资源时，条件又再次不满足了。$\color{pink} {pthread_cond_broadcast广播信号，一个线程把条件改变了，另一个线程在操作时条件就不满足了。}$

好在无论是哪种情况，醒来之后再次测试条件是否满足就可以解决虚假等待的问题。**这就是使用 while 循环来判断条件，而不是使用 if 语句的原因。**

### 条件变量信号丢失问题

上文中，我们介绍了，如果一个条件变量信号条件产生时（调用 **pthread_cond_signal** 或 **pthread_cond_broadcast**），没有相关的线程调用 **pthread_cond_wait** 捕获该信号，那么该信号条件就会永久性地丢失了，再次调用 **pthread_cond_wait** 会导致永久性的阻塞。这种情况在设计那些条件变量信号条件只会产生一次的逻辑中尤其需要注意，例如假设现在某个程序有一批等待条件变量的线程，和一个只产生一次条件变量信号的线程。为了让你的等待条件变量的线程能正常运行不阻塞，你的逻辑中，**一定要确保等待的线程在产生条件变量信号的线程发送条件信号之前调用 pthread_cond_wait 。**

> 这和生活中的很多例子一样，即许多事情你只有一次机会，必须提前准备好再去尝试这次机会，这个机会不会等待你的准备，一旦错过，就不会再有第二次机会了。

### 总结

本节介绍了学习 Linux 条件变量需要掌握的重难点知识，条件变量是最常用的一种多线程编程同步技术之一，也是面试高频问题之一，建议打算从事相关工作的读者**务必**理解和熟练使用它。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 17.Linux 线程同步之读写锁

在实际应用中，很多时候对共享变量的访问有以下特点：

> 大多数情况下线程只是读取共享变量的值，并不修改，只有在极少数情况下，线程才会真正地修改共享变量的值。

对于这种情况，读请求之间是无需同步的，它们之间的并发访问是安全的。然而写请求必须锁住读请求和其他写请求。

这种情况在实际中是存在的，如读取一个全局对象的状态属性，大多数情况下这个状态属性值是不会变化的，偶尔才会出现被修改的情况。如果使用互斥量，完全阻止读请求并发，则会造成性能的损失。

### 读写锁使用方法

读写锁在 Linux 系统中使用类型 **pthread_rwlock_t** 表示，读写锁的初始化和销毁使用如下系统 API 函数：

```c++
#include <pthread.h>

int pthread_rwlock_init(pthread_rwlock_t* rwlock, const pthread_rwlockattr_t* attr);
int pthread_rwlock_destroy(pthread_rwlock_t* rwlock);
```

参数 **rwlock** 即需要初始化和销毁的读写锁对象的地址，参数 **attr** 用于设置读写锁的属性，一般设置未 NULL 表示使用默认属性。函数调用成功返回 0，调用失败返回非 0 值，你可以通过检测错误码 **errno** 获取错误原因。

当然，如果你不需要动态创建或者设置非默认属性的读写锁对象，也可以使用如下语法初始化一个读写锁对象：

```c++
pthread_rwlock_t myrwlock = PTHREAD_RWLOCK_INITIALIZER;
```

下面是三个请求读锁的系统 API 接口：

```c++
int pthread_rwlock_rdlock(pthread_rwlock_t* rwlock);
int pthread_rwlock_tryrdlock(pthread_rwlock_t* rwlock);
int pthread_rwlock_timedrdlock(pthread_rwlock_t* rwlock, const struct timespec* abstime);
```

而下面三个请求写锁的系统 API 接口：

```c++
int pthread_rwlock_wrlock(pthread_rwlock_t* rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t* rwlock);
int pthread_rwlock_timedwrlock(pthread_rwlock_t* rwlock, const struct timespec* abstime);
```

**读锁用于共享模式**：

- 如果当前读写锁已经被某线程以**读模式**占有了，其他线程调用 **pthread_rwlock_rdlock** （请求读锁）会立刻获得读锁；
- 如果当前读写锁已经被某线程以**读模式**占有了，其他线程调用 **pthread_rwlock_wrlock** （请求写锁）会陷入**阻塞**。

**写锁用的是独占模式**：

- 如果当前读写锁被某线程以**写模式**占有，无论调用 **pthread_rwlock_rdlock** 还是 **pthread_rwlock_wrlock** 都会陷入**阻塞**，即写模式下不允许任何**读锁**请求通过，也不允许任何**写锁**请求通过，读锁请求和写锁请求都要陷入阻塞，直到线程释放写锁。

可以将上述读写锁逻辑总结成如下表格：

| 锁当前状态/其他线程请求锁类型 | 请求读锁 | 请求写锁 |
| :---------------------------: | :------: | :------: |
|             无锁              |   通过   |   通过   |
|         已经获得读锁          |   通过   |   阻止   |
|         已经获得写锁          |   阻止   |   阻止   |

无论是读锁还是写锁，锁的释放都是一个接口：

```c++
int pthread_rwlock_unlock (pthread_rwlock_t* rwlock);
```

无论是请求读锁还是写锁，都提供了 trylock 的功能（**pthread_rwlock_tryrdlock** 和 **pthread_rwlock_trywrlock**），调用线程不会阻塞，而会立即返回。如果能成功获得读锁或者写锁，函数返回 0，如果不能获得读锁或写锁时，函数返回非 0 值，此时错误码 errno 是 **EBUSY**。

当然，**无论是请求读锁还是写锁都提供了限时等待功能**，如果不能获取读写锁，则会陷入阻塞，最多等待到参数 **abstime** 设置的时间；如果仍然无法获得锁，则返回，错误码 errno 是 **ETIMEOUT**。

### 读写锁的属性

上文介绍 **pthread_rwlock_init** 函数时，提到其第二个参数可以设置读写锁的属性，读写锁的属性类型是 **pthread_rwlockattr_t** ，glibc 引入了如下接口来查询和改变读写锁的类型：

```c++
#include <pthread.h>

int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t* attr, int pref);
int pthread_rwlockattr_getkind_np(const pthread_rwlockattr_t* attr, int* pref);
```

**pthread_rwlockattr_setkind_np** 的第二个参数 **pref** 即设置读写锁的类型，其取值有如下几种：

```c++
enum
{
    //读者优先（即同时请求读锁和写锁时，请求读锁的线程优先获得锁）
    PTHREAD_RWLOCK_PREFER_READER_NP, 
    //不要被名字所迷惑，也是读者优先
    PTHREAD_RWLOCK_PREFER_WRITER_NP, 
    //写者优先（即同时请求读锁和写锁时，请求写锁的线程优先获得锁）
    PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,                 
    PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};
```

当然，为了得到一个有效的 **pthread_rwlockattr_t** 对象，你需要调用 **pthread_rwlockattr_init** 函数初始化这样一个属性对象，在你不需要的时候记得使用 **pthread_rwlockattr_destroy** 销毁之：

```c++
int pthread_rwlockattr_init(pthread_rwlockattr_t* attr);
int pthread_rwlockattr_destroy(pthread_rwlockattr_t* attr);
```

以下代码片段演示了如何初始化一个写者优先的读写锁：

```c
pthread_rwlockattr_t attr;
pthread_rwlockattr_init(&attr);
pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
pthread_rwlock_t rwlock;
pthread_rwlock_init(&rwlock, &attr);
```

### 读写锁使用示例

```c++
#include <pthread.h>
#include <unistd.h>
#include <iostream>

int resourceID = 0;
pthread_rwlock_t myrwlock;

void* read_thread(void* param)
{    
    while (true)
    {
        //请求读锁
        pthread_rwlock_rdlock(&myrwlock);

        std::cout << "read thread ID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;

        //使用睡眠模拟读线程读的过程消耗了很久的时间
        sleep(1);

        pthread_rwlock_unlock(&myrwlock);
    }

    return NULL;
}

void* write_thread(void* param)
{
    while (true)
    {
        //请求写锁
        pthread_rwlock_wrlock(&myrwlock);

        ++resourceID;
        std::cout << "write thread ID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;

        //使用睡眠模拟读线程读的过程消耗了很久的时间
        sleep(1);

        pthread_rwlock_unlock(&myrwlock);
    }

    return NULL;
}

int main()
{
    pthread_rwlock_init(&myrwlock, NULL);

    //创建5个请求读锁线程
    pthread_t readThreadID[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&readThreadID[i], NULL, read_thread, NULL);
    }

    //创建一个请求写锁线程
    pthread_t writeThreadID;
    pthread_create(&writeThreadID, NULL, write_thread, NULL);

    pthread_join(writeThreadID, NULL);

    for (int i = 0; i < 5; ++i)
    {
        pthread_join(readThreadID[i], NULL);
    }

    pthread_rwlock_destroy(&myrwlock);

    return 0;
}
```

上述程序中创建五个请求读锁的“读”线程和一个请求写锁的“写”线程，共享的资源是一个整形变量 **resourceID**，我们编译并执行得到输出结果：

```bash
[root@localhost testmultithread]# g++ -g -o rwlock rwlock.cpp -lpthread
[root@localhost testmultithread]# ./rwlock
read thread ID: 140575861593856, resourceID: 0
read thread ID: 140575878379264, resourceID: 0
read thread ID: 140575853201152, resourceID: 0
read thread ID: 140575869986560, resourceID: 0
read thread ID: 140575886771968, resourceID: 0
read thread ID: read thread ID: read thread ID: read thread ID: 140575861593856140575886771968, resourceID: 0, resourceID: 
0
140575878379264read thread ID: 140575869986560, resourceID: 0
, resourceID: 0
140575853201152, resourceID: 0
read thread ID: read thread ID: read thread ID: 140575861593856140575853201152140575886771968, resourceID: , resourceID: 0, resourceID: 00


read thread ID: 140575869986560, resourceID: 0
...更多输出结果省略...
```

上述输出结果，我们验证了两个结论：

- **由于读写锁对象 myrwlock 使用了默认属性，其行为是请求读锁的线程优先获得到锁**，请求写锁的线程 **write_thread** 很难获得锁的机会，因此结果中基本没有请求写锁线程的输出结果；
- 由于多个请求读锁的线程 **read_thread** 可以自由获得读锁，且代码 **15** 行（std::cout << "read thread ID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;）的输出不是原子性的，因而多个“读”线程的输出可能会交替，出现“错乱”现象。

我们将读写锁对象 **myrwlock** 的属性修改成请求写锁优先，再来试一试：

```c++
#include <pthread.h>
#include <unistd.h>
#include <iostream>

int resourceID = 0;
pthread_rwlock_t myrwlock;

void* read_thread(void* param)
{    
    while (true)
    {
        //请求读锁
        pthread_rwlock_rdlock(&myrwlock);

        std::cout << "read thread ID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;

        //使用睡眠模拟读线程读的过程消耗了很久的时间
        sleep(1);

        pthread_rwlock_unlock(&myrwlock);
    }

    return NULL;
}

void* write_thread(void* param)
{
    while (true)
    {
        //请求写锁
        pthread_rwlock_wrlock(&myrwlock);

        ++resourceID;
        std::cout << "write thread ID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;

        //使用睡眠模拟读线程读的过程消耗了很久的时间
        sleep(1);

        pthread_rwlock_unlock(&myrwlock);
    }

    return NULL;
}

int main()
{
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);
    //设置成请求写锁优先
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    pthread_rwlock_init(&myrwlock, &attr);

    //创建5个请求读锁线程
    pthread_t readThreadID[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&readThreadID[i], NULL, read_thread, NULL);
    }

    //创建一个请求写锁线程
    pthread_t writeThreadID;
    pthread_create(&writeThreadID, NULL, write_thread, NULL);

    pthread_join(writeThreadID, NULL);

    for (int i = 0; i < 5; ++i)
    {
        pthread_join(readThreadID[i], NULL);
    }

    pthread_rwlock_destroy(&myrwlock);

    return 0;
}
```

编译程序并运行，输出结果如下：

```bash
[root@localhost testmultithread]# g++ -g -o rwlock2 rwlock2.cpp -lpthread
[root@localhost testmultithread]# ./rwlock2
read thread ID: 140122217539328, resourceID: 0
read thread ID: 140122242717440, resourceID: 0
read thread ID: 140122209146624, resourceID: 0
write thread ID: 140122200753920, resourceID: 1
read thread ID: 140122234324736, resourceID: 1
write thread ID: 140122200753920, resourceID: 2
write thread ID: 140122200753920, resourceID: 3
write thread ID: 140122200753920, resourceID: 4
write thread ID: 140122200753920, resourceID: 5
write thread ID: 140122200753920, resourceID: 6
write thread ID: 140122200753920, resourceID: 7
write thread ID: 140122200753920, resourceID: 8
write thread ID: 140122200753920, resourceID: 9
write thread ID: 140122200753920, resourceID: 10
write thread ID: 140122200753920, resourceID: 11
write thread ID: 140122200753920, resourceID: 12
write thread ID: 140122200753920, resourceID: 13
read thread ID: 140122217539328, resourceID: 13
write thread ID: 140122200753920, resourceID: 14
write thread ID: 140122200753920, resourceID: 15
write thread ID: 140122200753920, resourceID: 16
write thread ID: 140122200753920, resourceID: 17
write thread ID: 140122200753920, resourceID: 18
write thread ID: 140122200753920, resourceID: 19
write thread ID: 140122200753920, resourceID: 20
write thread ID: 140122200753920, resourceID: 21
write thread ID: 140122200753920, resourceID: 22
write thread ID: 140122200753920, resourceID: 23
...更多输出结果省略...
```

由于将 **myrwlock** 设置成请求写锁优先，上述结果中几乎都是 **write_thread** 的输出结果。

我们将 **write_thread** 中的 **37** 行 sleep 语句挪到 **39** 行后面，增加请求写锁线程的睡眠时间，再看看执行结果。

```c++
#include <pthread.h>
#include <unistd.h>
#include <iostream>

int resourceID = 0;
pthread_rwlock_t myrwlock;

void* read_thread(void* param)
{    
    while (true)
    {
        //请求读锁
        pthread_rwlock_rdlock(&myrwlock);

        std::cout << "read thread ID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;

        //使用睡眠模拟读线程读的过程消耗了很久的时间
        sleep(1);

        pthread_rwlock_unlock(&myrwlock);
    }

    return NULL;
}

void* write_thread(void* param)
{
    while (true)
    {
        //请求写锁
        pthread_rwlock_wrlock(&myrwlock);

        ++resourceID;
        std::cout << "write thread ID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;

        pthread_rwlock_unlock(&myrwlock);

        //放在这里增加请求读锁线程获得锁的几率
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);
    //设置成请求写锁优先
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    pthread_rwlock_init(&myrwlock, &attr);

    //创建5个请求读锁线程
    pthread_t readThreadID[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&readThreadID[i], NULL, read_thread, NULL);
    }

    //创建一个请求写锁线程
    pthread_t writeThreadID;
    pthread_create(&writeThreadID, NULL, write_thread, NULL);

    pthread_join(writeThreadID, NULL);

    for (int i = 0; i < 5; ++i)
    {
        pthread_join(readThreadID[i], NULL);
    }

    pthread_rwlock_destroy(&myrwlock);

    return 0;
}
```

再次编译程序并执行，得到输出结果：

```bash
[root@localhost testmultithread]# g++ -g -o rwlock3 rwlock3.cpp -lpthread
[root@localhost testmultithread]# ./rwlock3
read thread ID: 140315524790016, resourceID: 0
read thread ID: 140315549968128, resourceID: 0
read thread ID: 140315541575424, resourceID: 0
write thread ID: 140315508004608, resourceID: 1
read thread ID: 140315549968128, resourceID: 1
read thread ID: 140315541575424, resourceID: 1
read thread ID: 140315524790016, resourceID: 1
read thread ID: 140315516397312, resourceID: 1
read thread ID: 140315533182720, resourceID: 1
write thread ID: 140315508004608, resourceID: 2
read thread ID: 140315541575424, resourceID: 2
read thread ID: 140315524790016, resourceID: 2
read thread ID: 140315533182720, resourceID: 2
read thread ID: 140315516397312, resourceID: 2
read thread ID: 140315549968128, resourceID: 2
read thread ID: 140315516397312, resourceID: 2
write thread ID: 140315508004608, resourceID: 3
read thread ID: 140315549968128, resourceID: 3
read thread ID: 140315541575424, resourceID: 3
read thread ID: 140315533182720, resourceID: 3read thread ID: read thread ID: 140315524790016, resourceID: 3
140315516397312, resourceID: 3

read thread ID: read thread ID: read thread ID: 140315524790016140315549968128, resourceID: , resourceID: 33
140315516397312, resourceID: 3
read thread ID: 140315541575424, resourceID: read thread ID: 140315533182720, resourceID: 3
3

write thread ID: 140315508004608, resourceID: 4
read thread ID: 140315516397312, resourceID: 4
read thread ID: 140315541575424, resourceID: 4
read thread ID: 140315524790016, resourceID: 4
read thread ID: 140315549968128, resourceID: 4
read thread ID: 140315533182720, resourceID: 4
read thread ID: 140315524790016, resourceID: 4
read thread ID: 140315541575424, resourceID: 4
write thread ID: 140315508004608, resourceID: 5
read thread ID: 140315516397312, resourceID: 5
read thread ID: 140315541575424, resourceID: 5
read thread ID: 140315524790016, resourceID: 5
read thread ID: 140315533182720, resourceID: 5
read thread ID: 140315549968128, resourceID: 5
```

这次请求读锁的线程和请求写锁的线程的输出结果分布就比较均匀了。

以上例子比较简单，建议读者实际运行一下代码实验一下。

### 总结

mutex 多线程之间，无论线程对共享资源是读还是写一概加上锁，加锁期间，不允许其他线程进行任何操作，而读写锁允许多个线程的读操作，因此相对于 mutex 提高了效率， **这也是 boost::mutex 和 boost::shared_mutex 在 Linux 平台的实现原理，前者使用 mutex 实现，后者使用读写锁实现。**

**思考题**

建议读者尝试自己利用读写锁实现一下 boost::mutex 和 boost::shared_mutex。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 18.C++ 11/14/17 线程资源同步对象

在 C/C++ 语言中直接使用操作系统提供的多线程资源同步 API 虽然功能强大，但毕竟存在诸多限制，且同样的代码却不能同时兼容 Windows 和 Linux 两个平台；再者 C/C++ 这种传统语言的使用份额正在被 Java、Python、Go 等语言慢慢蚕食，很大一部分原因是 C/C++ 这门编程语言在一些功能上缺少“完备性”，如对线程同步技术的支持，而这些功能在像 Java、Python、Go 中是标配。

因此，C++ 11 标准新加入了很多现代语言标配的东西，其中线程资源同步对象就是其中很重要的一部分。本小节将讨论 C++ 11 标准中新增的用于线程同步的 **std::mutex** 和 **std::condition_variable** 对象的用法，有了它们我们就可以写出跨平台的多线程程序了。

### std::mutex 系列

关于 mutex 的基本概念上文已经介绍过了，这里不再赘述。

C++ 11/14/17 中提供了如下 mutex 系列类型：

| 互斥量                | 版本  | 作用                                             |
| :-------------------- | :---- | :----------------------------------------------- |
| mutex                 | C++11 | 最基本的互斥量                                   |
| timed_mutex           | C++11 | 有超时机制的互斥量                               |
| recursive_mutex       | C++11 | 可重入的互斥量                                   |
| recursive_timed_mutex | C++11 | 结合 timed_mutex 和 recursive_mutex 特点的互斥量 |
| shared_timed_mutex    | C++14 | 具有超时机制的可共享互斥量                       |
| shared_mutex          | C++17 | 共享的互斥量                                     |

这个系列的对象均提供了加锁（lock）、尝试加锁（trylock）和解锁（unlock）的方法，我们以 **std::mutex** 为例来看一段示例代码：

```c++
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

// protected by g_num_mutex
int g_num = 0;  
std::mutex g_num_mutex;

void slow_increment(int id) 
{
    for (int i = 0; i < 3; ++i) {
        g_num_mutex.lock();
        ++g_num;
        std::cout << id << " => " << g_num << std::endl;
        g_num_mutex.unlock();

        //sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    std::thread t1(slow_increment, 0);
    std::thread t2(slow_increment, 1);
    t1.join();
    t2.join();

    return 0;
}
```

上述代码中，创建了两个线程 **t1** 和 **t2**，在线程函数的 for 循环中调用 std::mutex.lock() 和 std::mutex.unlock() 对全局变量 **g_num** 进行保护。编译程序并输出结果如下：

```bash
[root@localhost testmultithread]# g++ -g -o mutex c11mutex.cpp -std=c++0x -lpthread
[root@localhost testmultithread]# ./mutex 
0 => 1
1 => 2
0 => 3
1 => 4
1 => 5
0 => 6
```

> 注意：如果你在 Linux 下编译和运行程序，在编译时需要链接 pthread 库，否则能够正常编译但是运行时程序会崩溃，崩溃原因：
>
> terminate called after throwing an instance of 'std::system_error'
>
> what(): Enable multithreading to use std::thread: Operation not permitted

为了避免死锁，**std::mutex.lock()** 和 **std::mutex::unlock()** 方法需要成对使用，但是如上文介绍的如果一个函数中有很多出口，而互斥体对象又是需要在整个函数作用域保护的资源，那么在编码时因为忘记在某个出口处调用 **std::mutex.unlock** 而造成死锁，上文中推荐使用利用 RAII 技术封装这两个接口，其实 C++ 11 标准也想到了整个问题，因为已经为我们提供了如下封装：

| 互斥量管理  | 版本  | 作用                   |
| :---------- | :---- | :--------------------- |
| lock_guard  | C++11 | 基于作用域的互斥量管理 |
| unique_lock | C++11 | 更加灵活的互斥量管理   |
| shared_lock | C++14 | 共享互斥量的管理       |
| scope_lock  | C++17 | 多互斥量避免死锁的管理 |

我们这里以 **std::lock_guard** 为例：

```c++
void func()
{
    std::lock_guard<std::mutex> guard(mymutex);
    //在这里放被保护的资源操作
}
```

mymutex 的类型是 `std::mutex`，在 **guard** 对象的构造函数中，会自动调用 mymutex.lock() 方法加锁，当该函数出了作用域后，调用 **guard** 对象时析构函数时会自动调用 mymutex.unlock() 方法解锁。

注意： **mymutex 生命周期必须长于函数 func 的作用域**，很多人在初学这个利用 RAII 技术封装的 std::lock_guard 对象时，可能会写出这样的代码：

```c++
//错误的写法，这样是没法在多线程调用该函数时保护指定的数据的
void func()
{
    std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    //在这里放被保护的资源操作
}
```

### std::mutex 重复加锁问题

另外，如果一个 std::mutex 对象已经调用了 **lock()** 方法，再次调用时，其行为是未定义的，这是一个错误的做法。所谓“行为未定义”即在不同平台上可能会有不同的行为。

```c++
#include <mutex>

int main()
{
    std::mutex m;
    m.lock();
    m.lock();
    m.unlock();

    return 0;
}
```

实际测试时，上述代码重复调用 **std::mutex.lock()** 方法在 Windows 平台上会引起程序崩溃。如下图所示：

![img](image/e000e6e0-cfb0-11e9-b39a-29174b9d5834)

上述代码在 Linux 系统上运行时会阻塞在第二次调用 std::mutex.lock() 处，验证结果如下：

```bash
[root@localhost testmultithread]# g++ -g -o mutexlock mutexlock.cpp -std=c++0x -lpthread
[root@localhost testmultithread]# gdb mutexlock
Reading symbols from /root/testmultithread/mutexlock...done.
(gdb) r
Starting program: /root/testmultithread/mutexlock 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
^C
Program received signal SIGINT, Interrupt.
0x00007ffff7bcd4ed in __lll_lock_wait () from /lib64/libpthread.so.0
Missing separate debuginfos, use: debuginfo-install glibc-2.17-260.el7.x86_64 libgcc-4.8.5-36.el7.x86_64 libstdc++-4.8.5-36.el7.x86_64
(gdb) bt
#0  0x00007ffff7bcd4ed in __lll_lock_wait () from /lib64/libpthread.so.0
#1  0x00007ffff7bc8dcb in _L_lock_883 () from /lib64/libpthread.so.0
#2  0x00007ffff7bc8c98 in pthread_mutex_lock () from /lib64/libpthread.so.0
#3  0x00000000004006f7 in __gthread_mutex_lock (__mutex=0x7fffffffe3e0)
    at /usr/include/c++/4.8.2/x86_64-redhat-linux/bits/gthr-default.h:748
#4  0x00000000004007a2 in std::mutex::lock (this=0x7fffffffe3e0) at /usr/include/c++/4.8.2/mutex:134
#5  0x0000000000400777 in main () at mutexlock.cpp:7
(gdb) f 5
#5  0x0000000000400777 in main () at mutexlock.cpp:7
7        m.lock();
(gdb) l
2    
3    int main()
4    {
5        std::mutex m;
6        m.lock();
7        m.lock();
8        m.unlock();
9    
10        return 0;
11    }
(gdb)
```

我们使用 gdb 运行程序，然后使用 bt 命令看到程序确实阻塞在第二个 m.lock() 的地方（代码第 **7** 行）。

不管怎样，对一个已经调用 lock() 方法再次调用 lock() 方法的做法是错误的，我们实际开发中要避免这么做。

> 有不少开发者诟病 C++ 新标准的多线程库原因之一是 C++ 11 引入了 std::mutex，却到 **C++ 17 才引入 std::shared_mutex**，这给使用带来了非常不方便的地方。

### std::condition_variable

C++ 11 提供了 **std::condition_variable** 这个类代表条件变量，与 Linux 系统原生的条件变量一样，同时提供了等待条件变量满足的 **wait** 系列方法（wait、wait_for、wait_until 方法），发送条件信号使用 **notify** 方法（**notify_one** 和 **notify_all** 方法），当然使用 **std::condition_variable** 对象时需要绑定一个 **std::unique_lock** 或 **std::lock_guard** 对象。

> C++ 11 中 std::condition_variable 不再需要显式调用方法初始化和销毁。

我们将上文中介绍 Linux 条件变量的例子改写成 C++ 11 版本：

```c++
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <iostream>

class Task
{
public:
    Task(int taskID)
    {
        this->taskID = taskID;
    }

    void doTask()
    {
        std::cout << "handle a task, taskID: " << taskID << ", threadID: " << std::this_thread::get_id() << std::endl; 
    }

private:
    int taskID;
};

std::mutex                mymutex;
std::list<Task*>          tasks;
std::condition_variable   mycv;

void* consumer_thread()
{    
    Task* pTask = NULL;
    while (true)
    {
        std::unique_lock<std::mutex> guard(mymutex);
        while (tasks.empty())
        {               
            //如果获得了互斥锁，但是条件不合适的话，pthread_cond_wait会释放锁，不往下执行
            //当发生变化后，条件合适，pthread_cond_wait将直接获得锁
            mycv.wait(guard);
        }

        pTask = tasks.front();
        tasks.pop_front();

        if (pTask == NULL)
            continue;

        pTask->doTask();
        delete pTask;
        pTask = NULL;       
    }

    return NULL;
}

void* producer_thread()
{
    int taskID = 0;
    Task* pTask = NULL;

    while (true)
    {
        pTask = new Task(taskID);

        //使用括号减小guard锁的作用范围
        {
            std::lock_guard<std::mutex> guard(mymutex);
            tasks.push_back(pTask);
            std::cout << "produce a task, taskID: " << taskID << ", threadID: " << std::this_thread::get_id() << std::endl; 
        }

        //释放信号量，通知消费者线程
        mycv.notify_one();

        taskID ++;

        //休眠1秒
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return NULL;
}

int main()
{
    //创建5个消费者线程
    std::thread consumer1(consumer_thread);
    std::thread consumer2(consumer_thread);
    std::thread consumer3(consumer_thread);
    std::thread consumer4(consumer_thread);
    std::thread consumer5(consumer_thread);

    //创建一个生产者线程
    std::thread producer(producer_thread);

    producer.join();
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
    consumer5.join();

    return 0;
}
```

编译并执行程序输出结果如下所示：

```bash
[root@localhost testmultithread]# g++ -g -o cpp11cv cpp11cv.cpp -std=c++0x -lpthread
[root@localhost testmultithread]# ./cpp11cv 
produce a task, taskID: 0, threadID: 140427590100736
handle a task, taskID: 0, threadID: 140427623671552
produce a task, taskID: 1, threadID: 140427590100736
handle a task, taskID: 1, threadID: 140427632064256
produce a task, taskID: 2, threadID: 140427590100736
handle a task, taskID: 2, threadID: 140427615278848
produce a task, taskID: 3, threadID: 140427590100736
handle a task, taskID: 3, threadID: 140427606886144
produce a task, taskID: 4, threadID: 140427590100736
handle a task, taskID: 4, threadID: 140427598493440
produce a task, taskID: 5, threadID: 140427590100736
handle a task, taskID: 5, threadID: 140427623671552
produce a task, taskID: 6, threadID: 140427590100736
handle a task, taskID: 6, threadID: 140427632064256
produce a task, taskID: 7, threadID: 140427590100736
handle a task, taskID: 7, threadID: 140427615278848
produce a task, taskID: 8, threadID: 140427590100736
handle a task, taskID: 8, threadID: 140427606886144
produce a task, taskID: 9, threadID: 140427590100736
handle a task, taskID: 9, threadID: 140427598493440
...更多输出结果省略...
```

> 需要注意的是，如果在 Linux 平台上，std::condition_variable 也存在虚假唤醒这一现象，如何避免与上文中介绍 Linux 原生的条件变量方法一样。

### 总结

除了 std::mutex、std::condition_variable 类，C++ 11/14/17 还同步引入的其他一些多线程资源同步辅助类，如 std::lock_guard、std::unique_lock 等，它们被加入 C++ 语言中极大地方便了 C++ 的跨平台开发。当然，读者一定要明白，这些引入的对象其实就是前面章节介绍的 mutex、条件变量等操作系统平台的多线程资源同步 API 的封装。

> 从笔者自身的开发经历来说，自从有了 std::mutex、std::condition_variable 等对象，我在项目中大量使用他们，很少再使用操作系统本身提供的多线程资源同步 API 了，它们也在各种开源 C++ 项目中广泛使用。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。

## 19.如何确保创建的线程一定运行起来

在本章开头的小节里面我们介绍了如何创建线程，但是很少有人会注意到创建的线程如何确保一定运行起来了？很多人会说，对于使用系统 API 创建的线程，只需要判断一下创建的线程函数是否是调用成功的，这只做了一步，线程函数调用成功，也没法百分百保证线程函数一定运行起来了。

在一些“古老”或者“严谨”的项目中，你会发现这些代码创建线程时不仅判断线程创建函数是否调用成功，还会在线程函数中利用上文介绍的一些线程同步对象来通知线程的创建者线程是否创建成功。我们来看一段这样的代码：

```c++
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

std::mutex                 mymutex;
std::condition_variable mycv;
bool success = false;

void thread_func()
{
    {
        std::unique_lock<std::mutex> lock(mymutex);
        success = true;
        mycv.notify_all();
    }

    //实际的线程执行的工作代码放在下面
    //这里为了模拟方便，简单地写个死循环
    while (true)
    {

    }
}

int main()
{
    std::thread t(thread_func);

    //使用花括号减小锁的粒度
    {
        std::unique_lock<std::mutex> lock(mymutex);
        while (!success)
        {
            mycv.wait(lock);
        }
    }

    std::cout << "start thread successfully." << std::endl;

    t.join();

    return 0;
}
```

上述代码，发出一个创建新线程的请求后，立刻阻塞在一个条件变量上，工作线程如果成功运行起来，会发送条件变量信号告知主线程，这样主线程就知道新线程一定成功运行起来了。

基于以上思路，我们创建一组线程时，可以一个个地创建，每成功运行一个新线程再创建下一个，确保线程组中的每一个线程都可以运行起来。示例代码如下：

```c++
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <vector>
#include <memory>

std::mutex                 mymutex;
std::condition_variable mycv;
bool success = false;

void thread_func(int no)
{
    {
        std::unique_lock<std::mutex> lock(mymutex);
        success = true;
        mycv.notify_all();
    }

    std::cout << "worker thread started, threadNO: " << no << std::endl;
    //实际的线程执行的工作代码放在下面
    //这里为了模拟方便，简单地写个死循环
    while (true)
    {

    }
}

int main()
{
    std::vector<std::shared_ptr<std::thread>> threads;

    for (int i = 0; i < 5; ++i)
    {
        success = false;
        std::shared_ptr<std::thread> spthread;
        spthread.reset(new std::thread(thread_func, i));

        //使用花括号减小锁的粒度
        {
            std::unique_lock<std::mutex> lock(mymutex);
            while (!success)
            {
                mycv.wait(lock);
            }
        }

        std::cout << "start thread successfully， index: " << i << std::endl;

        threads.push_back(spthread);
    }

    for (auto& iter : threads)
    {
        iter->join();
    }

    return 0;
}
```

编译上述程序并运行，运行结果如下所示：

```bash
[root@myaliyun codes]# g++ -g -o makesurethreadgroup makesurethreadgroup.cpp -std=c++0x -lpthread
[root@myaliyun codes]# ./makesurethreadgroup 
worker thread started, threadNO: 0
start thread successfully， index: 0
worker thread started, threadNO: 1
start thread successfully， index: 1
worker thread started, threadNO: 2
start thread successfully， index: 2
worker thread started, threadNO: 3
start thread successfully， index: 3
worker thread started, threadNO: 4
start thread successfully， index: 4
```

可以看到，新线程挨个运行起来。当然，你不一定要使用条件变量，也可以使用其他类型的线程同步对象，如 Windows 平台的 Event 对象等。

> 按照行文逻辑，这一节应该放在创建线程那一节介绍，但是由于这里使用到了线程同步对象，因而这里的内容移到了介绍完各种线程资源同步对象之后来介绍。

### 小结

不知道读者注意到没有，我在介绍上述说的确保线程一定运行起来的做法时使用了两个词——“古老”和“严谨”，“严谨”不用多介绍，之所以说“古老”是因为你现在在各种新型的项目中基本上再也看不到这种确保线程运行起来的做法了，许多年以前多线程编程开始流行起来的时候，那时由于软硬件的水平限制，加之很多开发人员对多线程编程技术的不熟悉，创建新线程时确保一个线程跑起来非常必要；而如今多线程编程已经如此的司空见惯，加上操作系统和 CPU 普遍对多线程技术的支持，我们再也不用写这样的“防御“代码了；甚至只要你正确使用线程创建函数，我们实际编码时连线程函数的返回值都不必判断，基本上可以认为新线程一定会创建成功，且线程可以正常跑起来。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。

## 20.锁使用实践经验总结

关于锁的使用，根据我的经验总结如下几点。

### 减少锁的使用

实际开发中能不使用锁尽量不使用锁，当然这不是绝对的，如果使用锁也能满足性能要求，使用也无妨，一般使用了锁的代码会带来如下性能损失：

- 加锁和解锁操作，本身有一定的开销；
- 临界区的代码不能并发执行；
- 进入临界区的次数过于频繁，线程之间对临界区的争夺太过激烈，若线程竞争互斥量失败，就会陷入阻塞，让出 CPU，因此执行上下文切换的次数要远远多于不使用互斥量的版本。

替代锁的方式有很多，如无锁队列。

### 明确锁的范围

看下面这段代码：

```c++
if(hashtable.is_empty())
{
    pthread_mutex_lock(&mutex);
    htable_insert(hashtable, &elem);
    pthread_mutex_unlock(&mutex);
}
```

读者能看出这段代码的问题吗？代码行 **4** 虽然对 **hashtable** 的插入使用了锁做保护，但是判断 **hash_table** 是否为空也需要使用锁保护，因此正确的写法应该是：

```c++
pthread_mutex_lock(&mutex);
if(hashtable.is_empty())
{   
    htable_insert(hashtable, &elem);  
}
pthread_mutex_unlock(&mutex);
```

### 减少锁的粒度

所谓减小锁使用粒度指的是**尽量减小锁作用的临界区代码范围**，临界区的代码范围越小，多个线程排队进入临界区的时间就会越短。这就类似高速公路上堵车，如果堵车的路段越长，那么后续过来的车辆通行等待时间就会越长。

我们来看两个具体的例子：

**示例一**

```c++
void TaskPool::addTask(Task* task)
{
    std::lock_guard<std::mutex> guard(m_mutexList); 
    std::shared_ptr<Task> spTask;
    spTask.reset(task);            
    m_taskList.push_back(spTask);

    m_cv.notify_one();
}
```

上述代码中 **guard** 锁保护 **m_taskList**，仔细分析下这段代码发现，代码行 **4**、**5** 和 **8** 行其实没必要作为临界区内的代码的，因此建议挪到临界区外面去，修改如下：

```c++
void TaskPool::addTask(Task* task)
{
    std::shared_ptr<Task> spTask;
    spTask.reset(task);

    {
        std::lock_guard<std::mutex> guard(m_mutexList);             
        m_taskList.push_back(spTask);
    }

    m_cv.notify_one();
}
```

修改之后，**guard** 锁的作用范围就是 **7** 、**8** 两行了，仅对 **m_taskList.push_back()** 操作做保护，这样锁的粒度就变小了。

**示例二**

```c++
void EventLoop::doPendingFunctors()
{
    std::unique_lock<std::mutex> lock(mutex_);
    for (size_t i = 0; i < pendingFunctors_.size(); ++i)
    {
        pendingFunctors_[i]();
    }
}
```

上述代码中 **pendingFunctors_** 是被锁保护的对象，它的类型是 **`std::vector<Functor>`**，这样的代码效率比较低，必须等当前线程挨个处理完 **pendingFunctors_** 中的元素后其他线程才能操作 **pendingFunctors_** 。修改代码如下：

```c++
void EventLoop::doPendingFunctors()
{
    std::vector<Functor> functors;

    {
        std::unique_lock<std::mutex> lock(mutex_);
        functors.swap(pendingFunctors_);
    }

    for (size_t i = 0; i < functors.size(); ++i)
    {
        functors[i]();
    }   
}
```

修改之后的代码使用了一个局部变量 **functors**，然后把 **pendingFunctors_** 中的内容**倒换**到 **functors** 中，这样就可以释放锁了，允许其他线程操作 **pendingFunctors_** ，现在只要继续操作本地对象 **functors** 就可以了，提高了效率。

### 避免死锁的一些建议

- **一个函数中，如果有一个加锁操作，那么一定要记得在函数退出时记得解锁，且每个退出路径上都不要忘记解锁路径**。例如：

```c++
  void some_func()
  {
      //加锁代码

      if (条件1)
      {
          //其他代码
          //解锁代码
          return;
      } 
      else
      {
          //其他代码
          //解锁代码
          return;
      }


      if (条件2)
      {
          if (条件3)
          {
              //其他代码
              //解锁代码
              return;
          }

          if (条件4)
          {
              //其他代码
              //解锁代码
              return;
          }   
      } 

      while (条件5)
      {
          if (条件6)
          {
              //其他代码
              //解锁代码
              return;
          }
      }
  }
```

上述函数中每个逻辑出口处都需要写上解锁代码。前面也说过，这种逻辑非常容易因为疏忽忘记在某个地方加上解锁代码而造成死锁，因此一般建议使用 RAII 技术将加锁和解锁代码封装起来。

- **线程退出时一定要及时释放其持有的锁**

实际开发中会因一些特殊需求创建一些临时线程，这些线程执行完相应的任务后就会退出。对于这类线程，如果其持有了锁，一定记得在线程退出时记得释放其持有的锁对象。

- **多线程请求锁的方向要一致，以避免死锁**

假设现在有两个锁 A 和 B，线程 1 在请求了锁 A 之后再请求 B，线程 2 在请求了锁 B 后再请求锁 A，这种线程请求锁的方向就不一致了，线程 1 的方向是从 A 到 B，线程 2 的方向是从 B 到 A，多个线程请求锁的方向不一致容易造成死锁。因此建议的方式是线程 1 和 线程 2 请求锁的方向保持一致，要么都从 A 到 B，要么都从 B 到 A。

- **当需要同一个线程重复请求一个锁时，搞清楚你所使用的锁的行为，是递增锁引用计数，还是会阻塞抑或是直接获得锁？**

### 避免活锁的一些建议

前面说了避免“死锁”，读者应该能理解，但是这里突然出现了避免“活锁”，我相信很多人看到这个标题一下子就懵了。<u>**所谓活锁就是**，当多个线程使用 **trylock** 系列的函数时，由于多个线程相互谦让，导致即使在某段时间内锁资源是可用的，也可能导致需要锁的线程拿不到锁。</u>举个生活中的例子，马路上两个人迎面走来，两个人同时往一个方向避让，原来本意是给对方让路，结果还是发生了碰撞。

我们在实际编码时，尽量避免不要过多的线程使用 **trylock** 请求锁，以免出现“活锁”现象，这是对资源的一种浪费。

### 总结

从第 08 节到 第 17 节我们介绍 Windows 和 Linux 操作系统 API 层面上的各种常用多线程同步对象，本节是对它们的使用做了一个规范性和效率性总结。学会使用锁并不难，如何高效地使用它们则是一个不断积累不断总结的过程，希望本节的经验能对读者有帮助。同时，本节介绍锁的注意事项也适用于其他编程语言。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



# 第三部分: 线程池

## 21.线程局部存储

对于一个存在多个线程的进程来说，有时候我们需要有一份数据是每个线程都拥有的，**也就是说每个线程自己操作自己的这份数据**，<u>这有点类似 C++ 类的实例属性，每个实例对象操作的都是自己的属性</u>。我们把这样的数据称之为**线程局部存储**（**Thread Local Storage**，**TLS**），对应的存储区域叫做**线程局部存储区**。

### Windows 的线程局部存储

Windows 系统将线程局部存储区分成 **TLS_MINIMUM_AVAILABLE** 个块，每一块通过一个索引值对外提供访问。

> **TLS_MINIMUM_AVAILABLE** 的默认是 64。在 winnt.h 中定义：
>
> `#` define TLS_MINIMUM_AVAILABLE 64

![enter image description here](image/20d1d970-cfb3-11e9-a376-c52061de3e6e)

Windows 中使用函数 **TlsAlloc** 获得一个线程局部存储块的索引：

```c++
DWORD TlsAlloc();
```

如果这个函数调用失败，则返回值是 **TLS_OUT_OF_INDEXES**（0xFFFFFFFF）；如果函数调用成功，得到一个索引，接下来就可以利用这个索引去往这个内存块中存储数据或者从这个内存块中得到数据，分别使用如下两个 API 函数：

```c++
LPVOID TlsGetValue(DWORD dwTlsIndex);
BOOL TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue);
```

当你不再需要这个存储区域时，你应该释放它，释放调用函数：

```c++
BOOL TlsFree(DWORD dwTlsIndex);
```

当然，使用线程局部存储除了使用上面介绍的 API 函数外，Microsoft VC++ 编译器还提供了如下方法定义一个线程局部变量：

```c++
__declspec(thread) int g_mydata = 1;
```

我们看一个具体例子：

```c++
#include <Windows.h>
#include <iostream>

__declspec(thread) int g_mydata = 1;

DWORD __stdcall WorkerThreadProc1(LPVOID lpThreadParameter)
{
    while (true)
    {
        ++g_mydata;
        //std::cout << "g_mydata = " << g_mydata << ", ThreadID = " << GetCurrentThreadId() << std::endl;
        Sleep(1000);
    }
    return 0;
}

DWORD __stdcall WorkerThreadProc2(LPVOID lpThreadParameter)
{
    while (true)
    {       
        std::cout << "g_mydata = " << g_mydata << ", ThreadID = " << GetCurrentThreadId() << std::endl;
        Sleep(1000);
    }
    return 0;
}

int main()
{
    HANDLE hWorkerThreads[2];
    hWorkerThreads[0] = CreateThread(NULL, 0, WorkerThreadProc1, NULL, 0, NULL);
    hWorkerThreads[1] = CreateThread(NULL, 0, WorkerThreadProc2, NULL, 0, NULL);

    CloseHandle(hWorkerThreads[0]);
    CloseHandle(hWorkerThreads[1]);

    while (true)
    {
        Sleep(1000);
    }

    return 0;
}
```

上述代码中全局变量 **g_mydata** 是一个线程局部变量，因此该进程中每一个线程都会拥有这样一个变量副本，由于是不同的副本，**WorkerThreadProc1** 中将这个变量不断递增，对 **WorkerThreadProc2** 的 **g_mydata** 不会造成任何影响，因此其值始终是 **1**。程序执行结果如下：

![enter image description here](image/9c390930-cfb3-11e9-a227-638143eb6e37)

> 需要说明的是，在 Windows 系统中被声明成线程局部变量的对象，在编译器生成可执行文件时，会在最终的 PE 文件中专门生成一个叫 **tls 的节，这个节用于存放这些线程局部变量。**

### Linux 的线程局部存储

Linux 系统上的 NTPL 提供了一套函数接口来实现线程局部存储的功能：

```c++
int pthread_key_create(pthread_key_t* key, void (*destructor)(void*));
int pthread_key_delete(pthread_key_t key);

int pthread_setspecific(pthread_key_t key, const void* value);
void* pthread_getspecific(pthread_key_t key);
```

**pthread_key_create** 函数调用成功会返回 0 值，调用失败返回非 0 值，函数调用成功**会为线程局部存储创建一个新键**，用户通过参数 **key** 去设置（调用 **pthread_setspecific**）和获取（**pthread_getspecific**）数据，因为进程中的所有线程都可以使用返回的键，所以参数 **key** 应该指向一个全局变量。

参数 **destructor** 是一个自定义函数指针，其签名是：

```c++
void* destructor(void* value)
{
    /*多是为了释放 value 指针指向的资源*/
}
```

$\color{cyan} {线程终止时，如果 key 关联的值不是 NULL，那么 NTPL 会自动执行定义的 destructor 函数；如果无须解构，可以将 destructor 设置为 NULL。}$

我们来看一个具体例子：

```c++
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//线程局部存储 key
pthread_key_t thread_log_key;

void write_to_thread_log(const char* message)
{
    if (message == NULL)
        return;

    FILE* logfile = (FILE*)pthread_getspecific(thread_log_key);
    fprintf(logfile, "%s\n", message);
    fflush(logfile);
} 

void close_thread_log(void* logfile)
{
    char logfilename[128];
    sprintf(logfilename, "close logfile: thread%ld.log\n", (unsigned long)pthread_self());
    printf(logfilename);

    fclose((FILE *)logfile);
} 

void* thread_function(void* args)
{
    char logfilename[128];
    sprintf(logfilename, "thread%ld.log", (unsigned long)pthread_self());

    FILE* logfile = fopen(logfilename, "w");
    if (logfile != NULL)
    {
        pthread_setspecific(thread_log_key, logfile);

        write_to_thread_log("Thread starting...");
    }

    return NULL;
} 

int main()
{
    pthread_t threadIDs[5]; 
    pthread_key_create(&thread_log_key, close_thread_log);
    for(int i = 0; i < 5; ++i)
    {
        pthread_create(&threadIDs[i], NULL, thread_function, NULL);
    }

    for(int i = 0; i < 5; ++i)
    {
        pthread_join(threadIDs[i], NULL);
    }

    return 0;
}
```

上述程序一共创建 5 个线程，每个线程都会自己生成一个日志文件，每个线程将自己的日志写入自己的文件中，当线程执行结束时，会关闭打开的日志文件句柄。

程序运行结果如下：

![enter image description here](image/c940e600-cfb3-11e9-a376-c52061de3e6e)

生成的 5 个日志文件中，其内容都写入了一行“Thread starting…”。

上面的程序首先调用 pthread_key_create 函数来申请一个槽位。**在 NPTL 实现下，pthread_key_t 是无符号整型，pthread_key_create 调用成功时会将一个小于 1024 的值填入第一个入参指向的 pthread_key_t 类型的变量中。之所以小于 1024，是因为 NPTL 实现一共提供了 1024 个槽位。**

如图所示，记录槽位分配情况的数据结构 **pthread_keys** 是进程唯一的，pthread_keys 结构示意图如下：

![enter image description here](image/3409ef40-cfb4-11e9-8219-7158466f1e22)

和 Windows 一样 Linux gcc 编译器也提供了一个关键字 **__thread** 去简化定义线程局部变量。例如：

```c++
__thread int val = 0;
```

我们再来看一个示例：

```c++
#include <pthread.h>
#include <iostream>
#include <unistd.h>

//线程局部存储 key
__thread int g_mydata = 99;

void* thread_function1(void* args)
{
    while (true)
    {
        g_mydata ++;
    }

    return NULL;
} 

void* thread_function2(void* args)
{
    while (true)
    {       
        std::cout << "g_mydata = " << g_mydata << ", ThreadID: " << pthread_self() << std::endl;
        sleep(1);
    }

    return NULL;
} 

int main()
{
    pthread_t threadIDs[2]; 
    pthread_create(&threadIDs[0], NULL, thread_function1, NULL);
    pthread_create(&threadIDs[1], NULL, thread_function2, NULL);

    for(int i = 0; i < 2; ++i)
    {
        pthread_join(threadIDs[i], NULL);
    }

    return 0;
}
```

由于 **thread_function1** 修改的是自己的 **g_mydata**，因此 **thread_function2** 输出 **g_mydata** 的值始终是 **99**。

```bash
[root@localhost testmultithread]# g++ -g -o linuxtls2 linuxtls2.cpp -lpthread
[root@localhost testmultithread]# ./linuxtls2
g_mydata = 99, ThreadID: 140243186276096
g_mydata = 99, ThreadID: 140243186276096
g_mydata = 99, ThreadID: 140243186276096
g_mydata = 99, ThreadID: 140243186276096
g_mydata = 99, ThreadID: 140243186276096
g_mydata = 99, ThreadID: 140243186276096
g_mydata = 99, ThreadID: 140243186276096
g_mydata = 99, ThreadID: 140243186276096
g_mydata = 99, ThreadID: 140243186276096
g_mydata = 99, ThreadID: 140243186276096
g_mydata = 99, ThreadID: 140243186276096
...更多输出结果省略...
```

### C++ 11 的 thread_local 关键字

C++ 11 标准提供了一个新的关键字 **thread_local** 来定义一个线程变量。使用方法如下：

```c++
thread_local int g_mydata = 1;
```

**有了这个关键字，使用线程局部存储的代码同时在 Windows 和 Linux 运行了**。示例如下：

```c++
#include <thread>
#include <chrono>
#include <iostream>

thread_local int g_mydata = 1;

void thread_func1()
{
    while (true)
    {
        ++g_mydata;
    }
}

void thread_func2()
{
    while (true)
    {
        std::cout << "g_mydata = " << g_mydata << ", ThreadID = " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    std::thread t1(thread_func1);
    std::thread t2(thread_func2);

    t1.join();
    t2.join();

    return 0;
}
```

需要注意的是，如果读者是在 Windows 平台下，虽然 **thread_local** 关键字在 C++ 11 标准中引入，但是 Visual Studio 2013 （支持 C++ 11 语法的最低的一个版本）编译器却并不支持这个关键字，建议在 Visual Studio 2015 及以上版本中测试上述代码。

### 总结

最后关于线程局部存储变量，我还再强调两点：

- $\color{cyan} {对于线程变量，每个线程都会有该变量的一个拷贝，并行不悖，互不干扰，该局部变量一直都在，直到线程退出为止；}$
- $\color{orange} {系统的线程局部存储区域内存空间并不大，因此尽量不要利用这个空间存储大的数据块，如果不得不使用大的数据块，可以将大的数据块存储在堆内存中，再将该堆内存的地址指针存储在线程局部存储区域。}$

**思考题**

线程局部存储变量存储在进程地址空间的何处呢？答案可以在对应的课程微信群中获得。

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 22.C 库的非线程安全函数

我们先来看一段代码：

```c++
#include <time.h>

int main()
{
    time_t tNow = time(NULL);
    time_t tEnd = tNow + 1800;
    //注意下面两行的区别
    struct tm* ptm = localtime(&tNow);
    struct tm* ptmEnd = localtime(&tEnd);

    char szTmp[50] = { 0 };
    strftime(szTmp, 50, "%H:%M:%S", ptm);

    //struct tm* ptmEnd = localtime(&tEnd);
    char szEnd[50] = { 0 };
    strftime(szEnd, 50, "%H:%M:%S", ptmEnd);
    printf("%s \n", szTmp);
    printf("%s \n", szEnd);

    return 0;
}
```

程序执行结果如下图所示：

```c++
20:53:48
20:53:48
```

很奇怪是不是？**tNow** 和 **tEnd** 明明相差 1800 秒。我们调整一下代码第 **9** 行的位置：

```c++
#include <time.h>

int main()
{
    time_t tNow = time(NULL);
    time_t tEnd = tNow + 1800;
    //注意下面两行的区别
    struct tm* ptm = localtime(&tNow);    

    char szTmp[50] = { 0 };
    strftime(szTmp, 50, "%H:%M:%S", ptm);

    struct tm* ptmEnd = localtime(&tEnd);
    char szEnd[50] = { 0 };
    strftime(szEnd, 50, "%H:%M:%S", ptmEnd);
    printf("%s \n", szTmp);
    printf("%s \n", szEnd);

    return 0;
}
```

这次输出结果正确了：

```c
20:25:44
20:55:44
```

为什么会出现这种情况呢？我们来看下 **localtime** 函数的签名：

```c
struct tm* localtime(const time_t* timep);
```

这个函数返回值一个 **tm** 结构体指针类型，而我们外部并不需要释放这个指针指向的内存，**因此断定这个函数内部一定使用了一个全局变量或函数内部的静态变量**。这样的话，当再次调用这个函数时有可能前一次调用结果就被后一个结果覆盖了。**我们简化一下这种模型：**

```c++
int* func(int k)
{
    static int result;
    result = k;
    return &result;
}
```

当多个线程甚至单个线程调用这个函数时，如两个线程分别调用上述函数：

```c++
//线程1调用
int* p1 = func(1);
//线程2调用
int* p2 = func(2);
```

那么 * **p1** 和 * **p2** 的结果会是什么呢？结论是可能是 1 也可能是 2，甚至既不是 1 也不是 2。原因我们在前面《**为什么整形变量赋值操作不是原子》**的小节已经介绍过了。

像 **localtime** 这类 CRT 提供的具有上述行为的函数，我们称为**非线程安全函数**。因此在实际开发中应避免在多线程程序中使用这类函数，这类函数还有如 **strtok**，<u>甚至连操作系统提供的 socket 函数 **gethostbyname** 也不是线程安全的。</u>

```c++
char* strtok(char* str, const char* delim);

struct hostent* gethostbyname(const char* name);
```

为什么会出现这类函数呢？是因为最初编写很多 CRT 函数时，还没有多线程技术，所以很多函数内部实现都使用了函数内部的静态变量和全局变量。随着多线程技术的出现，很多函数出现了对应的多线程安全版本，如 **localtime_r**、**strtok_r**。<u>*在这些函数内部很多改用了**线程局部存储** 技术来**替代**原来使用**静态变量或者全局变量**的做法。*</u>

**因此，在实际开发中如果一个 CRT 函数可能被多个线程调用，要注意其是否是多线程安全函数，如果不是多线程安全的，要改用其线程安全的版本。**

[点击这里下载课程源代码](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)。



## 23.线程池与队列系统的设计

在很多新手的认知中，**线程池**和**队列系统** 是一项非常高深的技术，其实也不然，当你熟练掌握了多线程编程技术后，这一切将会变的很容易，你需要克服的是内心的恐惧而已。

### 线程池的设计原理

所谓**线程池**不过是一组线程而已，一般情况下，我们需要异步执行一些任务，这些任务的产生和执行是存在于我们程序的整个生命周期的，**与其让操作系统频繁地为我们创建和销毁线程，通常需要创建一组在程序生命周期内不会退出的线程，为了不浪费系统资源，**我们的基本要求是当有任务需要执行时，这些线程可以自动拿到任务去执行，没有任务时这些线程处于阻塞或者睡眠状态。这里就涉及到这些处理任务的**工作线程的唤醒与睡眠**，如果理解了上文中介绍的各种线程同步技术，相信现在对如何唤醒和睡眠线程已经很熟悉了。





# 第四部分: 协程

## 24.纤程的概念和用法





## 25.协程技术与总结













