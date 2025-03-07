# 安装

## wsl上安装docker（windows）

```
下载 Docker Desktop Installer.exe
双击运行 选择 'Use WSL 2 instead of Hyper-V' 安装
启动
```



[WSL 2 上的 Docker 远程容器入门](https://learn.microsoft.com/zh-cn/windows/wsl/tutorials/wsl-containers)

[Install Docker Desktop on Windows](https://docs.docker.com/desktop/install/windows-install/)



## 在linux上安装

[Install Docker Desktop on Linux](https://docs.docker.com/desktop/install/linux-install/)

[Install Docker Desktop on Ubuntu](https://docs.docker.com/desktop/install/ubuntu/)

# 仓库

仓库中存放镜像，类似于github中存放代码。

# 镜像

镜像=仓库名+tag.

## docker images

列出本地都有哪些镜像

```bash
hchy@DESKTOP-EI7DNUT:~$ sudo docker images
REPOSITORY    TAG       IMAGE ID       CREATED        SIZE
hello-world   latest    9c7a54a9a43c   2 months ago   13.3kB

#REPOSITORY: 镜像所在的仓库
#TAG: 镜像的标签
#IMAGE ID: 镜像id
#CREATED: 该镜像创建的时间
#SIZE：镜像大小
```

一个仓库中可以有多个tag，一个tag表示一个版本。比如ubuntu仓库中有16.04,20.04等多个版本。用`REPOSITORY:TAG`表示特定版本的镜像，不指定tag则为`REPOSITORY:latest`。

## docker search

查找镜像

```bash
hchy@DESKTOP-EI7DNUT:~$ sudo docker search ubuntu
NAME                             DESCRIPTION                                     STARS     OFFICIAL   AUTOMATED
ubuntu                           Ubuntu is a Debian-based Linux operating sys…   16164     [OK]
websphere-liberty                WebSphere Liberty multi-architecture images …   296       [OK]
open-liberty                     Open Liberty multi-architecture images based…   61        [OK]
neurodebian                      NeuroDebian provides neuroscience research s…   102       [OK]
ubuntu-debootstrap               DEPRECATED; use "ubuntu" instead                52        [OK]
ubuntu-upstart                   DEPRECATED, as is Upstart (find other proces…   114       [OK]
ubuntu/nginx                     Nginx, a high-performance reverse proxy & we…   96
ubuntu/cortex                    Cortex provides storage for Prometheus. Long…   3
```

- **NAME**：仓库名称。
- **DESCRIPTION**：描述信息
- **stars:** 类似 Github 里面的 star，表示点赞、喜欢的意思。
- **OFFICIAL**：是否官方发布。
- **AUTOMATED**：自动构建。



## docker pull

拉取镜像

```bash
sudo docker pull ubuntu:20.04	#不指定tag,则拉取最新的，即ubuntu:latest
```



## docker rmi

删除镜像

```bash
sudo docker rmi hello-world:latest  or  sudo docker rmi image-id
```

## docker commit

更新镜像

```bash
sudo docker commit -m="update software" -a="作者" e218edb10161 仓库名:tag 
sudo docker commit -m="666" -a="hcy" 9b4e778b2924 hchy/hello-new:v1
```

- -m: 提交的描述信息
- -a: 执行镜像作者
- e218edb10161：**容器ID**
- hchy/hello-new:v1 ：指定新的镜像名。

**docker commit命令不会直接将镜像上传到远程仓库**，而是将镜像保存在本地。

使用docker commit命令后，需要使用docker push命令将本地镜像推送到远程仓库。推送镜像时需要先使用docker login命令登录到远程仓库，然后使用格式为`docker push [registry-url]/[image-name]:[tag]`的命令将镜像推送到远程仓库中指定位置。

## docker build

从0开始构建一个镜像

1. 创建一个[Dockerfile](#Dockerfile)
2. 执行 `sudo docker build -t xxx/ubuntu:20.04 .`
   - -t(--tag): 指定要创建的目标镜像名
   
   - . ：Dockerfile文件所在的目录，可以指定绝对路径。docker build 命令得知这个路径后，会将路径下的**所有内容**打包。
   
     **注意**：上下文路径下不要放无用的文件，因为会一起打包发送给 docker 引擎，如果文件过多会造成过程缓慢。

-   --no-cache:

    ```bash
    docker build --no-cache -t myImage:myTag myPath/
    ```

    Docker 建议您定期重建 Docker 映像，以防止已解决的已知漏洞。重建时，请使用该选项 `--no-cache` 来避免缓存命中并确保全新下载。

## docker tag

设置镜像标签

```bash
sudo docker tag 84e8b2220c03 hcy/hello-world:dev
```

- 84e8b2220c03：**镜像ID**
- hcy/hello-world:dev ：用户名/仓库源名:镜像标签名。



## docker save

将指定镜像保存为文件

```bash
docker save -o myubuntu.tar ubuntu:20.04
docker save ubuntu:20.04 > myubuntu.tar 
```

- -o, --output string：指定输出的文件名。

## docker load

导入镜像

```bash
docker load -i myubuntu.tar
docker load < myubuntu.tar
```

-  -i, --input string: 指定要导入的文件
-  -q, --quiet：输出简要信息



# 容器

## docker create(创建容器)

创建一个容器并不启用它

```bash
docker create  --name myrunoob  nginx:latest 
```



## docker run(创建容器)

新建一个容器，启动后并进入。

```bash
docker run -t -i ubuntu:15.10 /bin/bash 
```

- -t: 表示分配一个伪终端（pseudo-TTY）。

- -i: 表示保持标准输入打开，以便可以与容器进行交互。

- -d (--detach): **使容器在后台运行**，并且不会进入容器。(守护进程)

- ubuntu:15.10：指定使用15.10版本的ubuntu镜像来启动容器。

  如果你不指定一个镜像的版本标签，例如你只使用 ubuntu，docker 将默认使用 **ubuntu:latest** 镜像。

- /bin/bash: 放在镜像名后的是命令，这里我们希望有个交互式 Shell，因此用的是 /bin/bash。

- -u: 指定用户进入容器。

  ```bash
  sudo docker exec -it -u root 容器名称 /bin/bash		#指定用户进入容器 -u root
  ```

- --name string：为容器添加一个名字。

- --rm: 指定在容器退出时自动删除容器。这样可以确保在容器退出后不会留下无用的容器占用存储空间。

-  --restart string：当容器退出时应用重启策略(默认为“no”)。

- -P: Publish all exposed ports to random ports. 将所有公开的端口发布到随机端口。将容器内部使用的网络端口随机映射到我们使用的主机上。

  ```bash
  docker run -d -P training/webapp python app.py
  ```

- -p: 映射容器内部的端口到指定的主机端口。

  ```bash
  docker run -d -p 5000:5000 training/webapp python app.py
  ```

  可以指定绑定到特定的地址：

  ```bash
  docker run -d -p 127.0.0.1:5001:5000 training/webapp python app.py	#将容器内端口5000绑定到主机地址和端口127.0.0.1:5001上
  ```

  还可以指定使用udp协议，默认tcp.

  ```bash
  docker run -d -p 127.0.0.1:5000:5000/udp training/webapp python app.py
  ```

  因为本地程序无法直接连接到docker内的服务，所以要把docker内的端口映射到外面

  ![image-20240209173557100](image/image-20240209173557100.png)

  ![image-20240209173859619](image/image-20240209173859619.png)

- -v：数据卷（共享文件夹）：宿主机与容器之间共享数据，容器与容器之间共享数据。

  ```bash
  docker run -it -v /root/host/data:/root/docker/data ubuntu:15.10
  ```

   例：

  ```bash
  docker run --rm -ti -v "$PWD:/opt/workspace" ghcr.io/opendds/opendds:latest-release
  # -v "$PWD:/opt/workspace": 这个参数用于将主机的当前工作目录（由 $PWD 变量表示）挂载到容器内的 /opt/workspace 目录。这样做的目的是将主机上的文件和目录共享到容器中，以便在容器内进行操作。
  #ghcr.io/opendds/opendds:latest-release: 这是指定要运行的 Docker 镜像的名称和标签。在这个例子中，它指定了从 GitHub Container Registry 中获取 opendds 镜像的 latest-release 标签。这意味着它将从 GitHub Container Registry 下载最新的 OpenDDS 镜像并在容器中运行。
  ```

  执行docker run创建容器时没有使用-v 参数挂载目录，还能在进入容器后挂载目录吗？

  答：**不能**。在执行`docker run`命令创建容器时，如果没有使用`-v`或`--volume`参数挂载目录，那么在容器创建之后，是无法在进入容器后再挂载目录的。`-v`参数用于在创建容器时挂载主机上的目录到容器内的目录，实现文件和数据的共享。

  如果需要在容器运行时挂载目录，可以考虑使用 [docker cp](# docker cp) 命令将文件或目录复制到容器中，或者通过其他方式（如FTP、SCP等）将文件或目录传输到容器中。但请注意，这些方式并不能实现目录的挂载，而是简单的文件或目录复制。

  因此，如果需要在容器内访问主机上的目录，建议在创建容器时就使用`-v`参数进行挂载。如果容器已经创建且没有挂载目录，那么可能需要重新创建容器并挂载所需的目录。

  

- --network

  将容器连接到指定的网络。

  ```bash
  $ docker run -itd --name test1 --network test-net ubuntu /bin/bash #运行一个容器test1并连接到网络test-net上
  ```


## 数据卷容器(volume)

```bash
#创建数据卷容器
docker run -it --name=c1 -v /volume centos:7
#根据数据卷容器创建新容器
docker run -it --name=c2 --volumes-from c1 centos:7
```





## docker ps(查看容器)

查看都有哪些容器

- -a: 查看所有容器。
- -q: 只显示容器ID。
- -l: 查询最后一次创建的容器。

## docker start

如果某个容器状态是已经退出(status: Exited)，可以使用`docker start 容器id`来启动容器

开启所有容器

```bash
sudo docker start $(docker ps -a -q)
```



## docker restart



## docker stop

批量停止docker容器：

```bash
sudo docker stop $(docker ps -a | grep "xxx" | awk '{print $1}')	#root权限 "xxx"可以是镜像ID
sudo docker ps -a | awk '{print $1}' | xargs docker stop	#root权限
```

停止所有容器：	

```bash
sudo docker stop $(docker ps -q)
```



## docker exec(进入容器)

```bash
docker exec [OPTIONS] CONTAINER COMMAND [ARG...]
               选项      容器ID     命令   参数...
```

退出容器时不会使容器退出。

```bash
sudo docker exec -it 容器ID /bin/bash
```

## docker attach

退出容器时会使容器退出。推荐使用docker exec.

## docker rm(删除容器)

删除停止的容器，如果容器还在运行，使用`docker stop`停止。

批量删除容器

```bash
sudo docker rm $(sudo docker ps -a | grep "xxx" | awk '{print $1}')	#root权限 "xxx"可以是Exited
sudo docker ps -a | awk '{print $1}' | xargs docker rm
```

删除所有已经停止的容器：

```bash
docker rm $(docker ps -a -q)
```



## 退出容器

exit



## docker import

导入容器快照到镜像

```bash
sudo docker import ubuntu.tar my/ubuntu:v1
```

也可以通过指定 URL 或者某个目录来导入，例如：

```bash
sudo docker import http://example.com/exampleimage.tgz example/imagerepo
```



## docker export

导出**容器快照**到本地文件。

```bash
sudo docker export b8fb0b91c64d > ubuntu.tar
```

## docker logs

查看docker 容器内部日志。Usage:  `docker logs [OPTIONS] CONTAINE`

-f: 类似于tail -f



## docker container

- prune：清除所有停止的容器

  ```bash
  docker container prune
  ```

## docker top

查看容器内部运行的进程。`docker top 容器ID/名字`

## docker port

查看容器的端口映射。`docker port 容器ID或者容器名`

## docker inspect

```bash
sudo docker inspect <container_id>	#查看容器的配置和状态信息
```



## docker cp

```bash
# 从容器中将文件拷贝到主机上
docker cp <container_name_or_id>:/path/to/container/file /path/to/host/file
# 从主机上将文件拷贝到容器中
docker cp /path/to/host/file <container_name_or_id>:/path/to/container/file
```





# docker网络

## docker network

- create

  -  -d, --driver string: 指定网络类型，有bridge(默认)，host。

  ```bash
  docker network create test-net
  ```

  

- ls

  ```bash
  root@DESKTOP-EI7DNUT:~# docker network ls
  NETWORK ID     NAME       DRIVER    SCOPE
  f8863d53aa9a   bridge     bridge    local
  fef96c6cc1b0   host       host      local
  6842921a30e5   none       null      local
  d0cc7d639bcd   test-net   bridge    local
  ```

## 使两个容器互联

```bash
docker network create -d bridge test-net	#创建一个网络
docker run -itd --name test1 --network test-net ubuntu /bin/bash #test1连接到test-net上
docker run -itd --name test2 --network test-net ubuntu /bin/bash #test2连接到test-net上

docker exec -it test1 /bin/bash && ping test2	#进入到test1中，并ping test2
docker exec -it test2 /bin/bash && ping test1	#进入到test2中，并ping test1
```

```bash
apt-get update
apt install iputils-ping
```

如果有多个容器之间需要互相连接，推荐使用 Docker Compose。



# 制作自己的ubuntu镜像

```bash
docker commit -a "xxx" -m "test" 23c3b7d70a03(容器) test:0.1
docker login
docker tag test:0.1 joyoo/test:0.1
docker push joyoo/test:0.1
```



1. 拉取官方Ubuntu镜像。

```bash
docker pull ubuntu
```

2. 创建一个新的Docker容器并在其中安装软件。

```bash
docker run -d --name my-ubuntu-container ubuntu apt-get update apt-get install -y <package-name>
```

3. 将Docker容器导出为镜像。

```bash
docker commit my-ubuntu-container my-ubuntu-image
```

4. 删除Docker容器。

```bash
docker rm my-ubuntu-container
```

5. 上传镜像到自己的仓库。 首先，需要使用`docker login`命令登录到自己的仓库。

```bash
docker login -u <username> -p <password> <registry-url>
```

然后，使用`docker push`命令将镜像上传到仓库。

```bash
docker push <registry-url>/<image-name>:<tag>
```

其中，`<username>`是登录仓库的用户名，`<password>`是登录仓库的密码，`<registry-url>`是仓库的URL，`<image-name>`是镜像名称，`<tag>`是标签。

例如，如果要将镜像上传到名为`myrepo`的仓库，并使用标签`14.04`，则可以使用以下命令：

```bash
docker login -u myusername -p mypassword myrepo.com
docker push myrepo.com/my-ubuntu:14.04
```



############################################################################



使用 Docker 制作镜像并上传到镜像仓库（如 Docker Hub）的大致步骤如下：

### 1. 编写 `Dockerfile`
Dockerfile 是用来定义镜像内容的文件。

一个简单的 `Dockerfile` 示例：

```Dockerfile
# 使用基础镜像
FROM ubuntu:20.04

# 设置镜像作者信息
LABEL maintainer="you@example.com"

# 安装一些软件包
RUN apt-get update && apt-get install -y curl

# 设置工作目录
WORKDIR /app

# 复制本地文件到镜像中
COPY . /app

# 暴露端口
EXPOSE 8080

# 运行命令
CMD ["bash"]
```

### 2. 构建镜像
在 Dockerfile 所在的目录下执行以下命令，构建镜像：

```bash
docker build -t your_image_name:tag .
```

`your_image_name` 是你希望给镜像取的名字，`tag` 是你给镜像打的标签（例如 `v1.0`）。最后的 `.` 表示当前目录。

例如：

```bash
docker build -t myapp:v1.0 .
```

### 3. 运行镜像
在构建完镜像后，可以使用以下命令运行它：

```bash
docker run -d -p 8080:8080 your_image_name:tag
```

例如：

```bash
docker run -d -p 8080:8080 myapp:v1.0
```

### 4. 登录到 Docker Hub
要上传镜像到 Docker Hub，首先需要登录。如果你还没有 Docker Hub 账号，可以在 [Docker Hub](https://hub.docker.com) 上创建一个账号。

使用以下命令登录：

```bash
docker login
```

系统会提示你输入 Docker Hub 的用户名和密码。

### 5. 给镜像打标签
为了上传到 Docker Hub，你需要给镜像打上 Docker Hub 仓库的标签：

```bash
docker tag your_image_name:tag dockerhub_username/repository_name:tag
```

例如：

```bash
docker tag myapp:v1.0 mydockerhub/myapp:v1.0
```

### 6. 上传镜像到 Docker Hub
使用以下命令将镜像推送到 Docker Hub：

```bash
docker push dockerhub_username/repository_name:tag
```

例如：

```bash
docker push mydockerhub/myapp:v1.0
```

### 7. 在 Docker Hub 上验证
登录到 Docker Hub 查看你刚刚上传的镜像，确认是否成功。

---

总结：

1. 编写 `Dockerfile`
2. 构建镜像：`docker build -t your_image_name:tag .`
3. 运行镜像：`docker run -d -p 8080:8080 your_image_name:tag`
4. 登录 Docker Hub：`docker login`
5. 给镜像打标签：`docker tag your_image_name:tag dockerhub_username/repository_name:tag`
6. 上传镜像：`docker push dockerhub_username/repository_name:tag`

这样就可以将你的镜像制作并上传到 Docker Hub。



# reference

https://blog.csdn.net/m0_51929611/article/details/127208448