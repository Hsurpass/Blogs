



###### mklink

**语法:**

``` mklink [[/d] | [/h] | [/j]] <link> <target> ```

**参数：**

| 参数       | 说明                                                    |
| :--------- | :------------------------------------------------------ |
| /d         | 创建目录符号链接。 默认情况下，此命令创建文件符号链接。 |
| /h         | 创建硬链接而不是符号链接。                              |
| /j         | 创建目录交接点。                                        |
| `<link>`   | 指定要创建的符号链接的名称。                            |
| `<target>` | 指定新 (链接) 的相对或绝对路径。                        |
| /?         | 在命令提示符下显示帮助。                                |

**硬链接**

```
mklink /h B.txt F:\A.txt
```

在文件资源管理器上看，“B.txt”与“A.txt”占用同样大小的空间，其实这个数据并不用去理会，硬链接相当于给文件的数据多创建了一个“入口”，“A.txt”,“B.txt”指向的是硬盘中的同一块区域，因此这两个文件的内容是完全一样的，编辑任何一个文件都会影响到另一文件，当删除其中一个文件，只是删除这个文件其中一个“入口”，要两个文件都删除，文件系统才会标志这块硬盘区域上的文件被删除。

**符号链接(软链接)**

对文件创建符号链接

```
mklink B.txt A.txt
```

对文件夹创建符号链接

```
mklink /D linkDir targetDir
```

$\color{red} {对于文件夹的软链接创建，一定要加上"/D"。通过相对路径创建的软链接在移动后无法使用，绝对路径创建的移动后不影响使用。符号链接可以直接右键删除，或通过rmdir命令删除，不会影响原文件，但del命令则会把目标文件删除。}$

**目录联接**

1. “目录联接”只能应用于文件夹，不可用于文件。

2. 目录符号链接与目录连接点的区别
   + 目录符号链接（/D）与目录连接点（/J）非常相似，但是本质是不同的。目录符号链接依旧是符号链接，是指向目录的符号链接，而目录连接点不属于符号链接。
   + 目录符号链接允许 Target 使用相对路径，当使用相对路径时创建目录符号链接之后，如果移动了符号链接文件，操作系统将无法再找到原来的目标。
   + 目录连接点只允许 Target 使用绝对路径，当创建目录连接点时，如果传入的参数是相对路径，mklink 命令会自动将相对路径补全为绝对路径
   + $\color{red} {当目录符号链接使用绝对路径时，其行为与目录连接点完全一样。}$
   + 此外，目录符号链接还可以指定 SMB 远程网络中的路径，而目录连接点不可以。

reference:

​	https://docs.microsoft.com/zh-cn/windows-server/administration/windows-commands/mklink?view=vs-2015

https://docs.microsoft.com/zh-cn/windows-server/administration/windows-commands/mklink

https://www.cnblogs.com/life-of-coding/p/10871831.html

https://www.jianshu.com/p/b1614a073087

https://baike.baidu.com/item/mklink/566760?fr=aladdin

https://zhidao.baidu.com/question/365866222843276892.html

https://zhuanlan.zhihu.com/p/98101500