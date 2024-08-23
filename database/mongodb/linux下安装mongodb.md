# 安装

https://www.mongodb.com/docs/v7.0/administration/install-on-linux/



docker拉取mongo镜像

https://www.mongodb.com/docs/v7.0/tutorial/install-mongodb-community-with-docker/



监听地址改为0.0.0.0

```bash
sudo vi /etc/mongod.conf
net:
  bindIp: 0.0.0.0
sudo mongod --config /etc/mongod.conf
```

or 

```bash
sudo mongod --bind_ip_all
```

https://www.mongodb.com/docs/manual/reference/configuration-options/#net-options



安装mongodb驱动

1.   通过命令安装

     ```bash
     sudo apt install libmongoc-dev
     sudo apt install libbson-dev
     ```

     

2.   通过编译源码安装

     ```bash
     sudo apt-get install libzstd-dev
     sudo apt-get install libsasl2-dev
     sudo apt-get install libsnappy-dev
     
     cmake -B build
     cmake --build build -j2
     ```

     





