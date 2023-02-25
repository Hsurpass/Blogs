# clone

```bash
$ git clone git@github.com:Hsurpass/cgdb.git
$ cd cgdb
$ mkdir build _install
$ ./autogen.sh
(a prebuilt configure script is not included in the git repository, so it must be generated with the autogen.sh script.)
```

# Install
cgdb depends on `libreadline` and `ncurses` development libraries.

```bash
$ cd build
$ ../configure --prefix=$PWD/../_install
$ make
$ sudo make install
```
# error

(1)出现错误：

```bash
configure: error: CGDB requires curses.h or ncurses/curses.h to build.
```
解决方案:
```bash
重要：确认是否安装ncurses库，且必须要安装 libncursesw5-dev，否则中文乱码

sudo apt install libncurses5-dev
sudo apt install libncursesw5-dev
```
(2) 出现错误：
```bash
configure: error: Please install flex before installing
```
解决:
```bash
sudo apt install flex
```

(3)

```bash
configure: error: Please install makeinfo before installing
sudo apt install texinfo
```

(4)

```bash
configure: error: CGDB requires GNU readline 5.1 or greater to link.
If you used --with-readline instead of using the system readline library,
make sure to set the correct readline library on the linker search path
via LD_LIBRARY_PATH or some other facility.

sudo apt install libreadline-dev
```

# path

```bash
vi ~/.bashrc

cgdb_bin=/mnt/d/WorkSpace/4openSourceCode/cgdb/_install/bin
export PATH=${cgdb_bin}:$PATH
```

# references:
    官网: http://cgdb.github.io/
    github: https://github.com/cgdb/cgdb
    中文文档: https://github.com/leeyiw/cgdb-manual-in-chinese
