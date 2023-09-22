# 安装

https://www.mongodb.com/docs/v7.0/administration/install-on-linux/



docker拉取mongo镜像

https://www.mongodb.com/docs/v7.0/tutorial/install-mongodb-community-with-docker/



监听地址改为0.0.0.0

```bash
vi /etc/mongod.conf
net:
  bindIp: 0.0.0.0
sudo mongod --config /etc/mongod.conf
```

or 

```bash
sudo mongod --bind_ip_all
```

https://www.mongodb.com/docs/manual/reference/configuration-options/#net-options