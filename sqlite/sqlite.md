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

## 查看当前使用的数据库

```sqlite
.databases
```

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

## 切换数据库

```sqlite
>sqlite .open otherr.db  --直接使用.open切换
```



# 数据库对象

CREATE 数据库对象：创建一个数据库对象

DROP 数据库对象：删除一个数据库对象

ALTER 数据库对象：修改一个数据库对象

## 表

### 查看创建表的命令 .schema

```sqlite
.schema table
or 
select sql from sqlite_master where type='table' and tbl_name='COMPANY';
```

### 查看都有哪些表 .tables

```sqlite
.tables
or
select tbl_name from sqlite_master where type='table';
```

### 创建一个表 CREATE TABLE

```sqlite
sqlite> CREATE TABLE COMPANY(
   ID INT PRIMARY KEY     NOT NULL,
   NAME           TEXT    NOT NULL,
   AGE            INT     NOT NULL,
   ADDRESS        CHAR(50),
   SALARY         REAL
);
```

### 删除一个表 DROP TABLE

```sqlite
DROP TABLE COMPANY
```

### 新增数据 INSERT INTO

```sqlite
insert into table_name (column1, column2, ... columnN) (value1, value2, ... valueN) --语法1
insert into table_name values(v1, v2, ... vN) --语法2
```

### 删除数据 DELETE

删除一行

```sqlite
delete from company where id = '1';
```

删除整个表

```sqlite
delete from company
```



### 修改数据 UPDATE

```sqlite
update company set address='Texas' where id = 6;
```







### 查找数据 SELECT

格式化输出：（所有的 .命令只在sqlite的命令提示符中可用。）

```sqlite
sqlite> .header on
sqlite> .mode column 
sqlite> .width 10,20,30 --显示列宽度, 第一列宽度为10，第二列宽度为20，第三列宽度为30
```

全表查询：查询company表中所有记录中的全部字段。

```sqlite
select * from company;
```

部分查询：查询company表中所有记录中的部分字段。

```sqlite
select id, name, salary from company; 
```

条件查询：

```sqlite
select * from company where salary > 50000; --查询salary>50000的所有记录
```

### where子句

##### 比较运算符

- 相等：== or =
- 不相等：!= or <>
- 大于：>
- 小于：<
- 大于等于：>=
- 小于等于：<=
- 不大于：!>
- 不小于：!<

##### 逻辑运算符

###### AND 和 OR

```sqlite
select * from company where age>=25 and salary >= 65000; --查找年龄>=25 并且 工资>=65000的所有记录的所有字段。
```

```sqlite
select * from company where age>=25 or salary >= 65000; --查找年龄>=25 或者 工资>=65000的所有记录的所有字段。
```

###### IS 和 IS NOT

```sqlite
select * from company where salary is 65000;  --查找工资等于65000的记录
select * from company where salary is not 65000; --查找工资等于65000的记录

select * from company where age is NULL; --查找年龄为NULL的记录
select * from company where age is not NULL; --查找age不为NULL的记录
```

###### IN 和 NOT IN

```sqlite
select * from company where age in (25,27); --查找年龄是25或者是27的记录
select * from company where age not in (25,27); --查找年龄不是25也不是27的记录
```

###### LIKE 和 GLOB

模糊匹配

有两个通配符和like一起使用：

- 百分号（%）：*百分号（%）代表零个、一个或多个数字或字符*。
- 下划线（ _ ）：下划线（_）代表一个单一的数字或字符。

```sqlite
select * from company where name like "Ki%"; --查找名字中以Ki开始的记录
```

有两个通配符和glob一起使用：

- 星号（ * ）：星号（*）代表零个、一个或多个数字或字符。
- 问号（?）：问号（?）代表一个单一的数字或字符。

这些符号可以被组合使用。

glob与like不同的是，glob是大小写敏感的。

```sqlite
select * from company where name glob "Ki*"; --查找名字中以Ki开始的记录
```



###### BETWEEN

```sqlite
select * from company where age between 25 and 27;    --查找年龄在25到27之间的所有记录
```

###### EXISTS

```sqlite
select * from company where exists (
    select age from company where salary > 90000); -- 子查询语句结果为真，外查询返回全部结果
select * from company where not exists (
    select age from company where salary > 90000); -- 子查询语句结果为真，not exists(子查询)为假，则外查询不会返回结果
select * from company where age > (select age from company where salary > 65000) --子查询结果为salary>65000的年龄的记录，外查询返回所有年龄大于子查询字段值的记录。
```

###### UNIQUE



##### 位运算符

https://www.runoob.com/sqlite/sqlite-operators.html

### limit 和 offset子句

```sqlite
select * from company limit 4;    --从第一条记录开始只输出4条记录
select * from company limit 3 offset 2; --从第3条记录(偏移2条)开始输出3条记录
```

### order by子句









## 视图



## 索引



## 触发器



# reference

[sqlite官网 英文](https://www.sqlite.org/index.html)

[sqlite中文](http://www.sqlite.net.cn/)

[sqlite 在线IDE](https://sqliteonline.com/)