### 编译流程：

- 1、预处理

  处理文件包含，宏和注释
  ```
	g++ -E hello.cpp -o hello.i
	```

- 2、编译

  编译为汇编文件

  ```
  g++ -S hello.i -o hello.s
  ```

- 3、汇编

  经汇编后成为二进制的机器指令

  ```
  g++ -c hello.s -o hello.o
  ```

- 4、链接

  ```
  g++ hello.o -o hello
  ```

### 编译参数：

**-g**: 产生可调试信息的可执行文件

**-O[n]**: 优化源代码

所谓优化，例如省略掉代码中从未使用过的变量、直接将常量表达式用结果值代替等等，这些操作会缩减目标文件所包含的代码量，提高最终生成的可执行文件的运行效率。

-O 选项告诉 g++ 对源代码进行基本优化。这些优化在大多数情况下都会使程序执行的更快。 -O2 选项告诉 g++ 产生尽可能小和尽可能快的代码。如-O2，-O3，-On（n 常为0–3）

   + -O 同时减小代码的长度和执行时间，其效果等价于-O1
   +  **-O0:** 表示不做优化
   +  **-O1:** 为默认优化
   +  **-O2:** 除了完成-O1的优化之外，还进行一些额外的调整工作，如指令调整等。
   +  **-O3:** 则包括循环展开和其他一些与处理特性相关的优化工作。选项将使编译的速度比使用 -O 时慢， 但通常产生的代码执行速度会更快。

**-l**: -l参数(小写)就是用来指定程序要链接的库，-l参数紧接着就是库名。在 */lib* 和 */usr/lib* 和 */usr/local/lib* 里的库直接用-l参数就能链接。

**-L**: 如果库文件没放在上面三个目录里，需要使用-L参数(大写)指定库文件所在目录。 -L参数跟着的是库文件所在的目录名

```
g++ -L/home/libfolder -ltest test.cpp
```

**-I**: 指定头文件搜索目录

​	/usr/include目录一般是不用指定的，gcc知道去那里找，但 是如果头文件不在/usr/icnclude里我们就要用-I参数指定了，比如头文件放在/myinclude目录里，那编译命令行就要加上-I/myinclude 参数了，如果不加你会得到一个”xxxx.h: No such file or directory”的错误。-I参数可以用相对路径，比如头文件在当前 目录，可以用-I.来指定。上面我们提到的–cflags参数就是用来生成-I参数的。

**-Wall**: 打印警告信息

**-w**: 关闭警告信息

**-std=c++11**: 设置编译标准

**-D**：定义宏

​	在使用gcc/g++编译的时候定义宏

​	常用场景：

​	-DDEBUG 定义DEBUG宏，可能文件中有DEBUG宏部分的相关信息，用个DDEBUG来选择开启或关闭DEBUG

```
#include <iostream>
using namespace std;

int main()
{
    #ifdef DEBUG
        cout << "DEBUG LOG" << endl;
    #endif

    #ifdef TEST
        cout << "TEST" << endl;
    #endif

    cout << "gcc_g++" << endl;

    return 0;
}
```

```
g++ -DDEBUG -DTEST test.cpp
./a.out ==> DEBUG LOG TEST gcc_g++
```

### 生成静态库和动态库：

生成静态库：

```
g++ -c hello.cpp -I. -o hello.o
ar rs libhello.a hello.o
archive resource

g++ main.cpp -I. -L. -lhello -o staticMain （静态库和动态库都存在时，优先加载动态库，可以使用 -static 指定加载静态库）
```

生成动态库：

```
g++ -fPIC -shared hello.cpp -I. -o libhello.so
等价于
g++ hello.cpp -I. -c -fPIC hello.o
g++ -shared -o libhello.so hello.o
PIC: positon independent code,不加fPIC编译出来的so,要再加载时根据加载到的位置再次重定位，导致无法共享。

g++ main.cpp -I. -L. -lhello -o sharedMain
```

链接动态库运行可执行文件：

+ 临时运行可执行文件

  ```
  1. LD_LIBRARY_PATH=src ./sharemain
  或
  2. export LD_LIBRARY_PATH = ./:$LD_LIBRARY_PATH
  ```

+ 可永久运行临时文件

  ```
  vim ~/.bashrc
  export LD_LIBRARY_PATH = ./:$LD_LIBRARY_PATH
  ```




```
gcc -c test.c -o test.o
查看二进制码：
objdump -t test.o
反推回函数：
c++filt _Z5printIiJiEEvRKT_DpRKT0_
```



编译选项:

![image-20220718073802113](image/image-20220718073802113.png)





**LIBRARY_PATH**：用于在程序**编译期间**查找动态链接库时指定查找共享库的路径。
**LD_LIBRARY_PATH**：用于在程序加载**运行期间**查找动态链接库时指定除了系统默认路径之外的其他路径。
**C_INCLUDE_PATH**: 指明c头文件的搜索路径。
**CPLUS_INCLUDE_PATH**:指明c++头文件的搜索路径。  

reference:

https://www.cnblogs.com/bigfi/p/9487427.html

https://blog.csdn.net/qq_34199383/article/details/80308782

