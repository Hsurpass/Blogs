# NGINX

## Nginx常用命令

1. `cd /usr/local/bin/sbin/`
2. `./nginx     启动`
3. `./nginx -s stop        停止`
4. `./nginx -s quit        安全退出`
5. `./nginx -s reload    重新加载配置文件`
6. `ps aux|grep nginx    查看nginx进程`



## **nginx 文件结构**

```
...              #全局块

events {         #events块
   ...
}

http      #http块
{
    ...   #http全局块
    server        #server块
    { 
        ...       #server全局块
        location [PATTERN]   #location块
        {
            ...
        }
        location [PATTERN] 
        {
            ...
        }
    }
    server
    {
      ...
    }
    ...     #http全局块
}
```

- 1、**全局块**：配置影响nginx全局的指令。一般有运行nginx服务器的用户组，nginx进程pid存放路径，日志存放路径，配置文件引入，允许生成worker process数等。
- 2、**events块**：配置影响nginx服务器或与用户的网络连接。有每个进程的最大连接数，选取哪种事件驱动模型处理连接请求，是否允许同时接受多个网路连接，开启多个网络连接序列化等。
- 3、**http块**：可以嵌套多个server，配置代理，缓存，日志定义等绝大多数功能和第三方模块的配置。如文件引入，mime-type定义，日志自定义，是否使用sendfile传输文件，连接超时时间，单连接请求数等。
- 4、**server块**：配置虚拟主机的相关参数，一个http中可以有多个server。 与“虚拟主机”的概念有密切关系。每个server 块相当于一台虚拟主机，最常见的两个配置项是监听配置和虚拟主机的名称或IP配置 。
- 5、**location块**：配置请求的路由，以及各种页面的处理情况。 在server 块中，可以有多个。地址定向，数据缓存，和应答控制等功能都是在这部分实现。 

下面给大家上一个配置文件，作为理解。

```
########### 每个指令必须有分号结束。#################
# =========================全局块============================
# user user [grop];        # 指定可以运行nginx 服务器的用户及组。只被设置的用户及组才有权限管理
# user nobody nobody;      # 所用用户可用，默认配置
user nginx nginx; 
#user administrator administrators;  #配置用户或者组，默认为nobody nobody。

# worker_processes number | auto;   # 控制并发处理，值越大，支持的并发数越多
# worker_processes 1;               # 默认值 ，最多产生1个worker_processes
worker_processes auto;
#worker_processes 2;  #允许生成的进程数，默认为1

#pid /nginx/pid/nginx.pid;   #指定nginx进程运行文件存放地址

error_log log/error.log debug;  #制定日志路径，级别。这个设置可以放入全局块，http块，server块，级别以此为：debug|info|notice|warn|error|crit|alert|emerg
# error_log logs/error.log error;  # 可在 全局块，http 块 ,serveer 块，location 块中配置

# include file;      # 配置文件引入，可以是相对/绝对路径。指令可以放在配置文件的任意地方(任意块中)

worker_rlimit_nofile 51200;

# ===========================events 块===============================

events {
    accept_mutex on;   #设置网路连接序列化，防止惊群现象发生，默认为on
    multi_accept on;  #设置一个进程是否同时接受多个网络连接，默认为off
    #use epoll;      #事件驱动模型(默认使用epoll)，select|poll|kqueue|epoll|resig|/dev/poll|eventport
    worker_connections  1024;    #最大连接数，默认为512。注意设置不能大于操作系统支持打开的最大文件句柄数量。
}

# ==========================http块============================

http {
	# 定义 mime-type (网络资源的媒体类型)。  指定能识别前端请求的资源类型 
    include etc/nginx/mime.types;   # 引入外部文件 ，在外部文件中有定义types 块
    include       mime.types;   #文件扩展名与文件类型映射表
    
    default_type  application/octet-stream; #默认文件类型，默认为text/plain
    
    #access_log off; #取消服务日志
	#error_log /dev/null 
	#error_log off并不能关闭日志记录功能，它将日志文件写入一个文件名为off的文件中，如果你想关闭错误日志记录功能，应使用以下配置：error_log /dev/null crit;（把存储位置设置到Linux的黑洞中去 ）。
    
    log_format myFormat '$remote_addr–$remote_user [$time_local] $request $status $body_bytes_sent $http_referer $http_user_agent $http_x_forwarded_for'; #自定义格式
    access_log /var/log/nginx/access.log myFormat;  #combined为日志格式的默认值
    
    sendfile on;   #允许sendfile方式传输文件，默认为off，可以在http块，server块，location块。
    tcp_nopush on;
    sendfile_max_chunk 100k;  #每个进程每次调用传输数量不能大于设定的值，默认为0，即不设上限。
    keepalive_timeout 65;  #连接超时时间，默认为75s，可以在http，server，location块。

	#Gzip Compression
    gzip on; #开启gzip压缩功能，目的：提高传输效率，节约带宽。
    gzip_buffers 16 8k;
    gzip_comp_level 6;	#定义压缩的级别（压缩比，文件越大，压缩越多，但是cpu使用越多）
    gzip_http_version 1.1;
    gzip_min_length 256;	#限制最小压缩，小于256字节不会压缩
    gzip_proxied any;
    gzip_vary on;
    # 定义压缩文件的类型
    gzip_types
        text/xml application/xml application/atom+xml application/rss+xml application/xhtml+xml image/svg+xml
        text/javascript application/javascript application/x-javascript
        text/x-json application/json application/x-web-app-manifest+json
        text/css text/plain text/x-component
        font/opentype application/x-font-ttf application/vnd.ms-fontobject
        image/x-icon;
    gzip_disable "MSIE [1-6]\.(?!.*SV1)";

    upstream mysvr {   
      server 127.0.0.1:7878;
      server 192.168.10.121:3333 backup;  #热备
    }
    error_page 404 https://www.baidu.com; #错误页
    server {
        keepalive_requests 120; #单连接请求上限次数。
        listen       4545;   #监听端口
        server_name  127.0.0.1;   #监听地址    
        # ^~ 以某个字符路径开头请求
        location  ~*^.+$ {       #请求的url过滤，正则匹配，~为区分大小写，~*为不区分大小写。
           #root path;  #根目录
           #index vv.txt;  #设置默认页
           proxy_pass  http://mysvr;  #请求转向mysvr 定义的服务器列表
           deny 127.0.0.1;  #拒绝的ip
           allow 172.18.5.54; #允许的ip           
        } 
    }
}
```

