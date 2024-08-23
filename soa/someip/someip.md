

[安装 automotive-dlt](#automotive-dlt.md)



安装capicxx-core-runtime:

```bash
git clone git@github.com:COVESA/capicxx-core-runtime.git
```

安装capicxx-core-tools：

[CommonAPICppUserGuide.113855339.pdf (usermanual.wiki)](https://usermanual.wiki/Document/CommonAPICppUserGuide.113855339.pdf)

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



vsomeip两个设备间通信

要实现两个设备间的通信，无需修改 c++ 代码，不过需要编写配置文件。

配置文件是由 json 格式编写的，默认配置文件是/etc/vsomeip.json，默认配置文件夹是 /etc/vsomeip。不过如果可执行文件同目录下存在 ./vsomeip.json或 ./vsomeip 文件夹时，则用本地的配置文件。如果环境变量 “VSOMEIP_CONFIGURATION” 设为有效的文件或目录路径，则会使用该环境变量中所指定的配置（此时既不会使用默认文件/文件夹，也不会使用本地文件/文件夹)。

在下面的配置示例中，服务器和客户端程序分别运行在两台 ubuntu 16.04 的虚拟机上，服务端所在虚拟机地址为192.168.24.132 的设备上，客户端地址为 192.168.24.129。

首先，看一下服务器端配置的示例。

```json
{
    "unicast" : "172.17.0.2",
    "logging" :
    { 
        "level" : "debug",
        "console" : "true",
        "file" : { "enable" : "false", "path" : "/tmp/vsomeip.log" },
        "dlt" : "false"
    },
    "applications" : 
    [
        {
            "name" : "World",
            "id" : "0x1212"
        }
    ],
    "services" :
    [
        {
            "service" : "0x1234",
            "instance" : "0x5678",
            "unreliable" : "30509"
        }
    ],
    "routing" : "World",
    "service-discovery" :
    {
        "enable" : "true",
        "multicast" : "224.224.224.245",
        "port" : "30490",
        "protocol" : "udp",
        "initial_delay_min" : "10",
        "initial_delay_max" : "100",
        "repetitions_base_delay" : "200",
        "repetitions_max" : "3",
        "ttl" : "3",
        "cyclic_offer_delay" : "2000",
        "request_response_delay" : "1500"
    }
}
```

对其中的部分项进行说明：

-   unicast：对于 IP 通信，单播（unicast ）地址是必须的。
-   logging：这里面的设置是可选的，设置 "console"=true 可以查看控制台上的日志消息。
-   applications：可以为每个 application (application  是通过 create_application(<name>) 创建的) 定义固定的ID，**而不是由自动配置决定。这将有助于在后续跟踪中有效识别出applications**。applications 中 id 是必须设置的，因为这个值在网络中必须是惟一的。==如果不设置该 id，自动配置将把每个设备上的 id 都设置为 1，通信将无法工作。==
-   services：对于每个服务实例（service instance），必须定义在哪个端口下可以访问它。如果端口**为“unreliable”，则说明是 UDP 端口，如果端口为“reliable”，则是 TCP 端口。**
-   routing：==每个设备只有一个路由管理器==。这个路由管理器将被附加到第一个启动的vsomeip 应用程序或该项定义的应用程序。
-   service-discovery：==**这里的所有参数只有在启用服务发现时才用得上**==。其中**必选参数**为发送服务发现消息的组播地址（**multicast**）、端口（**port**）和协议（**protocol**）。其他参数决定 offer messages 的频率、延迟等等。

注意：需确保设备已配置为接收组播消息(例如，通过`route add -nv 224.224.224.245 dev ens33/eth0` 或类似配置)。

这条命令的作用是向路由表中添加一条静态路由，将目标地址 `224.224.224.245` 发送到 `eth0` 网络接口。让我解释一下这条命令的各个部分：

-   `route`: 是用于配置内核中的路由表的命令。
-   `add`: 表示要添加一条新的路由。
-   `-nv`: 是选项，`-n` 表示使用数字形式显示地址，`-v` 表示显示详细信息。
-   `224.224.224.245`: 是目标地址，即要发送数据包到这个地址。
-   `dev eth0`: 指定数据包应该通过 `eth0` 网络接口发送。

~~因此，这条命令的作用是将发送到 `224.224.224.245` 的数据包通过 `eth0` 网络接口发送出去。这种操作通常用于配置特定的网络路由。~~

将组播地址添加到特定网络接口（如 eth0）时，系统会确保接收到的组播数据包只会通过指定的网络接口进行接收。这样可以避免在网络中造成不必要的广播，同时也确保了组播数据包的目的地是正确的设备或应用程序。

`route del -nv 224.224.224.245 dev eth0`

再来看下客户端配置示例：

```json
{
    "unicast" : "172.17.0.1",
    "logging" :
    {
        "level" : "debug",
        "console" : "true",
        "file" : { "enable" : "false", "path" : "/var/log/vsomeip.log" },
        "dlt" : "false"
    },
    "applications" : 
    [
        {
            "name" : "Hello",
            "id" : "0x1313"
        } 
    ],
    "routing" : "Hello",
    "service-discovery" :
    {
        "enable" : "true",
        "multicast" : "224.224.224.245",
        "port" : "30490",
        "protocol" : "udp",
        "initial_delay_min" : "10",
        "initial_delay_max" : "100",
        "repetitions_base_delay" : "200",
        "repetitions_max" : "3",
        "ttl" : "3",
        "cyclic_offer_delay" : "2000",
        "request_response_delay" : "1500"
    }
}
```

由于客户端不提供服务，因此不需要 “services” 设置。



Franca IDL

[franca/franca: A framework for defining and transforming interfaces (github.com)](https://github.com/franca/franca)

[Franca IDL与CommonAPI C++ D-Bus实战教程：方法、信号和属性传递详解 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/671160417)

[CommonAPI 使用说明文档_commonapi 订阅实现-CSDN博客](https://blog.csdn.net/C_Silence_K/article/details/104673833)

[【C/C++ CommonAPI入门篇】从 Franca IDL 到 C++: 深入解析汽车软件接口开发-CSDN博客](https://blog.csdn.net/qq_21438461/article/details/134917196)

# reference

https://some-ip.com/

https://github.com/COVESA/vsomeip/wiki/vsomeip-in-10-minutes

[深入浅出vsomeip：打造高效车载通信系统 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/667439011)

[译：vsomeip 10 分钟阅读](https://blog.csdn.net/bluebird_shao/article/details/126924611)

[原创 | vsomeip — SOME/IP 开源实现](https://mp.weixin.qq.com/s?__biz=MzUzNDYxOTA1NA==&mid=2247527763&idx=1&sn=958a10a87546f53d9ec8f1ddffc7f2e1&chksm=fa93db92cde452842b8d3df6d7d33216621d3d5a57e43924403f645c0d64369c4427214c867c&scene=27)

