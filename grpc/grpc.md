# 安装grpc

1. clone grpc 仓库

   ```
   
   ```

   

2. 编译

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

   解决：

   ```bash
   
   ```

   

   

3. ```cmake
   CMake Warning at cmake/ssl.cmake:55 (message):
     gRPC_SSL_PROVIDER is "module" but BORINGSSL_ROOT_DIR is wrong
   Call Stack (most recent call first):
     CMakeLists.txt:334 (include)
   ```

   sdfs

   

   



# reference

https://grpc.io/

https://github.com/grpc/grpc