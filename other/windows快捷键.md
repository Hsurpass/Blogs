# Windows快捷键：

ctrl + shift + n: 新建文件夹

ctrl + shift + esc: 打开任务管理器

win+e:打开文件夹。

`win+r` + notepad: 新建文本文档

`win+r` + regedit: 打开注册表

`win+r` + mstsc: 打开远程桌面

`win+r` + devmgmt.msc: 打开设备管理器

`win+r` + taskmgr.exe: 打开任务管理器

`win+r` + sysdm.cpl: 打开系统属性，设置环境变量会用到

## 查看电脑配置：

`win+r` + dxdiag:打开DirectX诊断工具

`win+r` + wmic: 

​	`cpu get *`: 查看CPU信息	

​	`cpu get numberofcores`: 查看cpu物理核数
​			`cpu get numberoflogicalprocessors`: 查看cpu逻辑核数



# 自定义快捷键：

## 自定义新建文本文档快捷键：
* 1.打开注册表：win + r + regedit	
* 2.找到 HKEY_CLASSES_ROOT\Local Settings\MuiCache\363\AAF68885
	
		C:\Windows\system32\notepad.exe,-469    （可以直接搜索）

   ![](image/notepad%E6%B3%A8%E5%86%8C%E5%8F%98.png)

* 3.双击，修改为：

   ![](image/%E4%BF%AE%E6%94%B9notepad%E5%BF%AB%E6%8D%B7%E9%94%AE.png)

* 4.设置成功，右击，新建，发现文本文档前面多了个T，此时$\color{red}{鼠标右击}$，键盘上按$\color{red}{WT}$就可以快速新建出文本文档了

