

qt.qpa.plugin: Could not load the Qt platform plugin "wayland" in "" even though it was found.

```bash
sudo apt install qtwayland5
```



信号与槽

自定义信号与槽

原生c++对象之间的通信很麻烦，自定义信号与槽进行通信是Qt中最常用的开发技术，当是自定义信号与槽函数的时候，需要注意这些细节：

-   只有继承至QObject的派生类才能使用信号槽。
-   必须在头文件添加宏Q_OBJECT。
-   关键字signals:指定声明信号区域。
-   关键字[public protect private] slot:指定申明槽函数区域。

```c++
class A : public QObject
{
	Q_OBJECT
public:
	A();
signals:
	void mysignal(int);
public slots:
	void myslot();
};
```

需要注意的是：有些开发者喜欢在cpp中定义一个class，但是Q_OBJECT 这个宏只能在头文件中才能被展开。



qtquickexamples



QT是事件驱动的，常见QT事件类型：

- 键盘事件：按下和松开
- 鼠标事件：鼠标移动，按下和松开
- 拖放事件：用鼠标进行拖放。
- 滚轮事件：鼠标滚轮滚动。
- 绘屏事件：重绘屏幕的某些部分。
- 定时事件：定时器到时。
- 焦点事件：键盘焦点移动。
- 进入和离开事件：鼠标移入widget之内，或是移出。
- 移动事件：widget的位置改变。
- 大小改变事件：widget的大小改变。
- 显示和隐藏事件：widget显示和隐藏。
- 窗口事件：窗口是否为当前窗口。





查看长期支持版：

https://wiki.qt.io/Main

download:

https://www.qt.io/download-open-source

https://www.qt.io/offline-installers

qt archive:

https://download.qt.io/

https://download.qt.io/archive/



docs:

https://doc.qt.io/

http://c.biancheng.net/view/3851.html





https://github.com/masterchen/Qt-Open-Source-Project

https://www.qgis.org/en/site/about/index.html





cmake 构建 ：

https://blog.csdn.net/CUBE_lotus/article/details/128507180

https://blog.csdn.net/pointerz_zyz/article/details/129781963