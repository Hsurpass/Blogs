# Valgrind

valgrind的**优势**在于不需要重新编译，**缺点**在于CPU开销大，而且程序的性能损耗较大(可损耗原程序的10~20倍)。https://valgrind.org

valgrind是一个工具集，包括：memcheck、。

其中**memcheck**可用于检测：

1. 内存泄漏。
2. 内存越界。
3. 使用释放后的内存。
4. 使用未初始化的变量。



# AddressSanitizer

https://github.com/google/sanitizers/wiki/AddressSanitizer

简称Asan，优势在于CPU开销小，程序性能损耗小(2倍左右)。缺点在于需要添加 `-fsanitize=address` 选项重新编译。



