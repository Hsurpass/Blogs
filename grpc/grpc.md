# 安装grpc

1. clone grpc 仓库

   ```bash
   git clone git@github.com:grpc/grpc.git
   cd grpc
git submodule update --init or git submodule update --init --recursive
   ```

2. 安装依赖

   - 安装 abseil-cpp：

     ```bash
     cd grpc/third_party/abseil-cpp
     mkdir build && cd build
     cmake ..
     make && make install
     ```

   - 安装protobuf：

     ```bash
     cd grpc/third_party/protobuf
     mkdir build && cd build
     cmake ..
     make -j4
     make install
     ```

     

3. 编译

   ```bash
   cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=../_install ..
   make -j 4
   make install
   ```

   

cmake 编译错误：

1. ```cmake
   -- Checking for module 'libsystemd>=233'
   --   No package 'libsystemd' found
   ```

   解决：

   ```bash
   sudo apt install libsystemd libsystemd-dev
   ```

2. ```cmake
   CMake Warning at cmake/protobuf.cmake:51 (message):
     gRPC_PROTOBUF_PROVIDER is "module" but PROTOBUF_ROOT_DIR is wrong
   Call Stack (most recent call first):
     CMakeLists.txt:332 (include)
   ```

   解决：可能之前装的pb版本不对，要以来thirty_party中的pb。

   
   
3. ```cmake
   CMake Warning at cmake/ssl.cmake:55 (message):
     gRPC_SSL_PROVIDER is "module" but BORINGSSL_ROOT_DIR is wrong
   Call Stack (most recent call first):
     CMakeLists.txt:334 (include)
   ```

   

   

   

https://grpc.io/docs/languages/cpp/quickstart/

https://github.com/grpc/grpc/blob/master/BUILDING.md

https://blog.csdn.net/cplcdk/article/details/127241905

https://blog.csdn.net/Aidam_Bo/article/details/114845688?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-114845688-blog-125272337.pc_relevant_default&spm=1001.2101.3001.4242.1&utm_relevant_index=3

https://blog.csdn.net/cucgyfjklx/article/details/122618536

https://www.baidu.com/s?wd=CMake%20Warning%20at%20cmake%2Fssl.cmake%3A55%20(message)%3A%20%20%20gRPC_SSL_PROVIDER%20is%20%22module%22%20but%20BORINGSSL_ROOT_DI&rsv_spt=1&rsv_iqid=0xaeedac450006f0f7&issp=1&f=8&rsv_bp=1&rsv_idx=2&ie=utf-8&rqlang=cn&tn=baiduhome_pg&rsv_dl=tb&rsv_enter=1&oq=--%2520%2526lt%253Bhecking%2520for%2520module%2520%2526%252339%253Blibsystemd%2526gt%253B%253D2%2526lt%253B%2526lt%253B%2526%252339%253B%2520--%2520No%2520package%2520%2526%252339%253Blibsystemd%2526%252339%253B%2520found&rsv_btype=t&inputT=561&rsv_t=871d78CPcNGcCL51Nda1SAGtXYlF6bJGJpVC7%2BIocNYQbiE5cUeD17JJwCDqMTWCQAyt&rsv_pq=bdec3c6500078605&rsv_sug3=5&rsv_n=2&rsv_sug2=0&rsv_sug4=561

https://blog.csdn.net/manageruser/article/details/126736076

https://www.likecs.com/show-305683643.html

https://zhuanlan.zhihu.com/p/113291650

https://blog.csdn.net/manageruser/article/details/126736076

# reference

https://grpc.io/

https://github.com/grpc/grpc