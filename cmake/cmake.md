#### references:

https://cmake.org/cmake/help/v3.20/manual/cmake-generators.7.html#visual-studio-generators

https://cmake.org/cmake/help/git-stage/index.html#

https://mp.weixin.qq.com/s?__biz=MzU5MzcyMjI4MA==&mid=2247494287&idx=1&sn=7f383549a1f2212b1cf33c192a4a1235&chksm=fe0e8448c9790d5ef72b36bb8d116730f29f86a9fe3c2a03ee5cbb0006b0a39e778ce7d81e47&scene=21#wechat_redirect

https://cloud.tencent.com/developer/article/1446788

https://zhuanlan.zhihu.com/p/50829542

https://www.hahack.com/codes/cmake/



### 1.1 语法特性介绍

- **基本语法格式：指令(参数 1 参数 2…)**

- - 参数使用**括弧**括起
  - 参数之间使用**空格**或**分号**分开

- **指令是大小写无关的，参数和变量是大小写相关的**

  ```
  1set(HELLO hello.cpp)
  2add_executable(hello main.cpp hello.cpp)
  3ADD_EXECUTABLE(hello main.cpp ${HELLO})
  ```

- **变量使用${}方式取值，但是在 IF 控制语句中是直接使用变量名**

### 2.1 重要指令和CMake常用变量

#### 2.1.1 重要指令

- **cmake_minimum_required** **- 指定CMake的最小版本要求**

  ```
  1# CMake最小版本要求为2.8.3
  2cmake_minimum_required(VERSION 2.8.3)
  ```

- - 语法：**cmake_minimum_required(VERSION versionNumber [FATAL_ERROR])**

- **project** **- 定义工程名称，并可指定工程支持的语言** 

  ```
  1# 指定工程名为HELLOWORLD
  2project(HELLOWORLD)
  ```

- - 语法：**project(projectname [CXX] [C] [Java])**

- **set** **- 显式的定义变量** 

  ```
  1# 定义SRC变量，其值为main.cpp hello.cpp
  2set(SRC sayhello.cpp hello.cpp)
  ```

- - 语法：**set(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])**

- **include_directories - 向工程添加多个特定的头文件搜索路径** --->相当于指定g++编译器的-I参数

  ```
  1# 将/usr/include/myincludefolder 和 ./include 添加到头文件搜索路径
  2include_directories(/usr/include/myincludefolder ./include)
  ```

- - 语法：**include_directories([AFTER|BEFORE] [SYSTEM] dir1 dir2 …)**

- **link_directories** **- 向工程添加多个特定的库文件搜索路径** --->相当于指定g++编译器的-L参数

  ```
  1# 将/usr/lib/mylibfolder 和 ./lib 添加到库文件搜索路径
  2link_directories(/usr/lib/mylibfolder ./lib)
  ```

- - 语法：link_directories(dir1 dir2 …) 

- **add_library** **- 生成库文件**

  ```
  1# 通过变量 SRC 生成 libhello.so 共享库
  2add_library(hello SHARED ${SRC})
  ```

- - 语法：**add_library(libname [SHARED|STATIC|MODULE] [EXCLUDE_FROM_ALL] source1 source2 … sourceN)**

- **add_executable** **- 生成可执行文件**

  ```
  1# 编译main.cpp生成可执行文件main
  2add_executable(main main.cpp)
  ```

- - 语法：**add_library(exename source1 source2 … sourceN)**

- **target_link_libraries** - 为 target 添加需要链接的共享库  --->相同于指定g++编译器-l参数

  ```
  1# 将hello动态库文件链接到可执行文件main
  2target_link_libraries(main hello)
  ```

- - 语法：**target_link_libraries(target library1library2…)**

- **add_subdirectory - 向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置**

  ```
  1# 添加src子目录，src中需有一个CMakeLists.txt
  2add_subdirectory(src)
  ```

- - 语法：**add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])**

- **aux_source_directory - 发现一个目录下所有的源代码文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表**

  ```
  1# 定义SRC变量，其值为当前目录下所有的源代码文件
  2aux_source_directory(. SRC)
  3# 编译SRC变量所代表的源代码文件，生成main可执行文件
  4add_executable(main ${SRC})
  ```

- - 语法：**aux_source_directory(dir VARIABLE)**

#### 2.1.2 CMake常用变量

- **CMAKE_C_FLAGS  gcc编译选项**

  **CMAKE_CXX_FLAGS  g++编译选项**

  ```
  1# 在CMAKE_CXX_FLAGS编译选项后追加-std=c++11
  2set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  ```

  **CMAKE_BUILD_TYPE  编译类型(Debug, Release)**

  ```
  1# 设定编译类型为debug，调试时需要选择debug
  2set(CMAKE_BUILD_TYPE Debug) 
  3# 设定编译类型为release，发布时需要选择release
  4set(CMAKE_BUILD_TYPE Release) 
  ```

  **CMAKE_BINARY_DIR**

  **PROJECT_BINARY_DIR**

  **<projectname>__BINARY_DIR**

- 1. 这三个变量指代的内容是一致的。
  2. 如果是 in source build，指的就是工程顶层目录。
  3. 如果是 out-of-source 编译,指的是工程编译发生的目录。
  4. PROJECT_BINARY_DIR 跟其他指令稍有区别，不过现在，你可以理解为他们是一致的。

- **CMAKE_SOURCE_DIR**

  **PROJECT_SOURCE_DIR**
  **<projectname>__SOURCE_DIR**

- 1. 这三个变量指代的内容是一致的,不论采用何种编译方式,都是工程顶层目录。
  2. 也就是在 in source build时,他跟 CMAKE_BINARY_DIR 等变量一致。
  3. PROJECT_SOURCE_DIR 跟其他指令稍有区别,现在,你可以理解为他们是一致的。

------

- **CMAKE_C_COMPILER：指定C编译器**
- **CMAKE_CXX_COMPILER：指定C++编译器**
- **EXECUTABLE_OUTPUT_PATH：可执行文件输出的存放路径**
- **LIBRARY_OUTPUT_PATH：库文件输出的存放路径**





## CMake Generators

#### Visual Studio Generators

- Visual Studio 11 2012
  - `cmake -G "Visual Studio 10 2010" -A Win32`
  - `cmake -G "Visual Studio 10 2010" -A x64`
  - `cmake -G "Visual Studio 10 2010" -A Itanium`
  - `cmake -G "Visual Studio 10 2010 Win64 `
  -  `cmake -G Visual Studio 10 2010 IA64`

- Visual Studio 12 2013
  - `cmake -G "Visual Studio 12 2013" -A Win32`
  - `cmake -G "Visual Studio 12 2013" -A x64`
  - `cmake -G "Visual Studio 12 2013" -A ARM`
  - `cmake -G "Visual Studio 12 2013 Win64"`
  - `cmake -G "Visual Studio 12 2013 ARM"`

- Visual Studio 16 2019
  - `cmake -G "Visual Studio 16 2019" -A Win32`
  - `cmake -G "Visual Studio 16 2019" -A x64`
  - `cmake -G "Visual Studio 16 2019" -A ARM`
  - `cmake -G "Visual Studio 16 2019" -A ARM64`