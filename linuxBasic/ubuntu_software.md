# 安装chrome

```bash
# 官网下载deb包
sudo dpkg -i google-chrome*
sudo apt-get -f install
```

# 卸载chrome

```bash
dpkg --list | grep google
sudo apt --purge remove google-chrome-stable  #  --purge 这个命令会删除包及其配置文件。当你使用此命令来删除一个包时，它会不仅仅删除包本身，也会删除与该包相关的配置文件和数据文件，以及任何其他与该包关联的文件。这可以确保包在系统中被完全删除，包括其留下的任何残余文件或配置。
# apt remove: 这个命令只会删除包本身，但不会删除与该包关联的配置文件和数据文件。这意味着包的二进制文件会被删除，但与该包关联的配置文件和数据文件仍然保留在系统中，以便稍后重新安装该包时可以保留之前的配置。
```







# reference

https://www.javatpoint.com/uninstall-chrome-ubuntu