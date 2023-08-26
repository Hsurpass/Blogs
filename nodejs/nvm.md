# 安装nvm

## windows安装nvm

下载：https://github.com/coreybutler/nvm-windows/releases

如果windows上之前安装过nodejs,一定要先卸载再安装nvm。nvm安装目录名不能有空格和中文。

### nvm命令

```bash
nvm ls or nvm list # 列出已安装的版本
nvm list available # 查找所有可用版本
nvm install <version> # 安装指定版本号（将 <version> 替换为版本号 如：nvm install 12.14.0）
nvm install lts # 安装最新的lts版本
nvm install latest #安装最新的版本
```

### 升级nvm

https://github.com/coreybutler/nvm-windows#upgrading-nvm-windows

重新执行新的installer，保证安装路径和原来的一样，这样旧的文件就会被覆盖。



## ubuntu安装nvm

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash	# 科学上网
wget -qO- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash # 二者选其一，注意wget命令里的-q参数表示--quiet，安静模式，无信息输出，看不到错误，也可去掉该参数
./install.sh
```

### 问题

trouble1:

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash
% Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0
curl: (7) Failed to connect to raw.githubusercontent.com port 443: Connection refused
```

科学上网

trouble2: Could not resolve host

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.4/install.sh | bash
% Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                Dload  Upload  Total   Spent    Left  Speed
0     0    0     0    0     0      0      0 --:--:--  0:00:09 --:--:--     0
curl: (6) Could not resolve host: raw.githubusercontent.com
```

见：https://github.com/nvm-sh/nvm/#wsl-troubleshooting

### nvm常用命令

```bash
nvm -v: 查看nvm自身版本
nvm ls: 查看已安装的版本
nvm ls-remote: 查看所有可用版本

nvm install --lts:安装最新的lts版本
nvm use --lts: 切换到最新的lts版本

nvm node :安装最新的版本
nvm use node :使用最新的版本。

nvm install 8.0.0 ：安装指定版本号的版本
nvm use 8.0.0：使用指定版本号的版本。
```

### 升级nvm

更新nvm仓库，重新执行install.sh脚本。



# reference:

https://blog.csdn.net/xhp312098226/article/details/131247719

https://github.com/nvm-sh/nvm/