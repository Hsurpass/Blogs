

# 生成.clang-format

windows的clang-format默认放在下面这个路径：

```
C:\Users\admin\.vscode\extensions\ms-vscode.cpptools-1.16.3-win32-x64\LLVM\bin\clang-format.exe
```

ubuntu的clang-format默认放在这个路径：

```
$HOME/.vscode-server/extensions/ms-vscode.cpptools-1.16.3-linux-x64/LLVM/bin/clang-format
```

.clang-format有多种格式，可以通过 `clang-format --help` 命令查看--style 字段。

生成 .clang-format 文件的命令：

```bash
./clang-format --style=LLVM --dump-config > .clang-format
```







# reference

https://clang.llvm.org/docs/ClangFormat.html