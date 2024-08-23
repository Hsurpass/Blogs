



```bash
sudo apt update
sudo apt install libyaml-cpp-dev

```



```bash
sudo apt update
sudo apt install cmake libyaml-dev  # 安装编译所需的工具和依赖

# 克隆 yaml-cpp 的 GitHub 仓库
git clone https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp

# 创建构建目录并编译
mkdir build
cd build
cmake .. # 。如果你想生成共享库（动态链接库），可以使用-DYAML_BUILD_SHARED_LIBS=on（注意，不同文章中的参数可能略有不同，但意义相同，如-DBUILD_SHARED_LIBS=ON，效果一致）cmake -DYAML_BUILD_SHARED_LIBS=on ..
make

# 安装
sudo make install

# 验证yaml-cpp是否正确安装
pkg-config --modversion yaml-cpp
```



