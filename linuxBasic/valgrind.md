# Valgrind

valgrind的**优势**在于不需要重新编译，**缺点**在于<u>CPU和内存</u>开销大，而且程序的性能损耗较大(可损耗原程序的10~20倍)。建议使用debug版本的程序`g++ -g`。https://valgrind.org

valgrind是一个工具集，包括：memcheck、cachegrind、callgrind、helgrind、DRD。

常用选项：

-   --help：
-   --version
-   --tool=<toolname>：指定要使用的工具，如：memcheck(默认)，cachegrind，callgrind，helgrind。
-   --leak-check=no|summary|full：对发现的内存泄露给出的信息级别
-   --quiet：安静地运行，只打印错误信息
-   --verbose：更详细的信息，增加错误数统计。
-   --track-origins=<yes/no>：启用或禁用**跟踪内存分配的源**。如果设置为“yes”，则 Valgrind 将记录内存分配的来源，以便更容易地确定哪些代码负责内存分配。
-   --log-file=<filename>: 将输出**写入指定的文件**中，而不是在标准输出中显示。
-   --trace-children=no|yes。当使用该参数时，Valgrind会跟踪所有由被跟踪程序创建的**子进程和线程**，并对它们进行检查。
-   --track-fds=no | yes：跟踪打开的**文件描述符**。

## memcheck

其中**memcheck**可用于检测：

1. 内存泄漏。
2. 内存越界。
3. 使用未初始化的内存。
4. 使用已释放的内存。
5. 不匹配的内存分配和释放：new[]/delete、malloc/delete、new/free。

```bash
==2062== Memcheck, a memory error detector
==2062== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2062== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==2062== Command: ./a.out
==2062== 
==2062== 
==2062== HEAP SUMMARY:
==2062==     in use at exit: 4 bytes in 1 blocks
==2062==   total heap usage: 2 allocs, 1 frees, 72,708 bytes allocated
==2062== 
==2062== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==2062==    at 0x483BE63: operator new(unsigned long) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==2062==    by 0x10919E: main (test.cpp:9)
==2062== 
==2062== LEAK SUMMARY:
==2062==    definitely lost: 4 bytes in 1 blocks
==2062==    indirectly lost: 0 bytes in 0 blocks
==2062==      possibly lost: 0 bytes in 0 blocks
==2062==    still reachable: 0 bytes in 0 blocks
==2062==         suppressed: 0 bytes in 0 blocks
==2062== 
==2062== For lists of detected and suppressed errors, rerun with: -s
==2062== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

definitely lost：确认丢失。

[valgrind检查代码内存泄漏，5种内存泄漏情况](https://www.cnblogs.com/muahao/p/9105656.html)



## callgrind

Callgrind可以对程序进行函数级别的性能分析，帮助我们了解程序中哪些**函数占用**了**CPU时间**，从而进行性能优化。

## cachegrind

Cachegrind可以**模拟CPU缓存的工作情况**，帮助我们分析程序的缓存使用情况，从而优化程序的性能。

## helgrind

Helgrind可以检测出**多线程程序中的竞争问题**，例如死锁、数据竞争等。





# AddressSanitizer

https://github.com/google/sanitizers/wiki/AddressSanitizer

简称Asan，优势在于CPU开销小，程序性能损耗小(2倍左右)。缺点在于需要添加 `-fsanitize=address` 选项重新编译。

```bash
 #0 0x7f3b8ccbc587 in operator new(unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cc:104
    #1 0x564360c6125e in main /mnt/d/WorkSpace/tmp/test.cpp:9
    #2 0x7f3b8c693082 in __libc_start_main ../csu/libc-start.c:308

SUMMARY: AddressSanitizer: 4 byte(s) leaked in 1 allocation(s).
```



