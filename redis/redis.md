# redis安装

```bash
sudo apt-get install libjemalloc-dev # ubuntu试了还是没编过

sudo make PREFIX=/usr/local/redis install MALLOC=libc
```

这里多了一个关键字 'PREFIX=' 这个关键字的作用是编译的时候用于指定程序存放的路径。比如我们现在就是指定了 redis 必须存放在 '/usr/local/redis' 目录。假设不添加该关键字 linux 会将可执行文件存放在 '/usr/local/bin' 目录，库文件会存放在 '/usr/local/lib' 目录。配置文件会存放在 '/usr/local/etc 目录。其他的资源文件会存放在 'usr/local/share' 目录。这里指定好目录也方便后续的卸载，后续直接 `rm -rf /usr/local/redis` 即可删除 Redis。

## 服务器启动

    服务启动要加上配置文件，否则还是启动的本地回环(127.0.0.1)，并且密码也不会生效
    ./redis-server ../redis.conf

## 客户端连接

指定 IP 和端口连接 redis：./redis-cli -h 127.0.0.1 -p 6379 -a 密码

-h：redis 主机 IP（可以指定任意的 redis 服务器）

-p：端口号（不同的端口表示不同的redis 服务）

-a：密码

--raw：避免中文乱码

# CONFIG 配置

```bash
CONFIG GET * #获取所有配置
CONFIG GET key #获取某个字段的值

CONFIG SET key value #设置某个字段的值
```

- CONFIG GET save：指定在多长时间内，有多少次更新操作，就将数据同步到数据文件，可以多个条件配合

  ```bash
  > config get save
  1) "save"
  2) "900 1 300 10 60 10000"
  #  900 秒（15 分钟）内有 1 个更改，300 秒（5 分钟）内有 10 个更改以及 60 秒内有 10000 个更改。
  ```

- CONFIG GET requirepass：redis连接密码，默认关闭。如果配置了，需要通过`AUTH <password>`命令进行登录。

- 

[redis配置参数](https://www.runoob.com/redis/redis-conf.html)



# key 键

- SELECT dbindex：切换数据库，默认为db0。例：切换到db1：**SELECT 1**
- KEYS <key>：查找指定的key，KEYS *：查找所有key
- EXISTS <key>：检查给定key是否存在
- TYPE <key>：返回key所对应的**value值的类型**。
- DEL <key>：删除key及其所对应的值。
- DUMP <key>：序列化key
- EXPIRE <key> seconds：为key设置过期时间，单位：秒
- EXPIREAT <key> timestamp：和EXPIRE功能一样，为key设置过期时间，只是后面是timestamp(以秒为单位)时间戳
- PEXPIRE <key> milliseconds：为key设置过期时间，单位：毫秒
- PEXPIREAT <key> milliseconds-timestamp：和PEXPIRE功能一样，为key设置过期时间，只是后面是以毫秒为单位时间戳。
- TTL <key>：返回key的剩余生存时间(time to live)，单位：秒
- PTTL <key>：返回key的剩余生存时间(time to live)，单位：毫秒
- MOVE <key> dbindex：将key移动到指定的数据库db中。redis默认有16个数据库，0~15。例：**MOVE key 1**
- PERSIST <key>：移除key的过期时间，将key持久化，也就是保存到文件
- RANDOMKEY：随机返回一个key
- RENAME key newkey：修改key的名称，如果数据库中有重名的 ‘newkey’，则会覆盖。
- RENAMENX key newkey：修改key的名称，如果数据库中有重名的 ‘newkey’，则不会修改key。



# 数据类型

## string 字符串

- SET <key> <value>：设置key的值
- SETEX <key> <seconds> <value>：设置key所对应的value和过期时间，单位：秒
- PSETEX <key> <milliseconds> <value>：设置key所对应的value和过期时间，单位：毫秒。
- SETNX <key> <value>：只有在key不存在时才会设置key的值。
- SETRANGE <key> <offset> <value>：用value覆盖从偏移量offset开始的值。
- GET <key>：获取key的值
- GETRANGE <key> start end：获取key对应value的子字符串
- GETSET <key> <newvalue>：为key设置新值，返回旧值。
- MSET <key1> <value1> <key2> <value2>：同时设置多个key-value键值对
- MSETNX <key1> <value1> <key2> <value2>：同时设置多个key-value键值对，**只有当所有key值都不存在时，才会set成功**。
- MGET <key1> <key2> ... ：获取所有指定key的值
- STRLEN <key>：获取value值的长度。
- INCR <key>：如果value是数字，则将value加1，**value必须为整数。**
- INCRBY <key> <increment>：给value加上给定的增量（increment），**increment必须为整数**。
- INCRBYFLOAT <key> <increment>：给value加上给定的浮点值增量
- DECR <key>：value减1，value必须为整数。
- DECRBY <key> <decrement>：value减decrement，value和decrement必须为整数。
- APPEND <key> <value>：如果key对应的v值的类型是string，则把value追加到原来值的后面



Redis 命令参考：http://doc.redisfans.com/

https://redis.com.cn/commands.html

http://www.redis.cn/commands.html



## 哈希(hash)



## 列表（list）



## 集合（set）



## 有序集合（sorted set）





# 发布订阅



# HyperLog



# 备份与恢复



持久化



# 跳表

# 布隆过滤器

编程沉思录

https://zhuanlan.zhihu.com/p/85042394



# referenece:

教程: https://zhuanlan.zhihu.com/p/469102289

Redis 官网：https://redis.io/

源码地址：https://github.com/redis/redis

Redis 在线测试：http://try.redis.io/



redis-hashes：https://github.com/redis/redis-hashes

redis中文网：http://www.redis.cn/

​						https://www.redis.net.cn/

​						http://redis.p2hp.com/

​						https://www.redis.com.cn/

​						https://www.w3cschool.cn/redis/

​						https://my.oschina.net/u/4880637/blog/5324340



https://www.zhihu.com/question/28677076

https://mp.weixin.qq.com/s?__biz=MzkyMjIxMzIxNA==&mid=2247483878&idx=1&sn=41660c3f2567fa1cfb796ca8215f62ac&chksm=c1f68fd7f68106c196e7ccf1c60826434240e54c6a2b4530fc705dda7232d4bee513e7bce4fb&token=1821417861&lang=zh_CN#rd

https://zhuanlan.zhihu.com/p/109134543

https://www.zhihu.com/question/58463057

https://www.kancloud.cn/wepeng/php/1172789

