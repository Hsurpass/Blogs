https://github.com/libevent/libevent/blob/master/Documentation/Building.md#jump-to

```bash
sudo apt-get install automake autoconf libtool pkg-config
sudo apt-get install doxygen git cmake
sudo apt-get install libssl-dev libmbedtls-dev
sudo apt-get install zlib1g-dev
sudo apt-get install python3

git clone git@github.com:libevent/libevent.git
cmake -B build -DCMAKE_BUILD-TYPE=Debug # Default to Unix Makefiles
cmake --build build -j4
cmake --install build
#cmake --install build --prefix ./install
make verify # Optional

libevent_root=/mnt/d/WorkSpace/4openSourceCode/libevent/install
libevent_bin=${libevent_root}/bin
libevent_include=${libevent_root}/include
libevent_lib=${libevent_root}/lib

#export CPLUS_INCLUDE_PATH=${libevent_include}:$CPLUS_INCLUDE_PATH
#export LIBRARY_PATH=${libevent_lib}:$LIBRARY_PATH
#export LD_LIBRARY_PATH=${libevent_lib}:$LD_LIBRARY_PATH
#export PATH=${libevent_root}:${libevent_bin}:$PATH

pkg-config --modversion libevent #查看libevent版本
```



# reference

https://libevent.org/libevent-book/

http://www.wangafu.net/~nickm/libevent-2.1/doxygen/html/