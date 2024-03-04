

[安装 automotive-dlt](#automotive-dlt.md)



安装capicxx-core-runtime:

```bash
git clone git@github.com:COVESA/capicxx-core-runtime.git
```

安装capicxx-core-tools：

```bash
sudo apt install openjdk-8-jdk # ubuntu22.04 使用openjdk-8 Maven-3.6.3 success， openjdk-11 fail

git clone git@github.com:COVESA/capicxx-core-tools.git
cd capicxx-core-tools/org.genivi.commonapi.core.releng
mvn -Dtarget.id=org.genivi.commonapi.core.target clean verify #（命令执行时间很长）(报错，将mvn版本升级到3.8.2 shishi)
cd ../org.genivi.commonapi.core.cli.product/target/products
unzip -d ./commonapi_core_generator commonapi_core_generator.zip # org.genivi.commonapi.core.cli.product/target/products/org.genivi.commonapi.core.cli.product/all 也是
# chmod +x ./commonapi_core_generator/commonapi-core-generator-linux-x86_64
sudo ln -s $PWD/commonapi_core_generator/commonapi-core-generator-linux-x86_64 /usr/local/bin/commonapi-core-generator-linux-x86_64
```

安装capicxx-someip-runtime:

在capicxx-core-runtime,vsomeip安装后安装

```bash
git clone git@github.com:COVESA/capicxx-someip-runtime.git
cmake -B build
```

安装capicxx-someip-tools：

```bash
git clone git@github.com:COVESA/capicxx-someip-tools.git
cd capicxx-someip-tools/org.genivi.commonapi.someip.releng
mvn -DCOREPATH=<path to your CommonAPI-Tools dir> -Dtarget.id=org.genivi.commonapi.someip.target clean verify # COREPATH指的是capicxx-core-tools仓库目录 例：mvn -DCOREPATH=../../capicxx-core-tools -Dtarget.id=org.genivi.commonapi.someip.target clean verify
cd ../org.genivi.commonapi.someip.cli.product/target/products
unzip -d ./commonapi_someip_generator commonapi_someip_generator.zip
# chmod +x ./commonapi_someip_generator/commonapi-someip-generator-linux-x86_64
sudo ln -s $PWD/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64 /usr/local/bin/commonapi-someip-generator-linux-x86_64
```

reference:

[lixiaolia/commonapi_someip_demo: 用于演示CommonAPI-SomeIP的使用 (github.com)](https://github.com/lixiaolia/commonapi_someip_demo)

```bash
sudo update-alternatives --install /usr/bin/java java /opt/jdk1.8.0_281/bin/java 700
```

-   `update-alternatives`: 这是一个Debian和Ubuntu系统中用于管理可替换命令的工具。它允许系统管理员为特定的命令设置多个版本，并可以方便地切换使用哪个版本。
-   `--install`: 这个参数告诉`update-alternatives`要安装一个新的替代项。
-   `/usr/bin/java`: 这是Java命令的默认路径。当你输入`java`命令时，系统通常会在这个路径下查找并执行Java。
-   `java`: 这是你想要设置替代项的命令名称。在这个情况下，它是`java`。
-   `/opt/jdk1.8.0_281/bin/java`: 这是你想要设置为默认的Java版本的完整路径。在这个例子中，它指向了Java 8的一个特定版本（1.8.0_281）。
-   `700`: 这是一个优先级数字。当系统中有多个版本的Java时，它会使用这个优先级数字来决定哪个版本应该被默认使用。数字越高，优先级越高。如果有其他版本的Java也被设置为替代项，并且它们的优先级低于700，那么系统就会使用这个版本。

安装capicxx-dbus-runtime:

```bash
wget http://dbus.freedesktop.org/releases/dbus/dbus-<VERSION>.tar.gz
wget http://dbus.freedesktop.org/releases/dbus/dbus-1.14.10.tar.gz
```



```bash

git clone git@github.com:COVESA/capicxx-dbus-runtime.git
git clone git@github.com:COVESA/capicxx-dbus-tools.git
```







生成代码：

```bash
commonapi-core-generator-linux-x86_64 HelloWorld.fidl
commonapi-someip-generator-linux-x86_64 HelloWorld.fdepl
```



安装vsomeip

cmake 命令中添加的参数 -DENABLE_SIGNAL_HANDLING=1 可以确保终止 vsomeip 应用程序的时候不出问题，否则当使用 Ctrl-c 停止应用时，共享内存段 /dev/shm/vsomeip 可能未被正确删除。

```bash
cmake -DENABLE_SIGNAL_HANDLING=1 -B build
cmake -DENABLE_SIGNAL_HANDLING=1 -DDIAGNOSIS_ADDRESS=0x10 -B build
```



Franca IDL

[franca/franca: A framework for defining and transforming interfaces (github.com)](https://github.com/franca/franca)

[Franca IDL与CommonAPI C++ D-Bus实战教程：方法、信号和属性传递详解 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/671160417)

[CommonAPI 使用说明文档_commonapi 订阅实现-CSDN博客](https://blog.csdn.net/C_Silence_K/article/details/104673833)

[【C/C++ CommonAPI入门篇】从 Franca IDL 到 C++: 深入解析汽车软件接口开发-CSDN博客](https://blog.csdn.net/qq_21438461/article/details/134917196)

# reference

https://some-ip.com/

https://github.com/COVESA/vsomeip/wiki/vsomeip-in-10-minutes

[深入浅出vsomeip：打造高效车载通信系统 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/667439011)