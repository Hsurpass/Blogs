# 添加submodule

```bash
git submodule add https://github.com/chaconinc/DbConnector	#在父仓库中，默认子仓库中文件 会放在和子仓库名相同的文件夹中。
```

如果想将子仓库放到一个不同的目录，可以在命令末尾添加一个路径：

```bash
git submodule add https://github.com/chaconinc/DbConnector mytest
```

添加成功后，执行`git status` 会发现在父仓库中生成一个**子仓库目录**和一个 `.gitmodules` 文件：

```bash
$ git status
On branch master
Your branch is up-to-date with 'origin/master'.

Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

	new file:   .gitmodules
	new file:   DbConnector
```

其中`.gitmodules` 文件中记录了子仓库的地址和路径：

```json
[submodule "DbConnector"]
	path = DbConnector
	url = https://github.com/chaconinc/DbConnector
```

**如果没添加成功，看一下父仓库的`.git/modules`目录下是否有重名的文件夹，删除掉再添加即可成功。**

最后执行 git commit、git push 把子项目提交到父仓库中。



# 获取submodule

当克隆一个包含子项目的仓库时，clone下来的子模块的文件夹是空的，还要进行如下操作：

## 方法1

```bash
git submodule init	#初始化本地配置文件
git submodule update	#从该项目中抓取所有数据并检出父项目中列出的合适的提交

git submodule update --init #将上面两部合成一步
git submodule update --init --recursive	# 如果子模块还有嵌套子模块，加上--recursive
```

## 方法二

```bash
git clone git@github.com:xxxx/xxx.git --recurse-submodules
```



# 删除submodule



# reference

[Git 工具 - 子模块](https://git-scm.com/book/zh/v2/Git-%E5%B7%A5%E5%85%B7-%E5%AD%90%E6%A8%A1%E5%9D%97)