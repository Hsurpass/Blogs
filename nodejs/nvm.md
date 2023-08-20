ubuntu安装nvm:

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash	# 科学上网
wget -qO- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash # 二者选其一，注意wget命令里的-q参数表示--quiet，安静模式，无信息输出，看不到错误，也可去掉该参数
```



常用命令：

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



# reference:

https://blog.csdn.net/xhp312098226/article/details/131247719

https://github.com/nvm-sh/nvm/