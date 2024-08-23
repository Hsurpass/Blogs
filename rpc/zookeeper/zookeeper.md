下载

```bash
https://zookeeper.apache.org/releases.html
or
https://dlcdn.apache.org/zookeeper/
```

解压

```
tar -zxvf apache-zookeeper-3.8.3-bin.tar.gz
```

配置

```bash
cd apache-zookeeper-3.8.3-bin/conf/
cp zoo_sample.cfg zoo.cfg
mkdir data # 创建存储数据的目录
修改zoo.cfg:
```

```bash
dataDir=绝对路径/data # $PWD error 
```

启动

```bash
./zkServer.sh start
输出：
/usr/bin/java
ZooKeeper JMX enabled by default
Using config: xxx/apache-zookeeper-3.8.3-bin/bin/../conf/zoo.cfg
Starting zookeeper ... STARTED

./zkServer.sh status
输出：
/usr/bin/java
ZooKeeper JMX enabled by default
Using config: xxx/apache-zookeeper-3.8.3-bin/bin/../conf/zoo.cfg
Client port found: 2181. Client address: localhost. Client SSL: false.
Mode: standalone # 单机

./zkServer.sh status
./zkServer.sh --help
bin/zkServer.sh start-foreground # 在前台启动zookeeper
```

连接zookeeper服务

```bash
zkCli.sh -server 127.0.0.1:2181 # zkCli.sh help
[zk: 127.0.0.1:2181(CONNECTED) 0] help
```



集群
