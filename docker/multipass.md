安装

```bash
sudo snap install multipass	
```

https://multipass.run/install

## multipass launch

安装虚拟机镜像实例，例：

```bash
multipass launch -n [实例名] -c [cpu核数] -m [内存大小] -d [磁盘大小]
multipass launch --name k3s --cpus 2 --memory 4G --disk 10G
```

## multipass list /ls

查看已经安装的虚拟机实例

## multipass shell [vm-name]

==进入虚拟机实例==，例：

```bash
multipass shell master
```

## multipass start [vm-name]

启动虚拟机实例，例

```bash
multipass start master
```

## multipass stop [vm-name]

停止虚拟机实例，例：

```bash
multipass stop master
```

## multipass exec

在实例中执行命令，例：

```bash
multipass exec [name] -- lsb_release -a # 在实例中执行lsb_release -a
```



## multipass delete [vm-name]

删除实例

## multipass purge

清理虚拟机

配置免密登录：[ssh](#../linuxBasic/ssh.md)



## multipass mount

挂载目录

```bash
multipass mount ~/k8s/master vm-name:~/master # 将本机的~/k8s/master目录挂载到虚拟机的~/master目录
```



https://geekhour.net/