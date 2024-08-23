https://blog.csdn.net/Chasingthewinds/article/details/130344853

https://blog.51cto.com/u_16213660/7280009

https://dev.mysql.com/doc/c-api/5.7/en/c-api-basic-interface-usage.html

https://dev.mysql.com/doc/connector-cpp/8.2/en/connector-cpp-installation-binary.html#connector-cpp-installation-binary-linux

https://blog.csdn.net/qq_39638989/article/details/126229189

https://blog.csdn.net/xunmeng2002/article/details/127852016

https://blog.csdn.net/qq_44918555/article/details/125153569

mysql能分布式安装吗？怎么配置？

itpub

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

systemctl is-enabled mysql   # 查看mysql是否开机自动启动后
sudo systemctl enable mysql  # 打开mysql开机自动启动
sudo systemctl disable mysql # 关闭mysql开机自动启动

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
   # mysql> alter user 'root'@'%' identified with mysql_native_password by '1111'; # unverified mysql > 5.7.9
   # mysql> update user set authentication_string=PASSWORD("1111") where user='root'; # unverified mysql < 5.7.9
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

```bash
mysql -h 主机名 -P port -u 用户名 -p
mysql -h127.0.0.1 P3306 -uroot -p1111
```

参数说明：

- **-h** : 指定客户端所要登录的 MySQL 主机名, 登录本机(localhost 或 127.0.0.1)该参数可以省略;
- **-P**：端口。
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



## 拉取mysql的docker镜像

```bash
docker pull mysql
docker run  -id --name=test_mysql -p 3306:3306 
 -v ~/mysql/conf:/etc/mysql/conf.d # 把docker中的配置文件目录映射到本机目录
 -v ~/mysql/logs:/var/log/mysql 
 -v ~/mysql/data:/var/lib/mysql
 -e MYSQL_ROOT_PASSWORD=mypassword #初始化一个密码
 mysql:5.6 # j
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

查看表

```sql
show tables;              -- 查看有哪些表
desc table table-name     -- 查看表结构
describe table table-name -- 查看表结构
SHOW COLUMNS from dbname.table_name; -- 查看表结构

SHOW CREATE TABLE test_table1; -- 查看表的详细定义
```

删除表

```
drop table table-name     -- 删除表
```

创建表

```mysql
create table table-name (
	字段1 类型 [约束]
    字段2 类型 [约束]
    字段n 类型 [约束]
)
create table table-name (id int, name char) # 创建表
```

修改表结构（列操作）

```mysql
ALTER table class RENAME student; # 重命名表

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



**行操作**

插入数据



删除数据



更新数据



查询数据







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

在`INT(n)`中，`n`用于指定**显示宽度**，但并不会限制存储的范围。这意味着，无论您指定的显示宽度是多少，`INT`类型**始终占据相同的存储空间**，并且能够存储相同的范围。

在实际使用中，指定`INT(n)`中的`n`主要用于在显示查询结果时使用，例如在命令行或某些客户端工具中显示整数时的宽度。这个参数并不会影响整数的存储或范围，因此在大多数情况下，指定`INT`类型时可以忽略这个参数。

#### 浮点数

| 类型    | 大小                                    | 范围(有符号)                                                 | 范围(无符号)   |
| ------- | --------------------------------------- | ------------------------------------------------------------ | -------------- |
| float   | 4字节                                   | (-3.402 823 466 E+38，-1.175 494 351E-38)，0，(1.175 494 351 E-38，3.402823 466 351 E+38) |                |
| double  | 8字节                                   |                                                              |                |
| decimal | 对DECIMAL(M,D)，如果M>D，为M+2否则为D+2 | 依赖于M和D的值,例如DECIMAL(5, 2) 范围为-999.99到999.99，占用7个字节，小数点与符号各占用一个字节 | 依赖于M和D的值 |

`decimal(5,2)`表示一个包含5位数字的十进制数，其中小数点后有2位小数。这意味着这个字段可以存储的数值范围是从-999.99到999.99。

float(总长度， 小数点后保留的位数)：float(3,2):1.23

double(总长度，小数点后保留的位数)：double(5,2)：123.45

#### 字符串

| 类型       | 大小                                                         | 用途                                  |
| ---------- | ------------------------------------------------------------ | ------------------------------------- |
| char(n)    | n的取值范围 [1,255], n代表字符个数。一个字符可能占用1~4个字节(汉字占用3个字节)。也就是说最大占用字节数为：255 * 4。 | 定长字符串，知道固定长度的时候用CHAR  |
| varchar(n) | n的取值范围 [1,255], n代表字符个数。                         | 变长字符串，经常变化的字段用varchar   |
|            |                                                              |                                       |
| tinytext   | 0-255字节                                                    | 短文本字符串                          |
| text       | 0-65535字节                                                  | 长文本数据，能用varchar的地方不用text |
| mediumtext | 0 ~ 2^24^ -1字节                                             | 中等长度文本数据                      |
| longtext   | 0 ~ 2^32^ - 1字节                                            | 极大文本数据                          |
|            |                                                              |                                       |
| tinyblob   | 0 ~ 255字节                                                  | 短二进制字符串                        |
| blob       | 0 ~ 65535字节                                                | 二进制字符串                          |
| mediumblob | 0 ~ 2^24^ -1字节                                             | 中等二进制字符串                      |
| longblob   | 0 ~ 2^32^ -1字节                                             | 长二进制字符串                        |

