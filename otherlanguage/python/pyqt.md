



```
qt.qpa.plugin: Could not load the Qt platform plugin "xcb" in "" even though it was found.
This application failed to start because no Qt platform plugin could be initialized. Reinstalling the application may fix this problem.

Available platform plugins are: eglfs, linuxfb, minimal, minimalegl, offscreen, vnc, wayland-egl, wayland, wayland-xcomposite-egl, wayland-xcomposite-glx, webgl, xcb.

Aborted
```



解决：

```bash
ldd test_python/python3/lib/python3.10/site-packages/PyQt5/Qt5/plugins/platforms/libqxcb.so
#安装缺少的动态库
sudo apt-get install libxcb*
sudo apt-get install libxkbcommon*
```





中文乱码

```bash
sudo apt install fonts-noto-cjk **
sudo apt install fontconfig
sudo fc-cache -fv     # 刷新字体缓存
sudo apt install ttf-mscorefonts-installer

```

`sudo fc-cache -fv` 是一个在Linux系统中用于刷新字体缓存的命令。让我们来解释一下各个部分的含义：

- `sudo`: 这是一个用于以超级用户或管理员权限执行命令的关键字。在执行需要系统级别权限的命令时，需要在命令前加上`sudo`。
- `fc-cache`: 这是一个用于生成字体缓存信息的命令。当你安装或删除字体时，你需要更新字体缓存，以便系统能够正确地识别和使用这些字体。
- `-f`: 这是`fc-cache`命令的一个选项，表示强制刷新字体缓存。即使字体缓存看起来是最新的，也会强制重新生成。
- `-v`: 这也是`fc-cache`命令的一个选项，表示以详细模式运行命令，会输出更多的信息，包括哪些字体被扫描和加入了缓存。





https://blog.csdn.net/jerry_liufeng/article/details/120003783



# reference

[PyQt5 · PyPI](https://pypi.org/project/PyQt5/)

[PyQt5 Reference Guide — PyQt Documentation v5.15.4 (riverbankcomputing.com)](https://www.riverbankcomputing.com/static/Docs/PyQt5/index.html)