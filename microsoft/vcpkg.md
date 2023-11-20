```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install libevent

vcpkg.exe list #查看已经安装的库
vcpkg.exe update #列出可以升级的包
vcpkg.exe upgrade #更新已经安装的包
```



在使用 VCPKG 下载和安装软件包时，默认情况下使用 HTTPS 协议，如果你想改为使用 SSH 协议，可以在运行 vcpkg 命令时添加 --git-protocol=ssh 标志。 例如，如果你想从 Github 的 SSH 地址下载 boost 库，可以使用以下命令：

```bash
scss
.\vcpkg install boost:x64-windows --git-protocol=ssh
```

注意：由于 VCPKG 不支持私有的 Git 仓库，所以你只能从公开的 Git 地址下载软件包。另外，在 VCPKG 下载软件包时，需要先配置好你的 ssh key ，以确保可以正常访问 Git 服务器。





https://github.com/Microsoft/vcpkg