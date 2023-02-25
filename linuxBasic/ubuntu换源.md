更新源步骤：

1. 备份

```bash
cd /etc/apt/ && sudo cp sources.list sources.list.bak
```

2. 替换源

`sudo vi sources.list`打开源配置文件， 删除原来的源(http://archive.ubuntu.com/ubuntu/)，将163的源(http://mirrors.163.com/ubuntu/)粘贴进去，保存退出。

也使用sed命令批量替换文件中的字符串:

```bash
sudo sed -i 's/archive.ubuntu.com/mirrors.163.com/g' sources.list
sudo sed -i 's/http/https/g' sources.list

sudo sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' sources.list 
```

3. 更新软件包列表


```bash
sudo apt‐get update
```

4. 升级已安装软件包(可选)

```bash
sudo apt list --upgradable 查看可更新的包
sudo apt upgrade 更新已安装的包
```




国内源：

```bash
https://mirrors.aliyun.com/ubuntu/	#阿里源
https://mirrors.163.com/ubuntu/		#网易源
https://mirrors.tuna.tsinghua.edu.cn/ubuntu/	#清华源
https://mirrors.ustc.edu.cn/ubuntu/		#中科大源
```





