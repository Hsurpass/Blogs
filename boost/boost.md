





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



# reference:

boost源码目录下的index.html就是全部文档，`boost_1_76_0\index.html`

1. https://mmoaay.gitbooks.io/boost-asio-cpp-network-programming-chinese/content/
2. https://ishare.iask.sina.com.cn/f/137GZAuLfBa.html
3. https://github.com/mmoaay/boost-asio-cpp-network-programming-in-chinese
4. https://m.w3cschool.cn/nlzbw/nlzbw-3vs825ya.html
5. [C++ Boost库：环形缓冲区 circular_buffer_超级大洋葱806的博客-CSDN博客_boost circular_buffer](https://tangxing.blog.csdn.net/article/details/116402317)

