编译gtest

```bash
mkdir build
cd build
# cmake .. # 默认安装在/usr/local下
or
# cmake -Dgtest_build_tests=on -DCMAKE_INSTALL_PREFIX=./install ..
sudo make -j8
sudo make install
```

如果没有安装到系统目录，需要设置环境变量:

```bash
gtest_root=/mnt/d/WorkSpace/4openSourceCode/googletest/install
gtest_include=${gtest_root}/include
gtest_lib=${gtest_root}/lib

export CPLUS_INCLUDE_PATH=${gtest_include}:$CPLUS_INCLUDE_PATH
export LIBRARY_PATH=${gtest_lib}:$LIBRARY_PATH
export LD_LIBRARY_PATH=${gtest_lib}:$LD_LIBRARY_PATH
export PATH=${gtest_lib}:${gtest_include}:${gtest_root}:${cgdb_bin}:$PATH
```



```bash
g++ example.cc -o example -lgtest -lpthread
# 如果只想执行某个测试，可以使用--gtest_filter="xxx.xxx" 传参，例如：
# ./a.out  --gtest_filter="Add_Test*"
# ./a.out  --gtest_filter="Add_Test.positive"
./a.out --gtest_list_t
```

