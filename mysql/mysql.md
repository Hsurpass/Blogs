https://blog.csdn.net/Chasingthewinds/article/details/130344853

https://blog.51cto.com/u_16213660/7280009

https://dev.mysql.com/doc/c-api/5.7/en/c-api-basic-interface-usage.html

https://dev.mysql.com/doc/connector-cpp/8.2/en/connector-cpp-installation-binary.html#connector-cpp-installation-binary-linux

https://blog.csdn.net/qq_39638989/article/details/126229189

https://blog.csdn.net/xunmeng2002/article/details/127852016

https://blog.csdn.net/qq_44918555/article/details/125153569

mysql能分布式安装吗？怎么配置？

# 安装

## linux上安装

```bash
# https://dev.mysql.com/doc/mysql-apt-repo-quick-guide/en/
sudo apt update
sudo apt install mysql-server
mysql --version	# 查看mysql版本
sudo systemctl start mysql   or  sudo service mysql start # 启动mysql
sudo systemctl status mysql  or  sudo service mysql status # 查看mysql状态
sudo systemctl stop mysql    or  sudo service mysql stop # 停止mysql
sudo systemctl restart mysql or  sudo service mysql restart # 重启mysql
sudo service --status-all # 查看所有服务状态

mysqladmin -u root -p shutdown #停止mysql服务
```

https://learn.microsoft.com/zh-cn/windows/wsl/tutorials/wsl-database#install-mysql

## windows上安装

https://www.runoob.com/mysql/mysql-install.html

## 安装完成后创建密码

Mysql安装成功后，默认的root用户密码为空，你可以使用以下命令来创建root用户的密码：

方法1：

```bash
[root@host]# mysqladmin -u root password "new_password";
```

方法二：

```mysql
mysql> ALTER USER 'root'@'localhost' IDENTIFIED BY '1111'; # localhost表示只能本机的客户端连接mysql
```

https://dev.mysql.com/doc/refman/8.0/en/default-privileges.html

## 远端主机以root用户连接mysql

1. 设置root@%密码

   ```mysql
   mysql #登录服务器
   mysql> alter user 'root'@'%' identified by '1111'; # %表示远端所有地址可以连接mysql服务
   # mysql> set password for 'root'@'localhost'=password('1111'); # error
   ```

2. 刷新权限

   ```mysql
   mysql> flush privileges;
   ```

3. 修改监听地址

   ```bash
   sudo vi /etc/mysql/mysql.conf.d/mysqld.cnf
   # 修改bind-address和mysqlx-bind-address 为下面这样
   bind-address            = 0.0.0.0
   mysqlx-bind-address     = 0.0.0.0
   ```

   https://dev.mysql.com/doc/refman/8.0/en/server-system-variables.html#sysvar_bind_address

4. 开放root用户远程访问权限

   ```mysql
   mysql> select user, host from user where user='root'; # 查看root访问权限
   mysql> update user set host='%' where user='root' # 设置root访问权限为所有ip，<风险> 最好改为
   mysql> update user set host='localhost' where user='root'
   ```

5. 开放3306端口远程访问权限

   ```mysql
   mysql> show variables like "%port%"; 	#查看都有哪些端口
   ```

## 创建账户

```mysql
mysql> create user 'root'@'172.22.244.89' identified by "password"; # 创建root@172.22.244.89的账户
mysql> grant all on *.* to 'root'@'172.22.244.89' with grant option; #分配权限
mysql> show grants for 'root'@'172.22.244.89'; # 查看权限

mysql> create user 'test'@'%' identified by "password"; # 创建test@%的账户
mysql> grant all on *.* to 'test'@'%' with grant option; #分配权限 all代表所有权限 *.* 代表所有数据库
or
mysql> grant INSERT, DELETE, UPDATE, SELECT, CREATE, DROP on db1.* to 'test'@'%' with grant option; # 为test用户添加在数据库db1上的增删改查，创建/删除操作
mysql> grant INSERT, DELETE, UPDATE, SELECT, CREATE, DROP on db1.table1 to 'test'@'%' with grant option; # 为test用户添加在数据库db1的table1表上的增删改查，创建/删除操作
mysql> show grants for 'test'@'%'; # 查看权限
```

## 删除账户

```bash
mysql> DROP USER 'root'@'172.22.244.89'
mysql> DROP USER 'test'@'%'
```



https://dev.mysql.com/doc/refman/8.0/en/creating-accounts.html

https://dev.mysql.com/doc/refman/8.0/en/grant.html

## 连接服务器

mysql -h 主机名 -u 用户名 -p

参数说明：

