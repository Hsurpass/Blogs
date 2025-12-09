

# 服务端

安装其他版本: 

https://www.postgresql.org/download/

https://www.postgresql.org/download/linux/ubuntu/

```shell
sudo apt update
# 安装ubuntu自带版本
sudo apt install postgresql postgresql-client # postgresql-contrib

sudo service postgresql status
sudo service postgresql start
sudo service postgresql stop

sudo systemctl start postgresql
sudo systemctl status postgresql
sudo systemctl stop postgresql

systemctl is-enabled postgresql   # 查看postgresql是否开机自动启动后
sudo systemctl enable postgresql  # 打开postgresql开机自动启动
sudo systemctl disable postgresql # 关闭postgresql开机自动启动
```

postgresql-contrib 是 PostgreSQL 数据库的一个官方扩展模块，提供了一系列额外的功能和工具，可用于增强 PostgreSQL 数据库的功能性。这个扩展模块包含了许多有用的不同功能，例如：

1. 数据库扩展功能：提供了额外的数据类型、函数和运算符，用于数据分析、地理信息系统（GIS）支持等。
2. 数据库连接：提供了一些额外的数据库连接方法，例如 dblink、uuid-ossp 等。
3. 文本搜索：提供了全文搜索相关的功能，例如向量空间搜索、文本检索等。
4. 全文搜索配置：提供了文本搜索配置选项，可以用于定制全文搜索的行为。
5. 其他功能：还包含了一些其他有用的功能，例如 pg_trgm（用于模糊查询）、pgcrypto（用于数据加密解密）等。

安装 PostgreSQL-contrib 扩展模块后，你可以根据需要启用特定的扩展，并利用这些功能来满足数据库应用程序的需求。请注意，安装该扩展模块并不会自动启用所有功能，通常需要手动启用所需的功能。



# 客户端

https://wiki.postgresql.org/wiki/PostgreSQL_Clients#EMS_SQL_Manager_for_PostgreSQL_Freeware

psql:

https://www.postgresql.org/docs/current/app-psql.html

```sql
# 切换到PostgreSQL用户（默认为postgres）：
sudo -i -u postgres
# 进入PostgreSQL命令行界面：
psql
# or  direct
psql -U postgres -d postgres -h 127.0.0.1 -p 5432 # -U:指定用户 -d: 指定数据库，默认是postgresql carizon

\l # 查看现有数据库
\c 数据库名 # 切换数据库 
\q # 退出sql命令行界面
\password postgres # 修改postgres数据库密码
\conninfo # 查看连接信息
\du # 查看用户权限
\dt # 列出当前数据库中的所有表，以及这些表的所有者和访问权限

CREATE USER myuser WITH PASSWORD 'password'; # 创建用户
GRANT ALL PRIVILEGES ON DATABASE mydatabase TO myuser; # 为用户分配权限
create database test with owner=postgres encoding='UTF-8';
drop database test;
```

```bash
# psql执行sql文件
psql -h 主机名 -p 端口号 -U 用户名 -d 数据库名 -a -f SQL文件名.sql
```

- `-a`：这是可选的，但它允许你查看发送到服务器的命令（包括SQL文件中的命令）。
- `-f SQL文件名.sql`：这是你要执行的SQL文件的名称和路径。

pgcli:

https://www.pgcli.com/

```bash
pip install pgcli
$ pgcli -h localhost -U username -W '@postgres' -d app_db 
# 列出本地PostgreSQL服务器上的所有数据库
$ pgcli -h localhost -U your_username -l
```

```bash
# 注意：在密码中使用 @ 或特殊符号时，请对其进行编码并引用。
$ pgcli 'postgresql://amjith:%40postgres@localhost:5432/app_db' # %40代表@
$ pgcli postgres://username:password@example.com:5432/app_db 
```

1. **`postgres://`**：这是 URI scheme，它标识了后面提供的字符串是一个用于连接 PostgreSQL 数据库的 URI。
2. **`username`**：这是用户名，用于连接到 PostgreSQL 数据库的用户。
3. **`:password`**：这是与上面用户名关联的密码。注意，密码部分在 URI 中是直接跟在用户名后面的，它们之间由冒号（`:`）分隔。
4. **`@example.com`**：这是数据库服务器的主机名或 IP 地址。
5. **`:5432`**：这是数据库服务器的端口号。默认情况下，PostgreSQL 使用 5432 端口，但这里明确指定了这一点。
6. **`/app_db`**：这是要连接的数据库的名称。

pgadmin:

https://www.pgadmin.org/download/pgadmin-4-apt/



