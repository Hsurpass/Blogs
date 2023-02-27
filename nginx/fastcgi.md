# 编译fcgilib

1. ./configure

2. make

   出现以下错误：

   ```bash
   cd . && aclocal-1.9
   /bin/bash: aclocal-1.9: command not found
   make: *** [Makefile:320: aclocal.m4] Error 127
   ```

   解决方法：

   当前aclocal版本比makefile中的版本高，重新生成configure 文件：

   ```bash
   autoreconf -ivf
   
   #其中 -i install missing
   #    -v  verbose
   #    -f  force, 认为所有文件都过时而重新生成脚本.
   
   执行autoreconf -ivf出现如下错误：
   1. checking for C compiler warning flags... -Wall
      checking that generated files are newer than configure... done
      configure: creating ./config.status
      .in'ig.status: error: cannot find input file: `Makefile
   https://stackoverflow.com/questions/62662905/inig-status-error-cannot-find-input-file-makefile/68999840
   
    dos2unix configure.ac
   
   #然后再重新执行 ./configure 再make即可通过！
   ```

   