- **-h** : 指定客户端所要登录的 MySQL 主机名, 登录本机(localhost 或 127.0.0.1)该参数可以省略;
- **-u** : 登录的用户名;
- **-p** : 告诉服务器将会使用一个密码来登录, 如果所要登录的用户名密码为空, 可以忽略此选项。

```bash
[root@host]# mysql -u root -p
Enter password:*******
```



## mysql忘记密码重置

https://dev.mysql.com/doc/refman/8.0/en/default-privileges.html

https://www.runoob.com/mysql/mysql-install.html



## mysql可视化工具

### workbench

https://dev.mysql.com/downloads/workbench/

### beekeeper

### dbeaver

### mysql-shell

```bash
mysqlsh
MySQL Py> \sql
MySQL SQL> \connect test@localhost
Creating a session to 'test@localhost'
Please provide the password for 'test@localhost': ****
```

https://dev.mysql.com/downloads/shell/



## mysql connector

### windows

windows下的vs2019配置

（假设mysql的默认安装路径为：C:\Program Files\MySQL\MySQL Server 8.0）

1. VC++目录->包含目录。 C/C++—》常规—》附录包含目录：

   C:\Program Files\MySQL\MySQL Server 8.0\include

2. VC++目录->库目录。链接—》常规—》附加库目录：

   C:\Program Files\MySQL\MySQL Server 8.0\lib

3. 调试->环境

   Path=C:\Program Files\MySQL\MySQL Server 8.0\lib;C:\Program Files\MySQL\MySQL Server 8.0\bin;

4. 连接器->输入->附加依赖项

   libmysql.lib (c++驱动同理)



### linux

```bash
sudo apt install libmysqlcppconn-dev # c++ 驱动

sudo apt install mysql-client
sudo apt install libmysqlclient-dev #C 驱动
```





# 数据库

```mysql
show databases;          # 查看有哪些数据库
create database db-name; # 创建数据库
drop database db-name;   # 删除数据库
drop database if exists db-name;   # 删除数据库
use mysql;               # 选择数据库
```

# 数据库对象

## 表

```sql
show tables;              # 查看有哪些表
desc table table-name     # 查看表结构
describe table table-name # 查看表结构
drop table table-name     # 删除表
```

创建表

```sql
create table table-name (
	字段1 类型 [约束]
    字段2 类型 [约束]
    字段n 类型 [约束]
)
create table table-name (id int, name char) # 创建表

ALTER table class RENAME student; # 重命名表
```

修改表结构（列操作）

```sql
alter table table-name modify field varchar(12) # 修改字段类型
ALTER TABLE table_name CHANGE old_column_name new_column_name data_type; # 重命名字段 CHANGE关键字后面必须指定新的列名和数据类型。这种操作会影响到已有的索引、外键等依赖于该字段的对象，因此在进行修改之前应先确认相关信息并做好备份工作。

alter table table-name add column newfield tinyint;     # 添加一个新的字段(列)
alter table table-name drop column newfield;            # 删除一个字段(列)
```



在线修改表结构

gh-ost

pt-osc

facebook-osc

online ddl

native ddl



### 数据类型

#### 整数

| 类型         | 大小  | 范围(有符号)        | 范围(无符号)   |
| ------------ | ----- | ------------------- | -------------- |
| tinyint      | 1字节 | [-128,127]          | [0, 255]       |
| smallint     | 2字节 | [-32768, 32767]     | [0, 65535]     |
| mediumint    | 3字节 | [-2^23^, 2^23^ - 1] | [0, 2^24^ - 1] |
| int或integer | 4字节 | [-2^31^, 2^31^ - 1] | [0, 2^32^ - 1] |
| bigint       | 8字节 | [-2^63^, 2^63^]     | [0, 2^64^]     |

int(n)：注意括号的n表示**显示长度**，并不影响实际占用的存储长度（还是4）。

#### 浮点数

| 类型    | 大小                                    | 范围(有符号)                                                 | 范围(无符号)   |
| ------- | --------------------------------------- | ------------------------------------------------------------ | -------------- |
| float   | 4字节                                   | (-3.402 823 466 E+38，-1.175 494 351E-38)，0，(1.175 494 351 E-38，3.402823 466 351 E+38) |                |
| double  | 8字节                                   |                                                              |                |
| decimal | 对DECIMAL(M,D)，如果M>D，为M+2否则为D+2 | 依赖于M和D的值,例如DECIMAL(5, 2) 范围为-999.99到999.99，占用7个字 节，小数点与符号各占用一个字节 | 依赖于M和D的值 |

float(总长度， 小数点后保留的位数)：float(3,2):1.23

double(总长度，小数点后保留的位数)：double(5,2)：123.45

#### 字符串

