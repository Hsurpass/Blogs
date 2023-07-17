# 目录


- [目录](#目录)
- [C](#c)
  - [补码运算](#补码运算)
    - [负数求补码](#负数求补码)
    - [负数的补码求原码](#负数的补码求原码)
  - [编译过程](#编译过程)
  - [指针](#指针)
  - [stdarg.h](#stdargh)
    - [可变参函数](#可变参函数)
    - [可变参宏](#可变参宏)
  - [string.h](#stringh)
    - [memchr](#memchr)
  
  



# C

## 补码运算

整数的原码、反码、补码都是其二进制的本身。 0的补码是0。

### 负数求补码

1. 第一种方法：原码求反码，反码加1

```bash
# -5的原码：5的原码+最高位置1：			1000 0101
# -5的反码：原码的最高位不变+其余位置1：	 1111 1010
# -5的补码：反码+1：				   1111	1011			
```

2. 负数的绝对值的原码，取反，加1

```bash
# 5的原码：	0000 0101
# 取反：	 1111 1010
# 加1：	  1111 1011
```

3. 模 -（负数）

```bash
# 8位二进制的模是256(2^8)， 256-5 = 251 -->1111 1011
```



### 负数的补码求原码

补码求原：==取反加1 + 最高位置1==  （补码的补码就是原码  负负得正）

```bash
# -5补码：1111 1011 ->(取反) 0000 0100 ->(加1) 0000 0101 ->(因为是负数最高位补1) 1000 0101
```



## 编译过程

预处理->编译->汇编->链接

```bash
g++ -E hello.cpp -o hello.i
g++ -S hello.cpp -o hello.s
g++ -c hello.cpp -o hello.o
g++ hello.o -o hello
```

编译静态库：

```bash
gcc -c xx.c -o xx.o	#将.c文件编译成.o
ar rc libxx.a xx.o 	#将.o打包成.a
```

编译动态库：

```bash
gcc -c xx.c -o xx.o  # 将.c文件编译成.o
gcc -shared -fPIC -o libxx.so xx.o # 将.o打包成.so
```

[gcc_g++.md](./linuxBasic/gcc_g++.md)

## 指针

悬挂指针：当指针所指向的对象被释放，但是该指针没有任何改变，以至于其仍然指向已经被回收的内存地址，这种情况下该指针被称为悬挂指针。

野指针：未初始化的指针被称为野指针。可能指向任意地址。

### 二级指针

作用：改变一级指针的指向。

```c
int a;
int *p = &a;
int b;
int **pp = &p;
*pp = &b;

void func(int **p)
{
    *p = new int(9);
}
```

二级指针和指针数组等价。



## stdarg.h

### 可变参函数

[variable_parameter_function.c](https://github.com/Hsurpass/ElegantTest/blob/main/test_cpp/1C_library/cstdarg/variable_parameter_function.c)

### 可变参宏

```c++
// 宏定义的参数允许用"...", 表示是可变参数，在宏替换的时候用__VA_ARGS__表示"..."位置的所有参数
#define test1(...) printf(__VA_ARGS__)
#define test2(fmt, ...) printf(fmt, __VA_ARGS__)

// 很多编译器扩展了可变参数的宏替换，这样的写法更容易记忆，
// 宏定义的参数后面可以带三个小数点，表示这里是可变参数，
// 宏替换的时候，直接写这个参数就表示这个位置是所有的可变参数了。
// 注：某些编译器需要用 ##args 表示 args... 位置所有的参数的宏替换。
#define test3(fmt...) printf(fmt)
#define test4(fmt, args...) printf(fmt, args)
```

[variable_parameter_macro.c](https://github.com/Hsurpass/ElegantTest/blob/main/test_cpp/1C_library/cstdarg/variable_parameter_macro.c)

##__VA_ARGS__：宏前面加上##的作用在于，当可变参数的个数为 0 时，这里的##起到把前面多余的","去掉的作用,否则会编译出错,

C语言指针危险在哪？

​	指针可以自增，自减。++p, --p



## string.h

### memchr

```c
// 在ptr所指向的内存块的前num个字节内，搜索value第一次出现的位置。成功返回第一次出现的位置，失败返回NULL。
const void* memchr (const void * ptr, int value, size_t num );
      void* memchr (      void * ptr, int value, size_t num );
```



## stdlib.h

### calloc

```c
void* calloc (size_t num, size_t size);	// 自动分配num*size大小的的内存，并自动将内存清0
```

### realloc

```c
void* realloc (void* ptr, size_t size);	// 重新分配内存，且新分配的内存不会清0
```

1.   如果指定的地址后面**有连续的空间**，那么就会在已有地址基础上增加内存。
2.   指定的地址后面**没有空间**，那么realloc会重新分配**新的连续内存**，把旧内存的值**拷贝**到新内存，同时**释放**旧内存。

