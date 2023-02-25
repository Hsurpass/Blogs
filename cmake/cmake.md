#### references:

[CMake使用教程和原理](https://cloud.tencent.com/developer/article/1561162)



[使用ctest配置googletest](https://chunleili.github.io/cmake/ctest-googletest)

[彻底弄懂cmake中的 INTEFACE 可见性/传递性 问题](https://chunleili.github.io/cmake/understanding-INTERFACE)

[CMake菜谱（CMake Cookbook中文版）](https://www.bookstack.cn/books/CMake-Cookbook)



[Cmake之深入理解find_package()的用法](https://zhuanlan.zhihu.com/p/97369704)

[深入浅出CMake(三):find_package 添加依赖库](https://cloud.tencent.com/developer/article/1446788)

[cmake find_package路径详解](https://zhuanlan.zhihu.com/p/50829542)



[cmake入门](https://www.pudn.com/news/62ae93a7dfc5ee1968803a47.html)

[全网最细的CMake教程！(强烈建议收藏)](https://zhuanlan.zhihu.com/p/534439206)

[分享一篇很不错的CMake入门文章，值得收藏细读！](https://mp.weixin.qq.com/s?__biz=MzU5MzcyMjI4MA==&mid=2247494287&idx=1&sn=7f383549a1f2212b1cf33c192a4a1235&chksm=fe0e8448c9790d5ef72b36bb8d116730f29f86a9fe3c2a03ee5cbb0006b0a39e778ce7d81e47&scene=21#wechat_redirect)

[CMake 入门实战](https://www.hahack.com/codes/cmake/)

[cmake入门到精通资料大全](https://zhuanlan.zhihu.com/p/505300111)



## 构建

### 内部构建

```cmake
cmake .
make
```

### 外部构建

linux:

```cmake
mkdir build && cd build && cmake .. && make (同cmake --build . )

or

cmake -B build
cmake --build build --config Release  #生成可执行文件
```

windows:

```cmake
cmake -B build -G "Visual Studio 16 2019" 
cmake --build build --config Release  #生成可执行文件
```

注意：假如你在Windows下使用VS，那么**--config Release是必要的**。因为默认会进行Debug模式的构建。 **而且实际上VS会把所有的四种变体都生成，因此你在配置步骤指定CMAKE_BUILD_TYPE是没有用的！**



### 构建时传递参数

```cmake
cmake -DCMAKE_BUILD_TYPE=Debug
```



## 设置编译选项

```cmake
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
```



## 自定义编译选项(就是添加配置)



## 环境检查



## 生成库

##### LIBRARY_OUTPUT_PATH

设置库文件(动态库和静态库)输出目录：

```cmake
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib) 
```

##### add_library

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

类型有三种：

SHARED,动态库

STATIC,静态库

MODULE，在使用dyld的系统有效，如果不支持dyld，则被当做SHARED对待。

EXCLUDE_FROM_ALL参数的意思是这个不会被默认构建，除非有其他的组件依赖或者手工构建。

##### BUILD_SHARED_LIBS

这个开关用来控制默认的库编译方式，如果不进行设置，使用ADD_LIBRARY并没有指定库类型的情况下，默认编译生成的库都是静态库。

```cmake
SET(BUILD_SHARED_LIBS ON)	# 默认生成的为动态库。
```



### 生成静态库

##### CMAKE_ARCHIVE_OUTPUT_DIRECTORY

```cmake
# 静态库输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
```

```cmake
# 通过变量 hello.c 生成 libhello.a 静态库 (默认是静态库)
add_library(hello STATIC hello.c)
```

### 生成动态库

##### CMAKE_LIBRARY_OUTPUT_DIRECTORY

```cmake
# 动态库输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
```

==**cmake在windows平台链接动态库错误, error LNK1181(1104): 无法打开输入文件**==

```cmake
if(MSVC)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
  SET(BUILD_SHARED_LIBS TRUE)
endif()
```

```cmake
# 通过变量 hello.c 生成 libhello.so 共享库 (默认是静态库)
add_library(hello SHARED hello.c)
```

### 同时构建动态库和静态库

```cmake
// 如果⽤这种⽅式，只会构建⼀个动态库，不会构建出静态库，虽然静态库的后缀是.a
// 因为使用了这个语句，hello作为target是不能重名的。所以会造成静态库的构建指令无效。
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
ADD_LIBRARY(hello STATIC ${LIBHELLO_SRC})

// 修改静态库的名字，这样是可以的，但是我们往往希望他们的名字是相同的，只是后缀不同⽽已
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})
```

所以使用SET_TARGET_PROPERTIES添加一条：

```cmake
//对hello_static的重名为hello
SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")
```

可以使用GET_TARGET_PROPERTY获取目标属性：

```cmake
GET_TARGET_PROPERTY(OUTPUT_VALUE hello_static OUTPUT_NAME)
MESSAGE(STATUS "This is the hello_static OUTPUT_NAME:"${OUTPUT_VALUE})
```

如果没有这个属性则会返回**NOTFOUND**.而使用以上的例子会出现一个问题，那就是会发现libhello.a存在，但是libhello.so会消失，因为cmake在构建一个新的target时，会尝试清理掉其他使用这个名字的库。解决方案如下：

向CMakeLists.txt中添加：

```cmake
SET_TARGET_PROPERTIES(hello PROPERTIES CLEAN_DIRECT_PUTPUT 1)
SET_TARGET_PROPERTIES(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
```

最终方案：

```cmake
SET(LIBHELLO_SRC hello.cpp)
ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})
//对hello_static的重名为hello
SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")

//cmake 在构建⼀个新的target 时，会尝试清理掉其他使⽤这个名字的库，因为，在构建 libhello.so 时， 就
会清理掉 libhello.a
SET_TARGET_PROPERTIES(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
SET_TARGET_PROPERTIES(hello PROPERTIES OUTPUT_NAME "hello")
SET_TARGET_PROPERTIES(hello PROPERTIES CLEAN_DIRECT_OUTPUT 1)
```

### 添加动态库版本号

⼀般动态库都有⼀个版本号的关联

```c
libhello.so.1.2
libhello.so ->libhello.so.1
libhello.so.1->libhello.so.1.2
```

设置版本号:

```cmake
SET_TARGET_PROPERTIES(hello PROPERTIES VERION 1.2 SOVERSION 1)
#VERSION指代动态库版本，SOVERSION指代API版本。
```





## 生成可执行程序

##### EXECUTABLE_OUTPUT_PATH

设置可执行文件输出目录： 

```cmake
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
```

##### CMAKE_RUNTIME_OUTPUT_DIRECTORY

```cmake
# 可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
```





## 安装

#### INSTALL

##### TARGETS

执行INSTALL命令时需要注意**CMAKE_INSTALL_PREFIX**参数的值。INSTALL命令形式如下：

```cmake
INSTALL(TARGETS targets...
		[[ARCHIVE|LIBRARY|RUNTIME]
		 [DESTINATION <dir>]
		 [PERMISSIONS permissions...]
		 [CONFIGURATIONS [Debug|Release|...]]
		 [COMPONENT <component>]
		 [OPTIONAL]
		] [...]
		)
```

**参数TARGETS后跟目标是通过ADD_EXECUTABLE或者ADD_LIBRARY定义的目标文件，可能是可执行二进制、动态库、静态库。**

**DESTINATION**定义安装的路径，==如果路径以/开头，那么是绝对路径，此时CMAKE_INSTALL_PREFIX将
无效。== 如果希望使用**CMAKE_INSTALL_PREFIX**来定义安装路径，需要写成相对路径，即不要以/开头，安
装路径就是 **${CMAKE_INSTALL_PREFIX}/destination** 定义的路径
	==As absolute paths are not supported by [`cpack`](https://cmake.org/cmake/help/latest/manual/cpack.1.html#manual:cpack(1)) installer generators, it is preferable to use relative paths throughout.== In particular, there is no need to make paths absolute by prepending [`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX); this prefix is used by default if the DESTINATION is a relative path.

##### FILES|PROGRAMS

普通文件(*.h)和非目标文件的可执行程序安装(如**脚本**):

```cmake
INSTALL(<FILES|PROGRAMS> files... 
		TYPE <type> | DESTINATION <dir>
		[PERMISSIONS permissions...]
		[CONFIGURATIONS [Debug|Release|...]]
		[COMPONENT <component>]
		[RENAME <name>] [OPTIONAL] [EXCLUDE_FROM_ALL])
```

可用于安装一般文件，并可以指定访问权限，文件名是此指令所在路径下的相对路径。如果默认不定义**PERMISSIONS**，安装后的权限为：OWNER_WRITE，OWNER_READ，GROUP_READ和WORLD_READ，权限==644==。

非目标文件的可执行程序安装，如脚本之类的：安装后权限为：OWNER_EXECUTE，GROUP_EXECUTE和WORLD_EXECUTE，即==755==权限。

##### DIRECTORY

```cmake
install(DIRECTORY dirs...
        TYPE <type> | DESTINATION <dir>
        [FILE_PERMISSIONS permissions...]
        [DIRECTORY_PERMISSIONS permissions...]
        [USE_SOURCE_PERMISSIONS] [OPTIONAL] [MESSAGE_NEVER]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>] [EXCLUDE_FROM_ALL]
        [FILES_MATCHING]
        [[PATTERN <pattern> | REGEX <regex>]
         [EXCLUDE] [PERMISSIONS permissions...]] [...])
```

这里主要介绍其中的DIRECTORY、PATTERN、以及PERMISSIONS参数。

**DIRECTORY**后面连接的是所在Source目录的相对路径，当请**务必注意**：==abc和abc/有很大的区别。==

如果目录名不以/结尾，那么**这个目录**将被安装到目标路径下的abc，如果目录名以/结尾，代表将**这个目录中的内容**安装到目标路径，但不包括这个目录本身。

PATTERN用于使用正则表达式进行过滤，PERMISSIONS用于指定PATTERN过滤后的文件权限。

举例:

```cmake
install(DIRECTORY icons scripts/ DESTINATION share/myproj
        PATTERN "CVS" EXCLUDE
        PATTERN "scripts/*"
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                    GROUP_EXECUTE GROUP_READ)
```

这条指令的执行结果是：

将icons目录安装到<prefix>/share/myproj,将scripts/中的内容安装到<prefix>/share/myproj

**不包含目录名为CVS的目录**，对于scripts/*文件指定权限为OWNER_EXECUTE OWNER_WRITE WONER_READ GROUP_EXECUTE GROUP_READ.

##### 自定义安装逻辑

```cmake
install([[SCRIPT <file>] [CODE <code>]]
        [ALL_COMPONENTS | COMPONENT <component>]
        [EXCLUDE_FROM_ALL] [...])
```

SCRIPT参数用于在安装时调用cmake脚本文件（也就是<abc>.cmake文件）

CODE参数用于执行CMAKE指令，**必须以双引号括起来**。比如：

```cmake
install(CODE "MESSAGE(\"Sample install message.\")")
```

在安装的时候将会打印一条信息。





#### CMAKE_INSTALL_PREFIX

==/usr/local （默认安装路径）==

```cmake
# 设置安装路径
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/bin)
```

也可以通过-D CMAKE_INSTALL_PREFIX=xxx来从外部命令行传递。

## 测试

##### enable_testing()

```cmake
enable_testing()	#默认 测试是不开启的，需要调用开启
```

Enables testing for this directory and below.

This command should be in the source directory root because ctest expects to find a test file in the build directory root.

This command is automatically invoked when the [`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest) module is included, except if the **`BUILD_TESTING`** option is ==turned off.==

See also the [`add_test()`](https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test) command.

##### add_test

Add a test to the project to be run by [`ctest(1)`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1)).

```cmake
add_test(NAME <name> COMMAND <command> [<arg>...]
         [CONFIGURATIONS <config>...]
         [WORKING_DIRECTORY <dir>]
         [COMMAND_EXPAND_LISTS])
```

NAME:测试的名称

COMMAND: 指定测试要运行的命令及参数

​		<command>:测试要运行的命令

​		<arg>: 测试运行命令要用到的参数

CONFIGURATIONS：限制测试只对给定的配置执行

WORKING_DIRECTORY：执行测试的工作目录

COMMAND_EXPAND_LISTS：是否展开命令的参数

##### set_tests_properties

```cmake
set_tests_properties(test1 [test2...] PROPERTIES prop1 value1 prop2 value2)
```

设置测试的属性。如果测试没发现，cmake将会报错。

```cmake
#测试5的平方
add_test(NAME test_5_2 COMMAND demo5 5 2)
set_tests_properties(test_5_2 PROPERTIES PASS_REGULAR_EXPRESSION "is 25")
```

其中 **`PASS_REGULAR_EXPRESSION`** 用来测试输出是否包含后面跟着的字符串。



## 添加版本号

### <PROJECT-NAME>_VERSION_MAJOR

First version number component of the [`<PROJECT-NAME>_VERSION`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION.html#variable:_VERSION) variable as set by the [`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project) command.

```cmake
set (Demo_VERSION_MAJOR 1)	#指定当前的项目的主版本号
```

### <PROJECT-NAME>_VERSION_MINOR

Second version number component of the [`<PROJECT-NAME>_VERSION`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION.html#variable:_VERSION) variable as set by the [`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project) command.

```cmake
set (Demo_VERSION_MINOR 0)	# 指定当前的项目的副版本号
```

### <PROJECT-NAME>_VERSION_PATCH

Third version number component of the [`_VERSION`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION.html#variable:_VERSION) variable as set by the [`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project) command.

```cmake
set (Demo_VERSION_PATCH 0)	# 指定当前的项目的补丁号
```

之后，为了在代码中获取版本信息，我们可以修改 config.h.in 文件，添加两个预定义变量：

```c++
// the configured options and settings for Tutorial
#define Demo_VERSION_MAJOR @Demo_VERSION_MAJOR@
#define Demo_VERSION_MINOR @Demo_VERSION_MINOR@
```

cmake -B build && cmake --build build 。生成`config.h`

```c
// the configured options and settings for Tutorial
#define Demo7_VERSION_MAJOR 1
#define Demo7_VERSION_MINOR 0
```

这样就可以直接在代码中打印版本信息了：

```c
// print version info
printf("%s Version %d.%d\n", argv[0], Demo_VERSION_MAJOR, Demo_VERSION_MINOR);
```



## 生成安装包

1. CPack是安装CMake时集成安装的工具。

2. CPack只是个打包工具，你让它把啥打包，它就打包啥，你不告诉它，它就给你打个空包，或者报错。

3. CPack的打包流程是：

先在诸如“cmake-build-debug\_CPack_Packages\Linux\TGZ\Demo8-0.1.1-Linux”的文件夹下面安装一遍程序。

然后再对这个目录进行打包，所以...

​	3.1 **一定要在CMakeLists.txt中==写install==告诉脚本你要安装啥**

​	3.2 **写install的时候一定要写==相对路径==，==不然这个临时目录就是个空==**

```cmake
# 设置安装根目录
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
# 指定可执行程序和config.h安装路径
install(TARGETS demo8 DESTINATION bin)	# 一定要写相对路径，否则打的就是空包
install(FILES ${PROJECT_BINARY_DIR}/config.h DESTINATION include)
```

如何配置生成各种平台上的**安装包，包括二进制安装包和源码安装包。**为了完成这个任务，我们需要用到 **CPack** ，它同样也是由 CMake 提供的一个工具，专门用于打包。

首先在**顶层**的 CMakeLists.txt 文件尾部添加下面几行：

```cmake
# 构建一个 CPack 安装包
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
include (CPack)
```

上面的代码做了以下几个工作：

1. 导入 **InstallRequiredSystemLibraries** 模块( 该模块将包括当前平台项目所需的任何运行时库)，以便之后导入 CPack 模块；
2. 设置一些 CPack 相关变量，包括版权信息和版本信息，其中版本信息用了上一节定义的版本号；
3. 导入 CPack 模块。

==接下来的工作是像往常一样**构建工程**，**进入构建目录**，并执行 `cpack` 命令。==

- 生成二进制安装包：

```bash
cpack -C CPackConfig.cmake
```

- 生成源码安装包

```bash
cpack -C CPackSourceConfig.cmake
```

我们可以试一下。在生成项目后，执行 `cpack -C CPackConfig.cmake` 命令：

```bash
[ehome@xman Demo8]$ cpack -C CPackSourceConfig.cmake
CPack: Create package using STGZ
CPack: Install projects
CPack: - Run preinstall target for: Demo8
CPack: - Install project: Demo8
CPack: Create package
CPack: - package: /home/ehome/Documents/programming/C/power/Demo8/Demo8-1.0.1-Linux.sh generated.
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: Demo8
CPack: - Install project: Demo8
CPack: Create package
CPack: - package: /home/ehome/Documents/programming/C/power/Demo8/Demo8-1.0.1-Linux.tar.gz generated.
CPack: Create package using TZ
CPack: Install projects
CPack: - Run preinstall target for: Demo8
CPack: - Install project: Demo8
CPack: Create package
CPack: - package: /home/ehome/Documents/programming/C/power/Demo8/Demo8-1.0.1-Linux.tar.Z generated.
```

此时会在该目录下创建 3 个不同格式的二进制包文件：

```bash
[ehome@xman Demo8]$ ls Demo8-*
Demo8-1.0.1-Linux.sh  Demo8-1.0.1-Linux.tar.gz  Demo8-1.0.1-Linux.tar.Z
```

这 3 个二进制包文件所包含的内容是完全相同的。我们可以执行其中一个。此时会出现一个由 CPack 自动生成的交互式安装界面：

```bash
[ehome@xman Demo8]$ sh Demo8-1.0.1-Linux.sh 
Demo8 Installer Version: 1.0.1, Copyright (c) Humanity
This is a self-extracting archive.
The archive will be extracted to: /home/ehome/Documents/programming/C/power/Demo8

If you want to stop extracting, please press <ctrl-C>.
The MIT License (MIT)

Copyright (c) 2013 Joseph Pan(http://hahack.com)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


Do you accept the license? [yN]: 
y
By default the Demo8 will be installed in:
  "/home/ehome/Documents/programming/C/power/Demo8/Demo8-1.0.1-Linux"
Do you want to include the subdirectory Demo8-1.0.1-Linux?
Saying no will install in: "/home/ehome/Documents/programming/C/power/Demo8" [Yn]: 
y

Using target directory: /home/ehome/Documents/programming/C/power/Demo8/Demo8-1.0.1-Linux
Extracting, please wait...

Unpacking finished successfully
```

完成后提示安装到了 Demo8-1.0.1-Linux 子目录中，我们可以进去执行该程序：

```bash
[ehome@xman Demo8]$ ./Demo8-1.0.1-Linux/bin/Demo 5 2
Now we use our own Math library. 
5 ^ 2 is 25
```

关于 CPack 的更详细的用法可以通过 `man 1 cpack` 参考 CPack 的文档。

## 清理工程

可以使用make clean清理makefile产生的中间的文件，但是，不能使用make distclean清除cmake产生的中间件。如果需要删除cmake的中间件，可以采用rm -rf ***来删除中间件。



## CMAKE基础

### 1. 语法特性介绍

- **基本语法格式：指令(参数1 参数2…)**

  - 参数使用**括弧**括起
  - 参数之间使用**空格**或**分号**分开

- **指令是大小写无关的，参数和变量是大小写相关的**

  ```cmake
  set(HELLO hello.cpp)
  add_executable(hello main.cpp hello.cpp)
  ADD_EXECUTABLE(hello main.cpp ${HELLO})
  ```

- **变量使用${}方式取值，但是在 IF 控制语句中是直接使用变量名**

### 2. 重要指令和CMake常用变量

https://cmake.org/cmake/help/latest/      -----> search

#### 2.1 常用函数

##### cmake_minimum_required

指定CMake的最小版本要求

```cmake
cmake_minimum_required(VERSION <min>[...<policy_max>] [FATAL_ERROR])
```

```cmake
# CMake最小版本要求为2.8.3
cmake_minimum_required(VERSION 2.8.3)
```

##### project

定义工程名称，并可指定工程支持的语言

```cmake
project(projectname [CXX] [C] [Java])
```

```cmake
# 指定工程名为HELLOWORLD
project(HELLOWORLD)
```

##### set

set可以设置普通变量、缓存变量和环境变量

设置普通变量：

```cmake
set(<variable> <value>... [PARENT_SCOPE])
```

如果PARENT_SCOPE被设置，他的父级目录将可以访问子级目录的变量

设置缓存变量:

```cmake
set(<variable> <value>... CACHE <type> <docstring> [FORCE])
```

使用CACHE 将会把变量保存到CMakeCache.txt文件中，这样同级目录就能访问另一个目录中的变量

设置环境变量:

```cmake
set(ENV{<variable>} [<value>])
```

调用 `$ENV{<variable>}`返回设置的值

如果在ENV{<variable>}之后没写任何值，或者<value>是一个空字符串，那么这条命令将会清空这个环境变量所对应的值

##### include_directories

向工程添加多个特定的头文件搜索路径 ---> 相当于指定g++编译器的-I参数

```cmake
include_directories([AFTER|BEFORE] [SYSTEM] dir1 dir2 …)
```

  ```cmake
  # 将/usr/include/myincludefolder 和 ./include 添加到头文件搜索路径
  include_directories(/usr/include/myincludefolder ./include)
  ```

  这条指令可以用来向工程添加多个特定的头文件搜索路径，路径之间用空格分隔，可以使用双引号将它括起来，默认的行为是追加到当前的头文件搜索路径的后面，你可以通过两种方式来进行控制搜索路径添加的方式：

1. 通过SET这个cmake变量(**CMAKE_INCLUDE_DIRECTORIES_BEFORE**)为on，可以将添加的头文件搜索路径放在已有路径的前面。
2. 通过AFTER或者BEFOR参数，也可以控制是追加还是置前。

##### link_directories

向工程添加多个特定的库文件搜索路径  ---> 相当于指定g++编译器的-L参数

添加非标准的共享库搜索路径，比如在工程内部同时存在共享库和可执行二进制，在编译时就需要指定一下这些共享库的路径。

```cmake
link_directories([AFTER|BEFORE] directory1 [directory2 ...])
```

  ```cmake
  # 将/usr/lib/mylibfolder 和 ./lib 添加到库文件搜索路径
  link_directories(/usr/lib/mylibfolder ./lib)
  ```

##### add_executable

生成可执行文件

```cmake
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               [source1] [source2 ...])
```

  ```cmake
  # 编译main.cpp生成可执行文件main
  add_executable(main main.cpp)
  ```

##### target_link_libraries

为 target 添加需要链接的共享库  --->相同于指定g++编译器-l参数

```cmake
target_link_libraries(target library1 library2…)
```

  ```cmake
  # 将hello动态库文件链接到可执行文件main
  target_link_libraries(main hello)
  ```

##### add_subdirectory

```cmake
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL] [SYSTEM])
```

这个指令用于向当前工程添加存放源文件的子目录。并可以指定中间二进制和目标二进制存放的位置。**EXCLUDE_FROM_ALL**参数的含义是将这个目录从编译过程中排除，比如，工程中的example，可能就需要工程构建完成后，再进入example目录单独进行构建（当然，你可以通过定义依赖来解决此类问题）。

```cmake
add_subdirectory(example EXCLUDE_FROM_ALL)
```



##### set_target_properties

```cmake
set_target_properties(target1 target2 ...
                      PROPERTIES prop1 value1
                      prop2 value2 ...)
```

##### get_target_property

```cmake
get_target_property(<VAR> target property)
```



##### aux_source_directory

==发现一个目录下所有的源代码文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表==

```cmake
aux_source_directory(<dir> <variable>)
```

  ```cmake
  # 定义SRC变量，其值为当前目录下所有的源代码文件
  aux_source_directory(. SRC)
  # 编译SRC变量所代表的源代码文件，生成main可执行文件
  add_executable(main ${SRC})
  ```

  

##### find_package()



##### find_library()

###### CMAKE_LIBRARY_PATH



##### find_path()

###### CMAKE_INCLUDE_PATH



##### FIND_FILE



##### FIND_PROGRAM



##### macro

```cmake
macro(<name> [arg1 [arg2 [arg3 ...]]])
		COMMAND1(ARGS ...)
		COMMAND2(ARGS ...)
endmacro(<name>)
```





#### 2.2 CMake常用变量

##### ADD_DEFINITIONS

向C/C++编译器添加-D定义，比如：

`ADD_DEFINITIONS(-DENABLE_DEBUG -DABC)`，参数之间用空格分隔。如果你的代码中定义了

`#ifdef ENABLE_DEBUG #endif`，这个代码块就会生效。如果要添加其他的编译器开关，可以通过CMAKE_C_FLAGS变量和CMAKE_CXX_FLAGS变量设置。

##### CMAKE_C_FLAGS  

**gcc编译选项**, 也可以通过指令ADD_DEFINITIONS()添加。

##### CMAKE_CXX_FLAGS  

**g++编译选项**,也可以通过指令ADD_DEFINITIONS()添加。

```cmake
# 在CMAKE_CXX_FLAGS编译选项后追加-std=c++11
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-elide-constructors")
```

##### CMAKE_C_COMPILER

```cmake
-DCMAKE_C_COMPILER #指定C语言编译器如交叉编译器未加入到环境变量，需要使用绝对路径
```

##### CMAKE_CXX_COMPILER

指定C++编译器



##### CMAKE_BUILD_TYPE

**编译类型(Debug, Release)**

```cmake
# 设定编译类型为debug，调试时需要选择debug
set(CMAKE_BUILD_TYPE Debug) 
# 设定编译类型为release，发布时需要选择release
set(CMAKE_BUILD_TYPE Release) 
```

##### CMAKE_CXX_STANDARD

```cmake
# 设置c++11标准
set(CMAKE_CXX_STANDARD 11)
```



##### CMAKE_CXX_STANDARD_REQUIRED

```cmake
# 需要满足c++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```



##### CMAKE_CXX_EXTENSIONS

```cmake
# 不用c++扩展语法
set(CMAKE_CXX_EXTENSIONS OFF
```



##### CMAKE_BINARY_DIR

##### PROJECT_BINARY_DIR

##### “projectname”__BINARY_DIR

1. 这三个变量指代的内容是一致的。
2. 如果是 in source build，指的就是工程顶层目录。
3. 如果是 out-of-source 编译,指的是工程编译发生的目录。
4. PROJECT_BINARY_DIR 跟其他指令稍有区别，不过现在，你可以理解为他们是一致的。

##### CMAKE_SOURCE_DIR

##### PROJECT_SOURCE_DIR
##### "projectname"_SOURCE_DIR

1. 这三个变量指代的内容是一致的,不论采用何种编译方式,都是工程顶层目录。

2. 也就是在 in source build时,他跟 CMAKE_BINARY_DIR 等变量一致。

3. PROJECT_SOURCE_DIR 跟其他指令稍有区别,现在,你可以理解为他们是一致的。

##### CMAKE_CURRENT_SOURCE_DIR

##### CMAKE_CURRENT_BINARY_DIR



##### CMAKE_CURRENT_LIST_DIR

1. ${CMAKE_CURRENT_LIST_DIR}代表当前的CMakeLists.txt文件所在的**绝对路径**。

##### CMAKE_CURRENT_LIST_LINE

输出这个变量所在的行

##### CMAKE_MODULE_PATH

这个变量用来定义自己的cmake模块所在的路径。如果你的工程比较复杂，有可能会自己编写一些cmake模块，这些cmake模块是随你的工程发布的，为了让cmake在处理CMakeLists.txt时找到这些模块，你需要通过SET指令，将自己的cmake模块路径设置一下。

```cmake
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
```

这个时候你就可以通过INCLUDE指令来调用自己的模块。

##### CMAKE_INCLUDE_CURRENT_DIR 

自动将当前源代码和构建目录添加到include路径。默认是OFF

如果启用此变量，CMake会自动将**CMAKE_CURRENT_SOURCE_DIR**和CMAKE_CURRENT_BINARY_DIR添加到每个目录的包含路径中。这些附加包含目录不会向下传播到子目录。这主要对外部构建有用，生成到构建树(build目录)中的文件包含在源树(main目录)中的文件中。

```cmake
set(CMAKE_INCLUDE_CURRENT_DIR ON)
```

---------------

##### 系统信息

###### CMAKE_MAKOR_VERSION

CMAKE的主版本号，比如2.4.6中的2

###### CMAKE_MINOR_VERSION

CAMKE的次版本号，比如2.4.6中的4

###### CMAKE_PATCH_VERSION

CMAKE的补丁等级，比如2.4.6中的6

###### CAMKE_SYSTEM

系统名称比如LInux-2.6.22

###### CAMKE_SYSTEM_NAME

不包含版本的系统名，比如linux

###### CMAKE_SYSTEM_VERSION

系统版本，比如2.6.22

###### CMAKE_SYSTEM_PROCESSOR

处理器的名称，比如i686。

###### UNIX

在所有的类UNIX平台为TRUE，包括OS X和cygwin

###### WIN32

在所有win32平台为TRUE，包括cygwin



### 3. CMake Generators

cmake -G

**references**: [cmake-generators(7)](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id7)

#### Visual Studio Generators

##### Visual Studio 11 2012

- `cmake -G "Visual Studio 10 2010" -A Win32`
- `cmake -G "Visual Studio 10 2010" -A x64`
- `cmake -G "Visual Studio 10 2010" -A Itanium`
- `cmake -G "Visual Studio 10 2010 Win64 `
-  `cmake -G Visual Studio 10 2010 IA64`

##### Visual Studio 12 2013

- `cmake -G "Visual Studio 12 2013" -A Win32`
- `cmake -G "Visual Studio 12 2013" -A x64`
- `cmake -G "Visual Studio 12 2013" -A ARM`
- `cmake -G "Visual Studio 12 2013 Win64"`
- `cmake -G "Visual Studio 12 2013 ARM"`

##### Visual Studio 16 2019

- `cmake -G "Visual Studio 16 2019" -A Win32`
- `cmake -G "Visual Studio 16 2019" -A x64`
- `cmake -G "Visual Studio 16 2019" -A ARM`
- `cmake -G "Visual Studio 16 2019" -A ARM64`