location的匹配规则

```
空格：默认匹配，普通匹配
location / {
	root /home
}

=：精确匹配
location = /imooc/img/face1.png {
	root /home
}

~*:匹配正则表达式，不区分，大小写

~：匹配正则表达式，区分大小写

^~:以某个字符路径开头
```



上面是nginx的基本配置，需要注意的有以下几点：

1、几个常见配置项：

- 1.$remote_addr 与 $http_x_forwarded_for 用以记录客户端的ip地址；
- 2.$remote_user ：用来记录客户端用户名称；
- 3.$time_local ： 用来记录访问时间与时区；
- 4.$request ： 用来记录请求的url与http协议；
- 5.$status ： 用来记录请求状态；成功是200；
- 6.$body_bytes_s ent ：记录发送给客户端文件主体内容大小；
- 7.$http_referer ：用来记录从那个页面链接访问过来的；
- 8.$http_user_agent ：记录客户端浏览器的相关信息；

2、惊群现象：一个网路连接到来，多个睡眠的进程被同时叫醒，但只有一个进程能获得链接，这样会影响系统性能。

3、每个指令必须有分号结束。



cgi:

$\color{red} {web服务器与cgi通过环境变量、标准输入、标准输出、标准错误互相传递数据。}$

$\color{red} {CGI使外部程序与Web服务器之间交互成为可能。CGI程式运行在独立的进程中，并对每个Web请求建立一个进程，这种方法非常容易实现。}$ 

$\color{red} {但效率很差，难以扩展。面对大量请求，进程的大量建立和消亡使操作系统性能大大下降。此外，由于地址空间无法共享，也限制了资源重用。}$

fastcgi:





 

*原文地址：https://www.cnblogs.com/knowledgesea/p/5175711.html* 

references:

https://www.runoob.com/w3cnote/nginx-setup-intro.html

https://www.kuangstudy.com/bbs/1483987971375263745

fastcgi:

https://www.cnblogs.com/skynet/p/4146083.html

https://www.cnblogs.com/skynet/p/4173450.html