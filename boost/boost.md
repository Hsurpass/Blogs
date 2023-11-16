





# boost/operators.hpp

## boost::less_than_comparable

只要实现 **operator<() const** 就可自动实现<=，>，>=。

less_than_comparable.cpp

## boost::equality_comparable

只要实现 **operator==() const** ，就能自动实现 operator !=() const

less_than_comparable.cpp

# boost/any.hpp

## boost::any

相对于 void* 的好处：

1. void*不是类型安全的。
2. 任意类型的类型安全存储以及安全的取回。
3. 在标准库容器中，存放不同类型的对象，比如说：vector< boost::any >。



# boost/asio.hpp



## strand

https://zhuanlan.zhihu.com/p/155792445?utm_medium=social&utm_oi=29671328579584&utm_source=zhihu



boost::post和boost::dispatch的区别

不同之处在于 `dispatch` 可能会在其中运行 `handler`(传递给它的 `CompletionHandler`)，这意味着您将等待它完成，如果是，则在函数返回之前。另一方面，`post` 本身不会运行 `handler` 并立即返回调用站点。

因此，`dispatch` 是一个**潜在的阻塞调用**，而 `post` 是一个非阻塞调用。

https://www.coder.work/article/1215186



一个io_service对象可以通过多个线程调用io_service.run进行事件处理器的并发。分发到不同的线程上执行的策略可以认为是随机的。

strand是线程安全的任务队列的封装，具体执行还是会调用io_service的接口进行处理。**一个io_service可以被多个strand绑定**。

因此strand的特性是保证同一个strand里面的任务是按序执行，任务执行的线程是根据io_server.run线程分配的，所以一个strand里面的任务执行的线程并不一定是同一个。

https://www.cnblogs.com/my_life/articles/8524407.html

https://www.cnblogs.com/chobits/p/5632225.html

https://cloud.tencent.com/developer/article/2290343?areaSource=102001.14&traceId=WI2n-20ESPP494XRA_kLW

https://zhuanlan.zhihu.com/p/49497613




# reference:

https://think-async.com/Asio/

[BOOST.ASIO源码剖析(二) ---- 架构浅析](https://www.cnblogs.com/yyzybb/p/3795428.html)


boost源码目录下的index.html就是全部文档，`boost_1_76_0\index.html`

1. https://mmoaay.gitbooks.io/boost-asio-cpp-network-programming-chinese/content/
2. https://ishare.iask.sina.com.cn/f/137GZAuLfBa.html
3. https://github.com/mmoaay/boost-asio-cpp-network-programming-in-chinese
4. https://m.w3cschool.cn/nlzbw/nlzbw-3vs825ya.html
5. [C++ Boost库：环形缓冲区 circular_buffer_超级大洋葱806的博客-CSDN博客_boost circular_buffer](https://tangxing.blog.csdn.net/article/details/116402317)

