#### 安装

```text
make PREFIX=/usr/local/redis install
```

这里多了一个关键字 'PREFIX=' 这个关键字的作用是编译的时候用于指定程序存放的路径。比如我们现在就是指定了 redis 必须存放在 '/usr/local/redis' 目录。假设不添加该关键字 linux 会将可执行文件存放在 '/usr/local/bin' 目录，库文件会存放在 '/usr/local/lib' 目录。配置文件会存放在 '/usr/local/etc 目录。其他的资源文件会存放在 'usr/local/share' 目录。这里指定好目录也方便后续的卸载，后续直接 `rm -rf /usr/local/redis` 即可删除 Redis。

#### 服务器启动
    服务启动要加上配置文件，否则还是启动的本地回环(127.0.0.1)，并且密码也不会生效
    ./redis-server ../redis.conf

#### 客户端连接

指定 IP 和端口连接 redis：./redis-cli -h 127.0.0.1 -p 6379 -a 密码

-h redis 主机 IP（可以指定任意的 redis 服务器）

-p 端口号（不同的端口表示不同的redis 应用



#### referenece:

教程: https://zhuanlan.zhihu.com/p/469102289

Redis 官网：https://redis.io/

源码地址：https://github.com/redis/redis

Redis 在线测试：http://try.redis.io/

Redis 命令参考：http://doc.redisfans.com/

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

