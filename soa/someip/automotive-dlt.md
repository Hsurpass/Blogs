安装 automotive-dlt：

No package 'automotive-dlt' found

```bash
sudo apt install dlt-daemon
sudo apt install dlt-viewer
```

[automotive-dlt: Main Page (pfefferz.github.io)](https://pfefferz.github.io/dlt-daemon-doxygen-built/index.html)

or 源码安装：

DLT包括：DLT daemon、DTL viewer两个子工程。DLT daemon运行在ECU上，DTLviewer运行在调试PC上。

```
git clone git@github.com:COVESA/dlt-daemon.git
git clone git@github.com:COVESA/dlt-viewer.git
```

安装dlt-daemon:

```bash
sudo apt-get install zlib1g-dev libdbus-glib-1-dev build-essential
optional: sudo apt-get install libjson-c-dev # in case you want to use dlt-receives extended filtering

mkdir build
cd build
cmake ..
make
optional: sudo make install
optional: sudo ldconfig # in case you executed make install
```

[COVESA/dlt-daemon: Diagnostic Log and Trace. (github.com)](https://github.com/COVESA/dlt-daemon?tab=readme-ov-file#build-and-install)

[dlt-daemon安装教程 - 多弗朗强哥 - 博客园 (cnblogs.com)](https://www.cnblogs.com/chendeqiang/p/13033234.html)

# reference

[AGL-AMM-W16-DLT_A.pdf (linuxfoundation.org)](http://events17.linuxfoundation.org/sites/events/files/slides/AGL-AMM-W16-DLT_A.pdf)

[dlt daemon - Create a DLT logs in C++. Problem with dlt-deamon - Stack Overflow](https://stackoverflow.com/questions/77487897/create-a-dlt-logs-in-c-problem-with-dlt-deamon)

[【DLT学习笔记2】-- 什么是DLT？(Diagnostic Log and Trace) (eepw.com.cn)](https://eleaction01.spaces.eepw.com.cn/articles/article/item/326281)



