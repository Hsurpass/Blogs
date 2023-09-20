

安装leveldb

```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
cmake --install . --prefix ../install
```

https://github.com/google/leveldb/tree/1.23#build-for-posix