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
```

https://learn.microsoft.com/zh-cn/windows/wsl/tutorials/wsl-database#install-mysql

## windows上安装

https://www.runoob.com/mysql/mysql-install.html

## 安装完成后创建密码

Mysql安装成功后，默认的root用户密码为空，你可以使用以下命令来创建root用户的密码：

```bash
[root@host]# mysqladmin -u root password "new_password";
```

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

https://www.runoob.com/mysql/mysql-install.html

# 数据库

## 查看有哪些数据库

```mysql
show databases
```

## 创建数据库



## 删除数据库





# 数据库对象