# 数据类型

## 数值型



## 字符串



## 布尔



## JSON

```sql
CREATE TABLE orders (
    id SERIAL PRIMARY KEY,
    data JSONB
);
```



```sql
CREATE TABLE <table_name> (
	id SERIAL PRIMARY KEY,
	title VARCHAR(200),
    content TEXT,
    tags TEXT[] # 数组类型， 如：存储一篇文章的所有标签。
);
INSERT INTO <table_name> (field1, field2, field3) VALUES (value1, value2, value3);

UPDATE <table_name> SET <age = 10> WHERE name = "a";

DELETE FROM <table_name> WHERE id = 1;
```









# postgis

```bash
sudo apt install postgresql-contrib
sudo apt install postgis

sudo -i -u postgres
psql
CREATE DATABASE mygisdb;
\c mygisdb

# 创建POSTGIS扩展
CREATE EXTENSION postgis;
CREATE EXTENSION postgis_topology;
# 验证安装
SELECT PostGIS_Version();
select postgis_full_version();	
```

![image-20240627210052650](/home/user/me/Blogs/database/postgresql/image/image-20240627210052650.png)







## function

### st_geomfromtext



### st_geogfromtext





修改表结构

```bash
```





查询记录一某两个字段和记录二某两个字段相等的记录。

```sql
SELECT t1.*, t2.*
FROM table1 t1
JOIN table1 t2
  ON t1.a = t2.a AND t1.b = t2.b
WHERE t1.id != t2.id

SELECT *
FROM table1 t1
WHERE EXISTS (
    SELECT 1 FROM table1 t2
    WHERE t1.a = t2.a AND t1.b = t2.b AND t1.id <> t2.id
)
```

“自连接 vs EXISTS”查询差异问题。

## 原因分析

### 第一条（JOIN）

- 这是**自连接**，每对满足条件的 `(t1, t2)` 都会返回一行。
- 如果有3条记录的 `from_link_id, to_link_id` 相同，则会产生 3×2=6 行（每行都和其他两条配对，除了自己）。
- 总之，**会有重复的 t1 记录**，因为每个 t1 可能和多个 t2 匹配。

### 第二条（EXISTS）

- 这是**筛选 t1**，只返回 t1 的表结构，每条 t1 只会在结果中出现一次。
- 只要存在**至少一条不同 id 的记录**（from_link_id, to_link_id 都相同），就选它。
- **不会有重复**，每条 t1 只可能出现 0 或 1 次。

------

## 举例说明

假设有如下数据：

| id   | a    | b    |
| ---- | ---- | ---- |
| 1    | 100  | 200  |
| 2    | 100  | 200  |
| 3    | 100  | 200  |
| 4    | 300  | 400  |

- 用 JOIN，结果是 (1,2), (1,3), (2,1), (2,3), (3,1), (3,2) 共6条。
- 用 EXISTS，id 为1、2、3的记录都至少有一个“兄弟”，所以只返回3条（id=1,2,3）。

------

## 总结

- **JOIN**：结果数 = 某组内记录数的==排列组合==（会重复，行数多）。
- **EXISTS**：结果数 = 满足条件的 t1 记录数（每条只出现一次）。

------

### 如果你只关心“有无重复组的记录”，用第二种（EXISTS）；

如果你想看“所有配对”，用第一种（JOIN）。

如需“唯一重复组”所有成员，且无重复，可用(distinct)：

```sql
SELECT DISTINCT t1.*
FROM table1 t1
JOIN table1 t2
  ON t1.from_link_id = t2.from_link_id AND t1.to_link_id = t2.to_link_id
WHERE t1.id != t2.id
```

------

**核心原因：JOIN会重复行，EXISTS不会。**

# storage engine

[Postgres存储引擎](https://zhuanlan.zhihu.com/p/622596175?utm_id=0)

[PostGIS 插件](https://docs.shanhe.com/v6.1/database/postgresql/manual/postgis/)

https://github.com/postgis/

https://trac.osgeo.org/postgis/

[PostGIS教程一：PostGIS介绍](https://blog.csdn.net/qq_30430463/article/details/132229587)

https://blog.csdn.net/G_D0120/article/details/136989516

# reference 

[PostgreSQL Documentation](https://www.postgresql.org/docs/current/index.html)

[Postgres存储引擎](https://zhuanlan.zhihu.com/p/622596175?utm_id=0)

[【PostgreSQL】从零开始:（一）初识PostgreSQL](https://circle-dba.blog.csdn.net/article/details/134957163)

https://circle-dba.blog.csdn.net/category_12524941_2.html

