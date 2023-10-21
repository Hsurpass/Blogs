

flamegraph不需要安装，直接下载源码就可以使用其提供的脚本

```c
https://github.com/brendangregg/FlameGraph
```

在wsl2上安装perf：

```bash
apt install flex bison
git clone https://github.com/microsoft/WSL2-Linux-Kernel --depth 1
cd WSL2-Linux-Kernel/tools/perf
make -j8
sudo cp perf /usr/local/bin
```



```bash
sudo apt install linux-tools-generic
vi ~/.bashrc
linux_tools=/usr/lib/linux-tools/5.15.0-87-generic
export PATH=${linux_tools}:$PATH
```

[在WSL2中使用perf性能剖析工具](https://zhuanlan.zhihu.com/p/600483539)

[Perf分析CPU性能问题笔记](https://cloud.tencent.com/developer/article/1416234)



```bash
# 1 检测进程
sudo perf record -F 99 -p pid -g -- sleep 30
对进程ID为181的进程进行采集，采集时间为30秒
执行期间不要退出上述代码中perf record表示记录，-F 99表示每秒99次
-p 13204是进程号，即对哪个进程进行分析，-g表示记录调用栈，sleep 30则是持续30秒
执行完这行指令后，会自动生成perf.data文件

perf report # 展示报告

# 2 解析数据
sudo perf script -i perf.data &> perf.unfold
# 3 符号进行折叠
./stackcollapse-perf.pl perf.unfold &> perf.folded

# 4 生成svg图
./flamegraph.pl perf.folded > perf-$(date +%Y%m%d-%H:%M:%S).svg

```

https://blog.csdn.net/u011436427/article/details/132324713

https://blog.csdn.net/gatieme/article/details/78885908