==char和varchar超过n后，字符串会被截断(mysql8报错)。==

从官方文档中我们可以得知当varchar大于某些数值的时候，其会自动转换为text，大概规则如下：

-   大于varchar（255）变为 tinytext
-   大于varchar（500）变为 text
-   大于varchar（20000）变为 mediumtext

**char(4)和varchar(4)括号中数字是代表字节数吗？**

不，`CHAR(4)` 和 `VARCHAR(4)` 中的数字不代表字节数，而是字符数。

- `CHAR(4)` 是一个定长字段，无论存储的实际字符串长度如何，它都会占用4个字符的空间。
- `VARCHAR(4)` 是一个可变长字段，它最多可以存储4个字符。实际存储的长度取决于实际字符串的长度，**加上一个额外的字节来存储长度信息**。

在UTF-8编码中，一个字符可能占用1到4个字节。所以，`CHAR(4)` 和 `VARCHAR(4)` 在UTF-8编码中可能会占用4到16个字节，具体取决于存储的字符串内容。

**varchar类型的字段存储数据时会存储数据长度吗？**

在大多数数据库系统中，存储 varchar 类型的字段时会存储数据的长度。通常情况下，varchar 类型的字段会存储实际的数据内容以及一个额外的长度信息。

这个长度信息通常以某种方式存储在数据结构中，以便数据库系统能够在读取和处理数据时知道每个 varchar 类型字段的实际长度。这个长度信息可以用于优化数据的存储和检索，以及在进行查询和索引操作时提高性能。

因此，对于大多数数据库系统来说，varchar 类型的字段在存储数据时会包含数据的实际内容以及长度信息。这样的设计可以提高数据库系统的效率和性能。

需要注意的是，具体的实现细节可能会因数据库系统而异，因此在具体的数据库系统中可能会有一些差异。但总的来说，varchar 类型的字段通常会存储数据的长度信息。

**那这个额外的长度信息存储在哪里？**

在大多数数据库系统中，varchar 类型的字段的额外长度信息通常存储在数据记录的存储格式中。具体的存储位置和方式可能因数据库系统而异，以下是一些常见的存储方式：

1. **数据记录的开头**：某些数据库系统会在数据记录的开头存储一个表示字段长度的信息。这个长度信息可以是固定长度的，也可以是动态长度的，取决于数据库系统的实现。
2. **数据记录的结尾**：另一些数据库系统可能会在数据记录的结尾存储字段的长度信息。这样的设计可以简化数据记录的存储格式，因为所有的长度信息都可以集中存储在记录的末尾。
3. **数据字典或系统表**：一些数据库系统可能会将字段的长度信息存储在系统表或数据字典中，而不是直接存储在数据记录中。这种方式可以提高数据库系统的灵活性，但可能会增加额外的查询开销。

需要注意的是，具体的实现细节可能会因数据库系统而异，不同的数据库系统可能会有不同的存储方式。这些细节通常是数据库系统的内部实现，并且可能受到数据库版本、存储引擎等因素的影响。

总的来说，**varchar 类型字段的额外长度信息通常会存储在数据记录的存储格式**中，以便数据库系统能够在读取和处理数据时知道每个 varchar 类型字段的实际长度。





#### 日期和时间

| 类型      | 大小(字节) | 范围                                      | 格式                | 用途                                |
| --------- | ---------- | ----------------------------------------- | ------------------- | ----------------------------------- |
| DATE      | 3          | 1000-01-01~9999-12-31                     | YYYY-MM-DD          | 只存储日期                          |
| TIME      | 3          | '-838:59:59' ~ '838:59:59'                | HH:MM:SS            | 只存储时间                          |
| YEAR      | 1          | 1901 ~ 2155                               | YYYY                | 只存储年份                          |
| DATETIME  | 8          | 1000-01-01 00:00:00 ~ 9999-12-31 23:59:59 | YYYY-MM-DD HH:MM:SS | 存储日期和时间                      |
| TIMESTAMP | 4          | 1970-01-01 00:00:00/2037 年某时           | YYYYMMDD            | 存储从1970/1/1 0:0:0 到现在的时间戳 |



### 约束

| 约束     | 描述 | 关键字 |
| -------- | ---- | ------ |
| 主键约束 |      |        |
| 自增约束 |      |        |
| 非空约束 |      |        |
| 默认约束 |      |        |
| 唯一约束 |      |        |
| 检查约束 |      |        |
| 外键约束 |      |        |



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