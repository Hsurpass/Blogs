```bash
docker run --name container-name -v /my/mysql/conf:etc/mysql/conf.d -p 3306:3306 -e MYSQL_ROOT_PASSWORD=my-password -d mysql:tag
```

<==> docker-compose

```bash
networks:
  default:
    name: host
version: '3' 	# 代表docker-compose的版本
services: 		# 一个services下可以有多个service
  container-name: # 容器名 代表一个service
    image: mysql:tag # 所要拉取的镜像
    working_dir: /workspace # 代表services的工作目录
    tty: true # 代表容器后台运行，同 -d
    volumes: # 主机目录和docker中目录相互映射
      - "/my/mysql/conf:etc/mysql/conf.d"
    ports: # 端口映射
      - "3306:3306"
    ports:
      - ${PORT}:3306 # 动态指定端口
    environment: # 环境变量
      - MYSQL_ROOT_PASSWORD: xxx
      - COMPOSE_PROJECT_NAME
    command: echo "I'm running ${COMPOSE_PROJECT_NAME}"
```

在 Docker Compose 配置文件中，`version` 字段表示了使用的 **Docker Compose 文件格式的版本**。这个字段指定了 Docker Compose 配置文件中可以使用的语法和功能。不同的版本可能支持不同的特性和语法，因此指定正确的版本是很重要的。

目前，Docker Compose 支持多个版本，每个版本对应不同的语法和功能。常见的版本包括 "1", "2", "2.1", "3", "3.1", "3.2" 等。每个版本都有其特定的语法和支持的功能，例如网络定义、服务扩展、依赖关系等。

当你创建一个 Docker Compose 配置文件时，你需要根据你要使用的功能和语法来选择合适的版本号。通常来说，选择最新的稳定版本是一个不错的选择，因为它会包含最新的特性和改进。

例如，一个使用 "3.1" 版本的 Docker Compose 配置文件可能会包含一些 "3.1" 版本所支持的特性和语法，而这些特性和语法可能在较旧的版本中不可用。

```bash
# 创建实例 | 执行这个命令就创建出 .yml 里面配置的 image 实例，有点像 docker run
# 创建实例后，我们可以用 docker-compose stop / docker-compose start 启动和暂停实例
docker-compose up -d

# 删除实例
docker-compose down

# 列出目前正在运行相关容器服务
docker-compose ps

# 启动
docker-compose start

# 暂时
docker-composr stop

# 重启
docker-compose restart
```

## 修改 .yml 文件

我们现在已经知道，我们使用 docker-compose up 命令可以生成一个运行实例，利用 up 生成出来的实例，我们可以使用 start or stop 进行相关的启动关闭服务。

但是现在是这样的，我们更改了 docker-compose.yml 文件后，例如我们想更改某个端口，然后我们在 restart 重启服务，会读取到更新吗？ 答案是不会的，更改了 .yml 文件之后，需要再次使用 docker-compose up 更新。

```bash
// 更新 .yml 文件
sudo docker-compose up
```



例：一个博客系统启动时需要先启动数据库(A), 再启动身份验证服务(B)，最后启动web服务(C)

```bash
version: "3.8"
services:
  A:
   image: "a image"
   deploy:
     resources:
       limits:
         cpus: "0.5" #限制cpu使用率为50%
         memory: 256M #限制内存使用量为256MB
  B:
    image: "b iamge"
    depends_on:
     - A
  C:
    image: "c image"
    depends_on: 
     - B
```







reference:

[试用 Docker Compose |Docker 文档 --- Try Docker Compose | Docker Docs](https://docs.docker.com/compose/gettingstarted/)

