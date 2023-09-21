# 安装

## linux上安装

```bash
sudo apt update
sudo apt install mysql-server
mysql --version	# 查看mysql版本
sudo systemctl start mysql   or  sudo service mysql start # 启动mysql
sudo systemctl status mysql  or  sudo service mysql status # 查看mysql状态
sudo systemctl stop mysql or  sudo service mysql stop # 停止mysql
sudo systemctl restart mysql   or  sudo service mysql restart # 重启mysql
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
   mysql> alter user 'root'@'%' identified by '1111'; # %表示远端所有地址可以连接mysql服务
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
   mysql> update user set host='%' where user='root' # 设置root访问权限为所有ip，<风险>
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

# 数据库

## 查看有哪些数据库

```mysql
show databases
```

## 创建数据库



## 删除数据库





# 数据库对象



# 问题

## ERROR 1227 (42000): Access denied; you need (at least one of) the SYSTEM_USER privilege(s) for this operation

由于root用户没有SYSTEM_USER权限，把权限加入后即可解决：

```mysql
mysql> grant system_user on *.* to 'root';
```

https://www.jianshu.com/p/cc67e1dd9162