# 安装sqlite

```bash
sudo apt-get install tcl tcl-dev

mkdir _build
cd _build
../configure --prefix=${PWD}/../_install/

make 			#  Builds the "sqlite3" command-line tool
make sqlite3.c	#  Build the "amalgamation" source file
make devtest    #  Run some tests (requires Tcl)
make install
```







# reference

[sqlite官网 英文](https://www.sqlite.org/index.html)

[sqlite中文](http://www.sqlite.net.cn/)

[sqlite 在线IDE](https://sqliteonline.com/)