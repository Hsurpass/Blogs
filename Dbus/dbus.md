

安装

```bash
# 循环遍历 capicxx-dbus-runtime/src/dbus-patches/ 目录下的所有 .patch 文件，并将每个补丁文件应用到 dbus-1.12.16/ 目录中的相应文件上。
# for patch in capicxx-dbus-runtime/src/dbus-patches/*.patch; 这是一个 for 循环语句，用于遍历指定目录下所有以 .patch 结尾的文件。
# patch -d dbus-1.12.16/ -p1 <"$patch";: 在循环中，对每个找到的补丁文件执行 patch 命令。-d dbus-1.12.16/ 选项指定了要处理的目标文件所在的目录，-p1 选项告诉 patch 命令在应用补丁时去掉文件路径中的第一个目录。<"$patch" 则将当前循环到的补丁文件作为输入。
# for patch in capicxx-dbus-runtime/src/dbus-patches/*.patch; do patch -d dbus-1.14.10/ -p1 <"$patch"; done
for patch in capicxx-dbus-runtime/src/dbus-patches/*.patch; do patch -d dbus-1.12.28/ -p1 <"$patch"; done

cd dbus-1.12.28/
./configure --prefix=$PWD/install_20.04
make install	# 不要安装在 /usr/local 下，否则可能导致系统不能启动
make install-pkgconfigDATA # install-pkgconfigDATA: 在当前目录下执行 Makefile 中的 install-pkgconfigDATA 目标，安装 pkgconfig 配置文件到系统中。

export PKG_CONFIG_PATH="$PWD/install_20.04/lib/pkgconfig:$PKG_CONFIG_PATH" 

cd common-api-dbus-runtime

```







[CommonAPIDBusCppUserGuide.1823987351.pdf (usermanual.wiki)](https://usermanual.wiki/Document/CommonAPIDBusCppUserGuide.1823987351.pdf)

[CommonAPI基本流程 · zeerd's blog](https://blog.zeerd.com/capicxx-example-helloworld/)

[CommonAPI C D Bus in 10 minutes · COVESA/capicxx-dbus-tools Wiki (github.com)](https://github.com/COVESA/capicxx-dbus-tools/wiki/CommonAPI-C---D-Bus-in-10-minutes)