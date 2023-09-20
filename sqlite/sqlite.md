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



# 配置

注意：确保 sqlite> 提示符与点命令之间没有空格，否则将无法正常工作。

- .show：查看 SQLite 命令提示符的默认设置
- .headers ON | OFF：开启/关闭头部显示
- .mode <MODE>：设置输出模式
  - column：左对齐的列
  - line：每行一个值
  - list：由 “.”分隔的值
- .log
- .timer ON|OFF：开启或关闭CPU定时器
- 

格式化输出

```sqlite
sqlite>.header on
sqlite>.mode column
sqlite>.timer on
```

输出：

```sqlite
ID          NAME        AGE         ADDRESS     SALARY
----------  ----------  ----------  ----------  ----------
1           Paul        32          California  20000.0
2           Allen       25          Texas       15000.0
3           Teddy       23          Norway      20000.0
4           Mark        25          Rich-Mond   65000.0
5           David       27          Texas       85000.0
6           Kim         22          South-Hall  45000.0
7           James       24          Houston     10000.0
CPU Time: user 0.000000 sys 0.000000
```



[sqlite配置](https://www.runoob.com/sqlite/sqlite-commands.html)



# 数据类型

NULL：空值

INT：4字节有符号整型 

INTEGER：有符号整型，根据值的大小存储在**1~8**字节中。

REAL：8字节的浮点值

TEXT：文本字符串 ，UTF-8

BLOB：一个blob数据，完全根据输入存储。

NONE： 不做任何的转换，直接以该数据所属的数据类型进行存储。

## 亲和类型

### INTEGER

### REAL

### TEXT

### BLOB

### NUMERIC

# 数据库

## 创建数据库

方法1：

```bash
sqlite3 test.db
```

方法2：

```sqlite
sqlite>.open test.db -- 打开数据库，没有则创建
```

## 删除数据库



## 导出数据库

```bash
sqlite3 test.db .dump > testdb.sql
```

## 导入数据库

```bash
sqlite3 testdb.db < testdb.sql
```

### 查看当前在哪个数据库中

```bash
sqlite>.databases
```







# 数据库对象

CREATE 数据库对象：创建一个数据库对象

DROP 数据库对象：删除一个数据库对象

ALTER 数据库对象：修改一个数据库对象

## 表

### 查看创建表的命令

```sqlite
.schema table
CREATE TABLE sqlite_master (
  type text,
  name text,
  tbl_name text,
  rootpage integer,
  sql text
);
```

### 查看都有哪些表

```sqlite
.tables
```

### 创建一个表

CREATE TABLE

```sqlite
sqlite> CREATE TABLE COMPANY(
   ID INT PRIMARY KEY     NOT NULL,
   NAME           TEXT    NOT NULL,
   AGE            INT     NOT NULL,
   ADDRESS        CHAR(50),
   SALARY         REAL
);
```

### 删除一个表

DROP TABLE

```sqlite
DROP TABLE COMPANY
```



### 新增数据

### 删除数据

### 修改数据

### 查找数据





## 视图



## 索引



## 触发器



# reference

[sqlite官网 英文](https://www.sqlite.org/index.html)

[sqlite中文](http://www.sqlite.net.cn/)

[sqlite 在线IDE](https://sqliteonline.com/)