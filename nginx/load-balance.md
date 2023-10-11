# 什么是负载均衡

就是将不同的用户请求分摊到不同的服务器上。

# 负载均衡算法

## 静态算法

### 轮询(round robin)

nginx默认方式。

### 加权轮询(weighted round robin)

```nginx
upstream backend_server {
    server backend1.example.com weight=1;
    server backend2.example.com weight=2;
    server backend3.example.com weight=3 round-robin;
}
```

### ip hash

选择合适的hash函数对客户端的ip地址进行hash后，然后选择服务器。

### 随机分配

## 动态算法

### 最少连接(east connections)

根据后端服务器的连接数进行负载均衡，对连接数少的优先分配。需要实时监控服务器的连接数。

缺点：分配的服务器的响应时间可能很长。

### (最少响应时间)least time

根据服务器的最低相应时间来进行分配。需要实时监控服务器的响应时间。

缺点：分配的服务器连接数过多，导致负载不均。