

os.path.dirname()

是 Python 标准库 `os.path` 模块中的一个函数，用于**获取指定路径的目录部分**。

**功能说明**

- 它返回路径字符串中最后一个斜杠之前的部分，也就是“父目录路径”。
- 不会判断路径是否真实存在，只是按字符串处理。

**用法示例**

```python
import os

path = '/home/user/file.txt'
dir_name = os.path.dirname(path)
print(dir_name)  # 输出: /home/user
```

**详细说明**

- 如果传入的是文件路径，返回该文件所在的目录路径。
- 如果传入的是目录路径，返回该目录的上级目录路径。
- 如果路径中没有斜杠，则返回空字符串。

**更多例子**

```python
os.path.dirname('/home/user/file.txt')      # '/home/user'
os.path.dirname('/home/user/')              # '/home'
os.path.dirname('file.txt')                 # ''
```

**总结**

**`os.path.dirname(path)` 的作用是返回 path 的目录名（即去掉最后的文件或目录名，只留下上级目录部分）。**



[Python 的混合模式调试 - Visual Studio (Windows) | Microsoft Learn](https://learn.microsoft.com/zh-cn/visualstudio/python/debugging-mixed-mode-c-cpp-python-in-visual-studio?view=vs-2022)

[Python 标准库](https://docs.python.org/zh-cn/3/library/index.html)