| 类型       | 大小                                        | 用途                                  |
| ---------- | ------------------------------------------- | ------------------------------------- |
| char(n)    | n的取值范围：1-255字节。总长度为n           | 定长字符串，知道固定长度的时候用CHAR  |
| varchar(n) | n的取值范围：1-65535字节。总长度为n+1(‘\0’) | 变长字符串，经常变化的字段用varchar   |
|            |                                             |                                       |
| tinytext   | 0-255字节                                   | 短文本字符串                          |
| text       | 0-65535字节                                 | 长文本数据，能用varchar的地方不用text |
| mediumtext | 0 ~ 2^24^ -1字节                            | 中等长度文本数据                      |
| longtext   | 0 ~ 2^32^ - 1字节                           | 极大文本数据                          |
|            |                                             |                                       |
| tinyblob   | 0 ~ 255字节                                 | 不超过255个字符的二进制字符串         |
| blob       | 0 ~ 65535字节                               |                                       |
| mediumblob | 0 ~ 2^24^ -1字节                            |                                       |
| longblob   | 0 ~ 2^32^ -1字节                            |                                       |

char和varchar超过n后，字符串会被截断。

从官方文档中我们可以得知当varchar大于某些数值的时候，其会自动转换为text，大概规则如下：

-   大于varchar（255）变为 tinytext
-   大于varchar（500）变为 text
-   大于varchar（20000）变为 mediumtext



#### 日期和时间

| 类型      | 大小(字节) | 范围                                      | 格式                | 用途                                |
| --------- | ---------- | ----------------------------------------- | ------------------- | ----------------------------------- |
| DATE      | 3          | 1000-01-01~9999-12-31                     | YYYY-MM-DD          | 只存储日期                          |
| TIME      | 3          | '-838:59:59' ~ '838:59:59'                | HH:MM:SS            | 只存储时间                          |
| YEAR      | 1          | 1901 ~ 2155                               | YYYY                | 只存储年份                          |
| DATETIME  | 8          | 1000-01-01 00:00:00 ~ 9999-12-31 23:59:59 | YYYY-MM-DD HH:MM:SS | 存储日期和时间                      |
| TIMESTAMP | 4          | 1970-01-01 00:00:00/2037 年某时           | YYYYMMDD            | 存储从1970/1/1 0:0:0 到现在的时间戳 |



### 约束

#### 自增约束

##### 当删除一行时，mysql的自动递增列会自动减一吗？

当在MySQL中删除一行时，具有自动递增（AUTO_INCREMENT）属性的列的值**不会自动减少**。**自动递增列的目的是为了确保每行都有一个唯一的序号，而不是根据删除的行来递减。** 也就是说自增列可能出现序号不连续的情况。

每次插入新行时，MySQL会根据自动递增列的当前值来递增该值，而不是根据已删除的行。已删除的行的值对于自动递增列没有影响。

例如，假设有一个名为`table_name`的表，其中包含一个名为`id`的自动递增列。如果删除表中的一行，则`id`列的值不会减少。下一次插入新行时，MySQL将为新行分配一个新的`id`值，该值等于当前自动递增列的最大值加一。

以下是一个示例，说明在删除行后插入新行时自动递增列的行为：

```mysql
-- 创建一个具有自动递增列的表
CREATE TABLE table_name (
    id INT AUTO_INCREMENT PRIMARY KEY,  
    name VARCHAR(50)
);
-- 插入一些数据
INSERT INTO table_name (name) VALUES ('Row 1');
INSERT INTO table_name (name) VALUES ('Row 2');
INSERT INTO table_name (name) VALUES ('Row 3');
-- 删除一行
DELETE FROM table_name WHERE id = 2;
-- 插入新行
INSERT INTO table_name (name) VALUES ('Row 4');
-- 查看自动递增列的值
SELECT * FROM table_name;
```

以上示例中的输出将如下：

```diff
+----+------+
| id | name |
+----+------+
|  1 | Row 1 |
|  3 | Row 4 |
+----+------+
```

可以看到，删除行后插入新行时，自动递增列的值为3，而不是2。它没有受到之前删除的行的影响。

# 问题

## ERROR 1227 (42000): Access denied; you need (at least one of) the SYSTEM_USER privilege(s) for this operation

由于root用户没有SYSTEM_USER权限，把权限加入后即可解决：

```mysql
mysql> grant system_user on *.* to 'root';
```

https://www.jianshu.com/p/cc67e1dd9162



sql优化

https://www.bilibili.com/video/BV1Y5411c7F4/?spm_id_from=333.999.0.0&vd_source=c4b5fa82418420c778a8366bb840293d





数据类型

建表

删表



插入数据

更新数据

删除数据

查询数据



多表查询