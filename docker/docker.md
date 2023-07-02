docker命令

exec

```bash
sudo docker exec -it -u root 容器名称 /bin/bash		#指定用户进入容器 -u root
```



ps 

列出所有容器

```bash
docker ps -a
```

start

开启所有容器

```bash
sudo docker start $(docker ps -a -q)
```





stop

批量停止docker容器：

```bash
sudo docker stop $(docker ps -a | grep "xxx" | awk '{print $1}')	#root权限
sudo docker ps -a | awk '{print $1}' | xargs docker stop	#root权限
```

停止所有容器：

```bash
sudo docker stop $(docker ps -q)
```



rm

批量删除容器

```bash
sudo docker rm $(docker ps -a | grep "xxx" | awk '{print $1}')	#root权限
sudo docker ps -a | awk '{print $1}' | xargs docker rm
```

删除所有已经停止的容器：

```bash
docker rm $(docker ps -a -q)
```





# reference

https://blog.csdn.net/m0_51929611/article/details/127208448